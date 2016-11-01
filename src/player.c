/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#include <allegro.h>

#include "player.h"
#include "qtetris.h"
#include "playgame.h"
#include "control.h"
#include "graphics.h"
#include "handle.h"
#include "objects.h"
#include "bombs.h"
#include "hallfame.h"
#include "data.h"



PLAYER player1, player2;

int main_menu_option = 0;
int lineup_time = 0;
int lines_counter = 0;



static int score_line[] =
{
  0,
  SCORE_SINGLE,
  SCORE_DOUBLE,
  SCORE_TRIPLE,
  SCORE_TETRIS
};



static unsigned char level_lines[10] =
  { 4, 4+5,
    5, 5+6,
    6, 6+7,
    7, 7+8,
    8, 8+9 };



/* coloca la pieza actual en el panel del jugador */
static void put_piece(PLAYER *player)
{
  int c;

  get_piece_blocks(player);

  for (c=0; c<4; c++) {
    if ((player->piece.bx[c] >= 0) && (player->piece.bx[c]/BLOCK_SIZE < PANEL_WIDTH) &&
        (player->piece.by[c] >= 0) && (player->piece.by[c]/BLOCK_SIZE < PANEL_HEIGHT))
      player->panel[player->piece.by[c]/BLOCK_SIZE]
                   [player->piece.bx[c]/BLOCK_SIZE] = player->piece.block[c];
  }
}



/* obtiene si hay o no colisión entre el panel y la pieza actual */
static int get_collision(PLAYER *player)
{
  int c, x, y, bx, by, px, py;

  get_piece_blocks(player);

  /* bordes */
  for (c=0; c<4; c++) {
    if ((player->piece.bx[c] < 0) ||
        (player->piece.bx[c] > (PANEL_WIDTH -1)*BLOCK_SIZE) ||
        (player->piece.by[c] > (PANEL_HEIGHT-1)*BLOCK_SIZE))
      return TRUE;
  }

  /* panel */
  for (y=0; y<PANEL_HEIGHT; y++) {
    for (x=0; x<PANEL_WIDTH; x++) {
      for (c=0; c<4; c++) {
        if (player->panel[y][x]) {
          bx = player->piece.bx[c];
          by = player->piece.by[c];
          px = x*BLOCK_SIZE;
          py = y*BLOCK_SIZE;

          if ((bx+BLOCK_SIZE > px) && (bx < px+BLOCK_SIZE) &&
              (by+BLOCK_SIZE > py) && (by < py+BLOCK_SIZE))
            return TRUE;
        }
      }
    }
  }

  /* no hay colisión */
  return FALSE;
}



/* mira las líneas que hay que borrar */
static void lines_to_kill(PLAYER *player)
{
  int x, y, i = 0;

  for (y=0; y<PANEL_HEIGHT; y++) {
    for (x=0; x<PANEL_WIDTH; x++)
      if (!player->panel[y][x])
        break;

    if (x == PANEL_WIDTH)
      player->killines[i++] = y;
  }

  player->kill = i;
}



/* elimina las líneas que completó el jugador */
static void kill_lines(PLAYER *player)
{
  int x, y, i;

  for (i=0; i<player->kill; i++) {
    y = player->killines[i];

    /* mover todos los bloques de arriba una línea más abajo */
    for (; y>0; y--) {
      for (x=0; x<PANEL_WIDTH; x++)
        player->panel[y][x] = player->panel[y-1][x];
    }

    /* borrar la primer línea */
    y = 0;
    for (x=0; x<PANEL_WIDTH; x++)
      player->panel[y][x] = 0;

    player->killines[i] = 0;
  }

  player->kill = 0;
}



int player_death(PLAYER *player)
{
  int x;

  for (x=0; x<PANEL_WIDTH; x++) {
    if ((player->panel[0][x]) || (player->panel[1][x])) {
      qtetris_sound(DEATH_WAV, player->px+PANEL_WIDTH*BLOCK_SIZE/2, 255);

      player1.flags &= ~PLAYER_NORMAL;
      player2.flags &= ~PLAYER_NORMAL;
      player1.flags |= PLAYER_OVER;
      player2.flags |= PLAYER_OVER;
      player1.ani_time =
      player2.ani_time = game_clock;

      /* quién ganó y quién perdió? */
      player->winner = FALSE;

      if (player == &player1) {
        if (player2.flags & PLAYER_PANELDOWN) {
          kill_lines(player);
          player2.flags &= ~PLAYER_PANELDOWN;
        }
        player2.winner = TRUE;
      }
      else {
        if (player1.flags & PLAYER_PANELDOWN) {
          kill_lines(player);
          player1.flags &= ~PLAYER_PANELDOWN;
        }
        player1.winner = TRUE;
      }
      return TRUE;
    }
  }

  return FALSE;
}



/* se encargar de mover el jugador */
int move_player(PLAYER *player)
{
  int x, y;

  if (!(player->flags & PLAYER_PLAYING))
    return 0;

  /* controles */
  player->state.left      = get_control_state(player->control.left);
  player->state.right     = get_control_state(player->control.right);
  player->state.down      = get_control_state(player->control.down);
  player->state.rot_left  = get_control_state(player->control.rot_left);
  player->state.rot_right = get_control_state(player->control.rot_right);

  /* estados especiales */
  if (!(player->flags & PLAYER_NORMAL)) {
    /* OVER */
    if (player->flags & PLAYER_OVER) {
      if (!TIMEOUT(player->ani_time, TPS)) {
        int c = PANEL_HEIGHT*(game_clock - player->ani_time)/(TPS*3/4);
        c = MID(0, c, PANEL_HEIGHT);

        for (y=0; y<c; y++) {
          for (x=0; x<PANEL_WIDTH; x++) {
            if (player->panel[y][x]) {
              player->panel[y][x] &= ~0x0f;
              if (!(player->panel[y][x] & 0xf0))
                player->panel[y][x] |= BLOCK_GRAY;
            }
          }
        }
      }
      else if (!(player->flags & (PLAYER_RECORD | PLAYER_MENU))) {
        player1.flags |= PLAYER_RECORD;
        player2.flags |= PLAYER_RECORD;

        if (!make_a_new_record(&player1, game_mode)) {
          player1.flags |= PLAYER_WAITING;
          player1.name_pos = -1;
        }
        else
          player1.name_pos = 0;

        if (!make_a_new_record(&player2, game_mode)) {
          player2.flags |= PLAYER_WAITING;
          player2.name_pos = -1;
        }
        else
          player2.name_pos = 0;

        qtetris_clear_keybuf();
      }
    }

    /* RECORD */
    if (player->flags & PLAYER_RECORD) {
      if (TIMEOUT(player->key_time, TPS/10)) {
        if (player->flags & PLAYER_WAITING) {
          if (((player1.flags & PLAYER_WAITING) &&  (player2.flags & PLAYER_WAITING)) ||
              ((player1.flags & PLAYER_WAITING) && !(player2.flags & PLAYER_PLAYING))) {
            player1.flags &= ~(PLAYER_RECORD | PLAYER_WAITING);
            player2.flags &= ~(PLAYER_RECORD | PLAYER_WAITING);

            if (make_a_new_record(&player1, game_mode)) {
              add_new_record(&player1, game_mode);
              save_records();
            }

            if (make_a_new_record(&player2, game_mode)) {
              add_new_record(&player2, game_mode);
              save_records();
            }

            if ((player1.level < 51) && (player2.level < 51)) {
              player1.flags |= PLAYER_MENU;
              player2.flags |= PLAYER_MENU;
              main_menu_option = 0;
            }
            else {
              player1.flags |= PLAYER_FINISH;
              player2.flags |= PLAYER_FINISH;
              return -1;
            }

            qtetris_clear_keybuf();
          }
        }
        else if (player->state.down) {
          qtetris_sound(MENUSEL_WAV, QTETRIS_SCREEN_W/2, 255);
          player->flags |= PLAYER_WAITING;
          player->name_pos = -1;
        }
        else if (player->state.left) {
          qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
          player->key_time = game_clock;
          if (player->name_pos == 0)
            player->name_pos = 2;
          else
            player->name_pos--;
        }
        else if (player->state.right) {
          qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
          player->key_time = game_clock;
          if (player->name_pos == 2)
            player->name_pos = 0;
          else
            player->name_pos++;
        }
        else if (player->state.rot_left) {
          qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
          player->key_time = game_clock;
          if (player->name[player->name_pos] == 32)
            player->name[player->name_pos] = 127;
          else
            player->name[player->name_pos]--;
        }
        else if (player->state.rot_right) {
          qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
          player->key_time = game_clock;
          if (player->name[player->name_pos] == 127)
            player->name[player->name_pos] = 32;
          else
            player->name[player->name_pos]++;
        }
      }
    }

    /* MENU */
    if (player->flags & PLAYER_MENU) {
      if (keypressed()) {
        int scan = (readkey() >> 8);

        /* UP */
        if ((scan == KEY_UP) || (scan == KEY_8_PAD)) {
          qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
          if (main_menu_option == 0)
            main_menu_option = 2;
          else
            main_menu_option--;
        }
        /* DOWN */
        else if ((scan == KEY_DOWN) || (scan == KEY_2_PAD)) {
          qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
          if (main_menu_option == 2)
            main_menu_option = 0;
          else
            main_menu_option++;
        }
        /* ENTER */
        else if ((scan == KEY_ENTER) || (scan == KEY_ENTER_PAD) || (scan == KEY_SPACE)) {
          qtetris_sound(MENUSEL_WAV, QTETRIS_SCREEN_W/2, 255);
          /* CONTINUE */
          if (main_menu_option == 0) {
            player1.flags &= ~PLAYER_MENU;
            player2.flags &= ~PLAYER_MENU;
            player1.flags |= PLAYER_NORMAL;
            player2.flags |= PLAYER_NORMAL;

            if (player1.flags & PLAYER_OVER) {
              restart_game = TRUE;
              return -1;
            }
          }
          /* RESTART */
          else if (main_menu_option == 1) {
            player1.level = player2.level = 0;
            restart_game = TRUE;
            return -1;
          }
          /* QUIT */
          else if (main_menu_option == 2)
            return -1;
        }
      }
    }

    return 0;
  }

  /* estado normal del jugador */
  if (!(player->flags & (PLAYER_PUTPIECE | PLAYER_PANELDOWN))) {
    /* MOVIMIENTOS */
    /* DOWN */
    player->down_start = game_clock;

    if (player->state.down)
      player->piece.y += BLOCK_SIZE;
    else
      player->piece.y += (float)(player->level+1) / (float)(15.0);

    if (player->flags & PLAYER_PREPUTPIECE)
      player->piece.y++;

    /* se chocó con algo? */
    if (get_collision(player)) {
      for (; get_collision(player); --player->piece.y);

      if (!(player->flags & PLAYER_PREPUTPIECE)) {
        player->flags |= PLAYER_PREPUTPIECE;
        player->putpiece_time = game_clock;

        qtetris_sound(PREPUT_WAV, player->px+player->piece.x, 255);
      }
    }
    else if (player->flags & PLAYER_PREPUTPIECE) {
      player->piece.y--;
      player->flags &= ~PLAYER_PREPUTPIECE;
    }

    /* LEFT & RIGHT */
    if (TIMEOUT(player->key_time, TPS/10) && !(player->state.down) &&
        !(player->flags & (PLAYER_ROTATION_LEFT | PLAYER_ROTATION_RIGHT))) {
      /* LEFT */
      if (player->state.left && !(player->flags & PLAYER_RIGHT)) {
        x = player->piece.x;
        if (player->flags & (PLAYER_LEFT | PLAYER_RIGHT))
          player->piece.x = player->piece.dx;

        player->piece.x -= BLOCK_SIZE;
        if (!get_collision(player)) {
          player->piece.dx = player->piece.x;
          player->flags |= PLAYER_LEFT;

          if (player->fast_move) {
            player->piece.x -= BLOCK_SIZE;
            if (!get_collision(player))
              player->piece.dx = player->piece.x;
          }
        }

        player->piece.x = x;
        player->key_time = game_clock;
        player->fast_move = TRUE;
      }
      /* RIGHT */
      else if (player->state.right && !(player->flags & PLAYER_LEFT)) {
        x = player->piece.x;
        if (player->flags & (PLAYER_LEFT | PLAYER_RIGHT))
          player->piece.x = player->piece.dx;

        player->piece.x += BLOCK_SIZE;
        if (!get_collision(player)) {
          player->piece.dx = player->piece.x;
          player->flags |= PLAYER_RIGHT;

          if (player->fast_move) {
            player->piece.x += BLOCK_SIZE;
            if (!get_collision(player))
              player->piece.dx = player->piece.x;
          }
        }

        player->piece.x = x;
        player->key_time = game_clock;
        player->fast_move = TRUE;
      }
      else {
        player->fast_move = FALSE;
      }
    }

    /* ROTATE */
    if (!(player->state.down) && !(player->flags & (PLAYER_LEFT | PLAYER_RIGHT)) &&
        (player->state.rot_left || player->state.rot_right)) {
      if (!player->rot_time || TIMEOUT(player->rot_time, TPS/2)) {
        int old;

        x = player->piece.x;
        if (player->flags & (PLAYER_LEFT | PLAYER_RIGHT))
          player->piece.x = player->piece.dx;

        old = player->piece.rot;
        player->rot_time = game_clock;

        if (player->state.rot_left)
          player->piece.rot = (player->piece.rot+3)%(ROT_270+1);
        else
          player->piece.rot = (player->piece.rot+1)%(ROT_270+1);

        if (get_collision(player)) {
          player->piece.x = x;
          player->piece.rot = old;
        }
        /* la pieza pudo rotar... */
        else {
          player->piece.x = x;
          /* poner en ejecución la animación para rotar la pieza */
          player->flags |= (player->state.rot_left)? PLAYER_ROTATION_LEFT:
                                                     PLAYER_ROTATION_RIGHT;
          player->rot_ani_time = game_clock;

          /* crear el bitmap necesario para la animación */
          player->piece.bmp = create_piece_bitmap(player,
            &player->piece.bmp_x, &player->piece.bmp_y);

          qtetris_sound(ROTATE_WAV, player->px+player->piece.x, 255);
        }
      }
    }
    else if (player->rot_time)
      player->rot_time = 0;

    /* ANIMACIONES */
    /* LEFT */
    if (player->flags & PLAYER_LEFT) {
      player->piece.x-=3;
      if (player->piece.x <= player->piece.dx) {
        player->piece.x = player->piece.dx;
        player->flags &= ~PLAYER_LEFT;

        player->piece.x--;
        if (get_collision(player))
          qtetris_sound(PREPUT_WAV, player->px+player->piece.x, 255);
        player->piece.x++;
      }
    }
    /* RIGHT */
    else if (player->flags & PLAYER_RIGHT) {
      player->piece.x+=3;
      if (player->piece.x >= player->piece.dx) {
        player->piece.x = player->piece.dx;
        player->flags &= ~PLAYER_RIGHT;

        player->piece.x++;
        if (get_collision(player))
          qtetris_sound(PREPUT_WAV, player->px+player->piece.x, 255);
        player->piece.x--;
      }
    }
    /* ROTATE */
    if (player->flags & (PLAYER_ROTATION_LEFT | PLAYER_ROTATION_RIGHT)) {
      if (TIMEOUT(player->rot_ani_time, TPS/16)) {
        destroy_bitmap(player->piece.bmp);
        player->flags &= ~(PLAYER_ROTATION_LEFT | PLAYER_ROTATION_RIGHT);
      }
    }
    /* PREPUTPIECE */
    if (player->flags & PLAYER_PREPUTPIECE) {
      if (TIMEOUT(player->putpiece_time, TPS) ||
         (TIMEOUT(player->putpiece_time, TPS/8) && (player->state.down))) {
        x = player->piece.x;
        if (player->flags & (PLAYER_LEFT | PLAYER_RIGHT))
          player->piece.x = player->piece.dx;

        player->piece.y++;

        if (get_collision(player)) {
          player->piece.x = x;
          player->piece.y--;
          /* ...colocarla en el panel */
          put_piece(player);

          /* realizar la animación correspondiente */
          player->flags &= ~PLAYER_PREPUTPIECE;
          player->flags |= PLAYER_PUTPIECE;
          player->ani_time = game_clock;

          /* contruir las mega-bombas */
          make_megabombs(player);

          /* ver si hay líneas completas */
          lines_to_kill(player);

          /* crear las explosiones */
          if (game_mode == QTETRIS_MODE_DESTROYER) {
            if (player->kill > 0)
              create_bombs_explosion(player);
          }

          /* hay líneas por "matar"? entonces, realizar la animación
             para mostrar el mensaje que indica que tipo de línea hicimos */
          if (player->kill > 0) {
            int c;

            x = player->px + PANEL_WIDTH*BLOCK_SIZE/2;

            for (y=c=0; y<player->kill; y++)
              c += player->killines[y];

            y = (c / player->kill)*BLOCK_SIZE + BLOCK_SIZE;

            add_gameobj(90,
              create_linetype(x, player->py + y, player->kill));
            update_gameobj_list();
          }

          qtetris_sound(PUTPIECE_WAV, player->px+player->piece.x, 255);
        }
        else {
          player->piece.x = x;
          player->piece.y--;
          player->flags &= ~PLAYER_PREPUTPIECE;
        }
      }
    }
  }
  /* PUTPIECE */
  else if (player->flags & PLAYER_PUTPIECE) {
    if (TIMEOUT(player->ani_time, TPS/4)) {
      /* actualizar el puntaje */
      if (player->kill) {
        player->level_lines += player->kill;
        player->lines += player->kill;
        player->score += score_line[player->kill];

        lines_counter += ((player == &player1)? 1: -1) * player->kill;

        if (player->level_lines >= level_lines[player->level%10]) {
          player->level++;
          if (!(player->level % 2)) {
            player->level_lines = 0;
          }
        }
      }

      /* restaurar la velocidad de la bajada de la pieza */
      player->down_start = game_clock;

      /* ir a la próxima pieza */
      next_piece(player);
      get_start_piece_pos(player);

      /* hay líneas que "matar" */
      if (player->kill) {
        player->flags |= PLAYER_PANELDOWN;
        player->ani_time = game_clock;
      }
      /* y si no, fijarse si murió el jugador */
      else {
        player_death(player);
      }

      /* "limpiar" el estado del jugador */
      player->flags &= ~(PLAYER_PUTPIECE | PLAYER_LEFT | PLAYER_RIGHT |
                         PLAYER_ROTATION_LEFT | PLAYER_ROTATION_RIGHT);
    }
  }
  /* PANELDOWN */
  else if (player->flags & PLAYER_PANELDOWN) {
    if (TIMEOUT(player->ani_time, TPS/64*player->kill)) {
      player->flags &= ~PLAYER_PANELDOWN;

      qtetris_sound(PREPUT_WAV, player->px+PANEL_WIDTH*BLOCK_SIZE/2, 255);

      /* borrar las líneas completas */
      kill_lines(player);

      /* contruir las mega-bombas */
      make_megabombs(player);

      /* murió el jugador? */
      player_death(player);
    }
  }

  return 0;
}



/* dibujar todo un jugador */
void draw_player(BITMAP *bmp, PLAYER *player)
{
  FONT *f = (FONT *)datafile[FONTGAME_PCX].dat;
  int c, x, y, w, h;
  int old_x;
  float old_y;
  int old_shape, old_rot;
  int next_x, next_y;
  int yd, flag;

  if (!(player->flags & PLAYER_PLAYING))
    return;

  /* posición del indicador de la próxima pieza */
  next_y = player->py-8;
  if (player == &player1)
    next_x = player->px+BLOCK_SIZE*PANEL_WIDTH+8+1;
  else
    next_x = player->px-((BITMAP *)datafile[NEXT_BMP].dat)->w-8-1;

  /* PANEL */
  color_map = tint_map;

  draw_lit_sprite(bmp, datafile[PANEL_BMP].dat, player->px-8, player->py-8,
    (player == &player1)? PAL_BLUE: PAL_RED);

  draw_lit_sprite(bmp, datafile[NEXT_BMP].dat, next_x, next_y,
    (player == &player1)? PAL_BLUE: PAL_RED);

  /* PANEL BLOCKs */
  /* hay líneas a "matar"? */
  if (player->kill <= 0) {
    /* no, entonces dibujar el panel normalmente */
    for (y=0; y<PANEL_HEIGHT; y++)
      for (x=0; x<PANEL_WIDTH; x++)
        draw_block(bmp, player->px+x*BLOCK_SIZE,
                        player->py+y*BLOCK_SIZE, player->panel[y][x], TRUE);
  }
  /* dibujar el panel con las líneas completas */
  else {
    yd = 0;

    /* dibujar el panel desde abajo hacia arriba */
    for (y=PANEL_HEIGHT-1; y>=0; y--) {
      /* ver si esta línea (y) es una de las que se completaron */
      flag = FALSE;
      for (c=0; c<player->kill; c++) {
        if (y == player->killines[c]) {
          flag = TRUE;
          break;
        }
      }

      /* la línea no es una de las que se completaron;
         entonces dibujarla normalmente; */
      if (!flag) {
        for (x=0; x<PANEL_WIDTH; x++)
          /* note que en la posición "y" se está utilizando la
             variable yd, para que si el panel tenía líneas completas
             debajo, los bloques de arriba vayan bajando */
          draw_block(bmp, player->px+x*BLOCK_SIZE,
                          player->py+y*BLOCK_SIZE+yd, player->panel[y][x], TRUE);
      }
      /* la línea es una de las que ya se completaron */
      else {
        /* recién se colocó la pieza (PLAYER_PUTPIECE);
           por lo tanto, realizar la animación donde la línea desaparece */
        if (player->flags & PLAYER_PUTPIECE) {
          c = 4 * (game_clock-player->ani_time) / (TPS/4);
          c = MID(0, c, 3);

          for (x=0; x<PANEL_WIDTH; x++) {
            if (player->panel[y][x]) {
              blit(datafile[BLOCK_BMP].dat, block_bmp,
                BLOCK_SIZE*c, 8, 0, 0, BLOCK_SIZE, BLOCK_SIZE);

              color_map = tint_dark_map;
              draw_lit_sprite(bmp, block_bmp,
                player->px+x*BLOCK_SIZE, player->py+y*BLOCK_SIZE,
                player->panel[y][x]);
            }
          }
        }
        /* se está esperando a que baje el panel (PLAYER_PANELDOWN);
           entonces sumar a yd un valor de acuerdo al tiempo
           esperado para que se realiza una animación suave */
        else if (player->flags & PLAYER_PANELDOWN) {
          c = BLOCK_SIZE * (game_clock-player->ani_time) / (TPS/64*player->kill);
          yd += MIN(BLOCK_SIZE, c);
        }
      }
    }
  }

  /* PIECE */
  if (player->flags & PLAYER_NORMAL) {
    set_clip(bmp, player->px, player->py,
      player->px+BLOCK_SIZE*PANEL_WIDTH -1,
      player->py+BLOCK_SIZE*PANEL_HEIGHT-1);

    /* sin rotación */
    if (!(player->flags & (PLAYER_PUTPIECE | PLAYER_PANELDOWN))) {
      if (!(player->flags & (PLAYER_ROTATION_LEFT | PLAYER_ROTATION_RIGHT))) {
        get_piece_blocks(player);

        for (c=0; c<4; c++)
          draw_block(bmp, player->px+player->piece.bx[c],
                          player->py+player->piece.by[c],
                          player->piece.block[c], FALSE);
      }
      /* con rotación */
      else {
        fixed max = itofix(64);
        fixed angle = max / (TPS/16) * (game_clock - player->rot_ani_time);
        angle = MID(0, angle, max);

        rotate_sprite(bmp, player->piece.bmp,
          player->piece.bmp_x, player->piece.bmp_y,
          (player->flags & PLAYER_ROTATION_LEFT)? (max - angle): (angle - max));
      }
    }

    set_clip(bmp, 0, 0, bmp->w-1, bmp->h-1);

    /* NEXT PIECE */
    old_x     = player->piece.x;
    old_y     = player->piece.y;
    old_rot   = player->piece.rot;
    old_shape = player->piece.shape;

    player->piece.x     = 0;
    player->piece.y     = 0;
    player->piece.rot   = 0;
    player->piece.shape = pieces_list[player->piece.index+1];

    get_piece_blocks(player);
    get_piece_metrics(player, &x, &y, &w, &h);

    for (c=0; c<4; c++)
      draw_block(bmp, player->piece.bx[c]-x+next_x+BLOCK_SIZE*3-w/2,
                      player->piece.by[c]-y+next_y+BLOCK_SIZE*3-h/2,
                      player->piece.block[c], FALSE);

    player->piece.x     = old_x;
    player->piece.y     = old_y;
    player->piece.rot   = old_rot;
    player->piece.shape = old_shape;
  }

  /* SCORER */
  x = next_x;
  y = player->py + BLOCK_SIZE*6;

  text_mode(-1);

  textout(virtual, f, "SCORE", x, y+8*0, -1);
  textout(virtual, f, "LINES", x, y+8*2, -1);
  textout(virtual, f, "LEVEL", x, y+8*4, -1);

  textprintf(virtual, f, x, y+8*1, -1, "%6d", player->score);
  textprintf(virtual, f, x, y+8*3, -1, "%6d", player->lines);
  textprintf(virtual, f, x, y+8*5, -1, " %02d/%d",
    MIN(player->level, QTETRIS_LEVELS), QTETRIS_LEVELS);

  if (!(player->flags & PLAYER_NORMAL)) {
    /* OVER */
    if (player->flags & PLAYER_OVER) {
      /* dibujar la palabra WINNER o LOSER */
      BITMAP *sprite = datafile[(player->winner)? OWINNER_BMP: OLOSER_BMP].dat;
      fixed angle, scale;

      if (!TIMEOUT(player->ani_time, TPS)) {
        angle = itofix(256 - 256 * (game_clock - player->ani_time) / TPS);
        scale = itofix(1) * (game_clock - player->ani_time) / TPS;
      }
      else {
        angle = 0;
        scale = itofix(1);
      }

      pivot_scaled_sprite(bmp, sprite,
        player->px+PANEL_WIDTH*BLOCK_SIZE/2,
        player->py, sprite->w/2, sprite->h/2, angle, scale);
    }

    /* RECORD */
    if ((player->flags & PLAYER_RECORD) && (make_a_new_record(player, game_mode))) {
      text_mode(-1);

      textout_centre(bmp, datafile[FONTBIG_PCX].dat, "NEW RECORD",
        player->px+PANEL_WIDTH*BLOCK_SIZE/2, QTETRIS_SCREEN_H/3-20, -1);

      textprintf_lit(bmp, datafile[FONTBIG_PCX].dat,
        player->px+PANEL_WIDTH*BLOCK_SIZE/2-32, QTETRIS_SCREEN_H/3+20,
        (player->name_pos == 0)? PAL_YELLOW: PAL_GRAY,
        "%c", player->name[0]);

      textprintf_lit(bmp, datafile[FONTBIG_PCX].dat,
        player->px+PANEL_WIDTH*BLOCK_SIZE/2-8, QTETRIS_SCREEN_H/3+20,
        (player->name_pos == 1)? PAL_YELLOW: PAL_GRAY,
        "%c", player->name[1]);

      textprintf_lit(bmp, datafile[FONTBIG_PCX].dat,
        player->px+PANEL_WIDTH*BLOCK_SIZE/2+16, QTETRIS_SCREEN_H/3+20,
        (player->name_pos == 2)? PAL_YELLOW: PAL_GRAY,
        "%c", player->name[2]);
    }

    /* MENU */
    if (player->flags & PLAYER_MENU) {
      /* solamente hay que dibujar el menú una vez, por lo que
         si el jugador dos está jugando y "player" es el jugador
         uno, no hay que dibujar el menú (siempre el menú debe
         dibujarse al final de todo, para que quede encima) */
      if ((player2.flags & PLAYER_PLAYING) && (player != &player2))
        return;

      text_mode(-1);

      textout_centre(bmp, datafile[FONTBIG_PCX].dat, "MAIN MENU",
        QTETRIS_SCREEN_W/2, QTETRIS_SCREEN_H/3-20*1, -1);

      textout_centre_lit(bmp, datafile[FONTBIG_PCX].dat, "CONTINUE",
        QTETRIS_SCREEN_W/2, QTETRIS_SCREEN_H/3+20*1,
          (main_menu_option == 0)? PAL_YELLOW: -1);

      textout_centre_lit(bmp, datafile[FONTBIG_PCX].dat, "RESTART",
        QTETRIS_SCREEN_W/2, QTETRIS_SCREEN_H/3+20*2,
           (main_menu_option == 1)? PAL_YELLOW: -1);

      textout_centre_lit(bmp, datafile[FONTBIG_PCX].dat, "QUIT",
        QTETRIS_SCREEN_W/2, QTETRIS_SCREEN_H/3+20*3,
           (main_menu_option == 2)? PAL_YELLOW: -1);
    }
  }
}
