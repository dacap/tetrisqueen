/* TETRIS Queen - Copyright (C) 1999, 2000, 2001 by David A. Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <allegro.h>

#include "playgame.h"
#include "player.h"
#include "tetris.h"
#include "graphics.h"
#include "handle.h"
#include "objects.h"
#include "credits.h"
#include "data.h"

#include "musics.h"



int restart_game = FALSE;

static int active_background = 0;
static int change_palette = FALSE;
static int change_background = 0;



static int move(void *null)
{
  static int key_time = 0;
  int c;

  (void)null;

  if (TIMEOUT(key_time, TICKS_PER_SEC/8)) {
    /* ESC - men£ */
    if (key[KEY_ESC]) {
      key_time = game_clock;
      /* colocar el men£ */
      if (player1.flags & PLAYER_NORMAL) {
        player1.flags &= ~PLAYER_NORMAL;
        player2.flags &= ~PLAYER_NORMAL;
        player1.flags |= PLAYER_MENU;
        player2.flags |= PLAYER_MENU;

        clear_keybuf();
        main_menu_option = 0;
      }
    }
    /* F1 - baja el volumen del sonido */
    else if (key[KEY_F1]) {
      key_time = game_clock;
      digi_volume -= MAX_VOLUME / 20;
      digi_volume = MID(0, digi_volume, MAX_VOLUME);
      update_volume();
    }
    /* F2 - sube el volumen del sonido */
    else if (key[KEY_F2]) {
      key_time = game_clock;
      digi_volume += MAX_VOLUME / 20;
      digi_volume = MID(0, digi_volume, MAX_VOLUME);
      update_volume();
    }
    /* F3 - baja el volumen de la m£sica */
    else if (key[KEY_F3]) {
      key_time = game_clock;
      midi_volume -= MAX_VOLUME / 20;
      midi_volume = MID(0, midi_volume, MAX_VOLUME);
      update_volume();
    }
    /* F4 - sube el volumen de la m£sica */
    else if (key[KEY_F4]) {
      key_time = game_clock;
      midi_volume += MAX_VOLUME / 20;
      midi_volume = MID(0, midi_volume, MAX_VOLUME);
      update_volume();
    }
    /* F5 - salta a la m£sica anterior */
    else if (key[KEY_F5]) {
      key_time = game_clock;
      push_clock();
      if (last_music == MUSIC01_MID)
        last_music = MUSIC34_MID;
      else
        last_music--;
      play_music(last_music, FALSE);
      pop_clock();
    }
    /* F6 - salta a la pr¢xima m£sica */
    else if (key[KEY_F6]) {
      key_time = game_clock;
      push_clock();
      if (last_music == MUSIC34_MID)
        last_music = MUSIC01_MID;
      else
        last_music++;
      play_music(last_music, FALSE);
      pop_clock();
    }
    /* F7 - cambia la m£sica por una al azar */
    else if (key[KEY_F7]) {
      key_time = game_clock;
      push_clock();
      play_music(MUSIC01_MID + rand()%(MUSIC34_MID-MUSIC01_MID+1), FALSE);
      pop_clock();
    }
  }

  /* termin¢ la m£sica, ponerla otra */
  if (midi_pos < 0) {
    push_clock();
    play_music(MUSIC01_MID + rand()%(MUSIC34_MID-MUSIC01_MID+1), FALSE);
    pop_clock();
  }

  /* agregar l¡neas extras */
  if (player1.flags & PLAYER_NORMAL) {
    if (((game_mode == GAME_MODE_DESTROYER) ||
	 (player2.flags & PLAYER_PLAYING)) &&
	(TIMEOUT(lineup_time, TICKS_PER_SEC*10))) {
      int apply1 = (player2.flags & PLAYER_PLAYING)? (lines_counter < 0): TRUE;
      int apply2 = (player2.flags & PLAYER_PLAYING)? (lines_counter > 0): TRUE;
      int times  = (player2.flags & PLAYER_PLAYING)? ABS(lines_counter): 1;
      int x, y, i, c;

      for (i=0; i<times; i++) {
	/* subir todas las l¡neas un bloque m s arriba */
	for (y=0; y<PANEL_HEIGHT; y++)
	  for (x=0; x<PANEL_WIDTH; x++) {
	    if (apply1) player1.panel[y][x] = player1.panel[y+1][x];
	    if (apply2) player2.panel[y][x] = player2.panel[y+1][x];
	  }

	/* crear una l¡nea "mala" debajo de todo */
	/* 1ro: la rellenamos */
	y = PANEL_HEIGHT-1;
	for (x=0; x<PANEL_WIDTH; x++) {
	  c = (rand()%PAL_LIGHTBLUE)+1;
	  if (apply1) player1.panel[y][x] = c;
	  if (apply2) player2.panel[y][x] = c;
	}
	/* 2do: le dejamos 3 huecos */
	for (c=0; c<3; c++) {
	  x = rand()%PANEL_WIDTH;
	  if (apply1) player1.panel[y][x] = 0;
	  if (apply2) player2.panel[y][x] = 0;
	}
      }

      /* fijarse si murieron los jugadores */
      player_death(&player1);
      if (player2.flags & PLAYER_PLAYING)
	player_death(&player2);

      lineup_time = game_clock;
      lines_counter = 0;
    }
  }
    
  /* mover los jugadores */
  if (move_player(&player1))
    return -1;
  
  if (move_player(&player2))
    return -1;

  if (player1.flags & PLAYER_MENU) {
    if (lineup_time > 0)
      lineup_time = -(game_clock - lineup_time);
  }
  else if (lineup_time <= 0)
    lineup_time = game_clock + lineup_time;

  /* preparar el final */
  if ((MAX(player1.level, player2.level) == 51) && !(player1.flags & PLAYER_OVER)) {
    player1.flags &= ~PLAYER_NORMAL;
    player2.flags &= ~PLAYER_NORMAL;
    player1.flags |= PLAYER_OVER;
    player2.flags |= PLAYER_OVER;
    player1.ani_time =
    player2.ani_time = game_clock;

    /* qui‚n gan¢ y qui‚n perdi¢? */
    player1.winner = (player1.level >= player2.level);
    player2.winner = (player1.level <= player2.level);
  }
  else {
    /* se pas¢ a otro nivel? */
    c = MAX(player1.level/2, player2.level/2);
    if (active_background != MID(0, c, 23)) {
      active_background = MID(0, c, 23);
      change_background = game_clock;
      change_palette = TRUE;
    }

    if (change_background) {
      if (TIMEOUT(change_background, TICKS_PER_SEC*2))
	change_background = 0;
    }
  }

  return 0;
}



static void draw(void *null)
{
  (void)null;

  /* dibujar el gr fico del nivel actual */
  if (change_background) {
    int scale = ALBUM_W;
    int background = active_background;

    /* calcular el tama¤o del fondo */
    if (!TIMEOUT(change_background, TICKS_PER_SEC)) {
      background--;
      scale = scale - scale * (game_clock - change_background) / TICKS_PER_SEC;
    }
    else {
      if (change_palette) {
	change_palette = FALSE;
	push_clock();
	sel_palette(ALBUM_PAL(background));
	pop_clock();
      }
    
      scale = scale * ((game_clock - change_background) - TICKS_PER_SEC) / TICKS_PER_SEC;
    }

    /* dibujar el fondo */
    if ((scale > 0) && (background >= 0)) {
      BITMAP *bmp = create_bitmap(scale, scale);

      stretch_blit(ALBUM_BMP(background), bmp,
	0, 0, ALBUM_W, ALBUM_H, 0, 0, scale, scale);

      color_map = trans_dark_map;
      draw_trans_sprite(virtual, bmp,
	SCREEN_W/2-scale/2, SCREEN_H/2-scale/2);

      destroy_bitmap(bmp);
    }
  }
  else {
    color_map = trans_dark_map;
    draw_trans_sprite(virtual, ALBUM_BMP(active_background),
      SCREEN_W/2-ALBUM_W/2, SCREEN_H/2-ALBUM_H/2);
  }

  /* dibujar las l¡neas extras a agregar, y el tiempo restante */
  if ((game_mode == GAME_MODE_DESTROYER) || (player2.flags & PLAYER_PLAYING)) {
    int x, y, time;

    if (player2.flags & PLAYER_PLAYING) {
      x = SCREEN_W/2;
    }
    else {
      x = player1.px+BLOCK_SIZE*(PANEL_WIDTH+4);
    }

    y = player1.py + BLOCK_SIZE*6;
    time = 10 - (game_clock - lineup_time) / TICKS_PER_SEC;
    time = MID(0, time, 10);

    text_mode(-1);

    textout_centre(virtual, datafile[FONTGAME_PCX].dat, "TIME", x, y+8*8, -1);
    textprintf_centre(virtual, datafile[FONTGAME_PCX].dat, x, y+8*9, -1,
      "%02d", time);

    if (player2.flags & PLAYER_PLAYING) {
      textout_centre(virtual, datafile[FONTGAME_PCX].dat, "LINES", x, y+8*11, -1);
      textprintf_centre(virtual, datafile[FONTGAME_PCX].dat, x, y+8*12, -1,
	"%02d -> PLAYER%d", ABS(lines_counter), (lines_counter <= 0)? 1: 2);
    }
  }

  /* dibujar los jugadores */
  draw_player(virtual, &player1);
  draw_player(virtual, &player2);

  /* dibujar la m£sica actual */
  if ((midi_pos >= 0) && (midi_pos < 6)) {
    int i, x, y, index, max;

    x = SCREEN_W/2;
    y = SCREEN_H-(8+2)*3;

    max = MUSIC34_MID - MUSIC01_MID + 1;
    index = last_music - MUSIC01_MID;

    text_mode(-1);
    for (i=index-1; i<=index+1; i++) {
      textout_centre_lit(virtual, datafile[FONTGAME_PCX].dat,
	music_name[(i >= 0)? (i%max): (max+i)], x, y,
	(i == index)? PAL_YELLOW: PAL_RED);
      y += 8+2;
    }
  }
}



void play_game(void)
{
  GAMEOBJ *old_list = gameobj_list;
  int x, y;

  gameobj_list = NULL;

  stop_midi();
  
  add_gameobj(50, create_gameobj(move, draw, NULL));
  add_gameobj(0, create_stars());

  /* primer nivel */
  player1.level = player2.level = 0;
  player1.level_lines =
  player2.level_lines = 0;
  
restart:;
  /* resetear la lista de piezas */
  reset_pieces_list();

  /* resetear todos los datos de cada jugador */
  player1.score = player2.score = 0;
  player1.lines = player2.lines = 0;

  for (y=0; y<PANEL_HEIGHT; y++)
    for (x=0; x<PANEL_WIDTH; x++)
      player1.panel[y][x] = player2.panel[y][x] = 0;

  player1.piece.index = player2.piece.index = 0;
  next_piece(&player1);
  next_piece(&player2);

  player1.kill = player2.kill = 0;

  player1.down_start	= player2.down_start	= game_clock;
  player1.putpiece_time	= player2.putpiece_time	= 0;
  player1.key_time	= player2.key_time	= 0;
  player1.rot_time	= player2.rot_time	= 0;
  player1.fast_move	= player2.fast_move	= FALSE;

  player1.flags |= PLAYER_NORMAL;
  player2.flags |= PLAYER_NORMAL;
  player1.ani_time = 0;
  player2.ani_time = 0;

  lineup_time = game_clock;
  lines_counter = 0;

  /* comenzar con la animaci¢n de entrada del fondo */
  active_background = MAX(MID(0, player1.level/2, 23),
			  MID(0, player2.level/2, 23));
  change_background = game_clock - TICKS_PER_SEC;
  change_palette = TRUE;

  /* comenzar el juego */
  handle_game();

  if (restart_game) {
    player1.flags &= ~(PLAYER_OVER | PLAYER_MENU);
    player2.flags &= ~(PLAYER_OVER | PLAYER_MENU);
    restart_game = FALSE;
    goto restart;
  }

  /* FINAL */
  if (player1.flags & PLAYER_FINISH) {
    final_credits = TRUE;
    play_credits();
    final_credits = FALSE;
    sel_palette(NULL);
  }

  delete_gameobj_list();
  gameobj_list = old_list;
}



