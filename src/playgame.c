/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#include <allegro.h>

#include "playgame.h"
#include "player.h"
#include "qtetris.h"
#include "graphics.h"
#include "handle.h"
#include "objects.h"
#include "credits.h"
#include "data.h"

#include "musics.h"



int restart_game = FALSE;

static int active_background = -1;
static int change_palette = FALSE;
static int change_background = 0;



static int get_level_album(int level)
{
  int album = ALBUM_FIRST + (ALBUM_LAST-ALBUM_FIRST)*level/QTETRIS_LEVELS;
  return MID(ALBUM_FIRST, album, ALBUM_LAST);
}



static int move(void *null)
{
  static int key_time = 0;
  int c;

  (void)null;

  if (TIMEOUT(key_time, TPS/8)) {
    /* ESC - menú */
    if (key[KEY_ESC]) {
      key_time = game_clock;
      /* put the player menu */
      if (player1.flags & PLAYER_NORMAL) {
        player1.flags &= ~PLAYER_NORMAL;
        player2.flags &= ~PLAYER_NORMAL;
        player1.flags |= PLAYER_MENU;
        player2.flags |= PLAYER_MENU;

        qtetris_clear_keybuf();
        main_menu_option = 0;
      }
    }
    /* F1 - down the sound volume */
    else if (key[KEY_F1]) {
      key_time = game_clock;
      digi_volume -= MAX_VOLUME / 20;
      digi_volume = MID(0, digi_volume, MAX_VOLUME);
      qtetris_update_volume();
    }
    /* F2 - up the sound volume */
    else if (key[KEY_F2]) {
      key_time = game_clock;
      digi_volume += MAX_VOLUME / 20;
      digi_volume = MID(0, digi_volume, MAX_VOLUME);
      qtetris_update_volume();
    }
    /* F3 - down the music volume */
    else if (key[KEY_F3]) {
      key_time = game_clock;
      midi_volume -= MAX_VOLUME / 20;
      midi_volume = MID(0, midi_volume, MAX_VOLUME);
      qtetris_update_volume();
    }
    /* F4 - up the sound volume */
    else if (key[KEY_F4]) {
      key_time = game_clock;
      midi_volume += MAX_VOLUME / 20;
      midi_volume = MID(0, midi_volume, MAX_VOLUME);
      qtetris_update_volume();
    }
    /* F5 - jump to previous music */
    else if (key[KEY_F5]) {
      key_time = game_clock;
      qtetris_push_clock();
      if (last_music == MUSIC_FIRST)
        last_music = MUSIC_LAST;
      else
        last_music--;
      qtetris_music(last_music, FALSE);
      qtetris_pop_clock();
    }
    /* F6 - jump to next music */
    else if (key[KEY_F6]) {
      key_time = game_clock;
      qtetris_push_clock();
      if (last_music == MUSIC_LAST)
        last_music = MUSIC_FIRST;
      else
        last_music++;
      qtetris_music(last_music, FALSE);
      qtetris_pop_clock();
    }
    /* F7 - jump to a random theme */
    else if (key[KEY_F7]) {
      key_time = game_clock;
      qtetris_push_clock();
      qtetris_music(MUSIC_FIRST + rand()%(MUSIC_LAST-MUSIC_FIRST+1), FALSE);
      qtetris_pop_clock();
    }
  }

  /* the music is stopped, play a new one */
  if (midi_pos < 0) {
    qtetris_push_clock();
    qtetris_music(MUSIC_FIRST + rand()%(MUSIC_LAST-MUSIC_FIRST+1), FALSE);
    qtetris_pop_clock();
  }

  /* add extra lines */
  if (player1.flags & PLAYER_NORMAL) {
    if (((game_mode == QTETRIS_MODE_DESTROYER) || (player2.flags & PLAYER_PLAYING)) &&
        (TIMEOUT(lineup_time, TPS*10))) {
      int apply1 = (player2.flags & PLAYER_PLAYING)? (lines_counter < 0): TRUE;
      int apply2 = (player2.flags & PLAYER_PLAYING)? (lines_counter > 0): TRUE;
      int times  = (player2.flags & PLAYER_PLAYING)? ABS(lines_counter): 1;
      int x, y, i, c;

      for (i=0; i<times; i++) {
        /* subir todas las líneas un bloque más arriba */
        for (y=0; y<PANEL_HEIGHT; y++)
          for (x=0; x<PANEL_WIDTH; x++) {
            if (apply1) player1.panel[y][x] = player1.panel[y+1][x];
            if (apply2) player2.panel[y][x] = player2.panel[y+1][x];
          }

        /* crear una línea "mala" debajo de todo */
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

  /* move all players */
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

  /* some player pass the final level */
  if ((MAX(player1.level, player2.level) == QTETRIS_LEVELS+1) &&
      !(player1.flags & PLAYER_OVER)) {
    player1.flags &= ~PLAYER_NORMAL;
    player2.flags &= ~PLAYER_NORMAL;
    player1.flags |= PLAYER_OVER;
    player2.flags |= PLAYER_OVER;
    player1.ani_time =
    player2.ani_time = game_clock;

    /* who win and who loss? */
    player1.winner = (player1.level >= player2.level);
    player2.winner = (player1.level <= player2.level);
  }
  else {
    /* next level? */
    c = MAX(get_level_album(player1.level), get_level_album(player2.level));

    if (active_background != c) {
      active_background = c;
      change_background = game_clock;
      change_palette = TRUE;
    }

    /* the background is changing? */
    if (change_background) {
      /* the background transition delay only two seconds */
      if (TIMEOUT(change_background, TPS*2))
        /* the animation is over */
        change_background = 0;
    }
  }

  return 0;
}



static void draw(void *null)
{
  (void)null;

  /* draw the album cover... */

  /* ...in a transition */
  if (change_background) {
    int background = active_background;
    int scale;

    /* calcule the background size... */

    /* output... */
    if (!TIMEOUT(change_background, TPS)) {
      background--;
      scale = ALBUM_W - ALBUM_W * (game_clock - change_background) / TPS;
    }
    /* input... */
    else {
      if (change_palette) {
        change_palette = FALSE;
        qtetris_push_clock();
        sel_palette(ALBUM_PAL(background));
        qtetris_pop_clock();
      }

      scale = ALBUM_W * (game_clock - change_background - TPS) / TPS;
    }

    scale = MIN(scale, ALBUM_W);

    /* draw the scaled background */
    if ((scale >= 0) && (background >= ALBUM_FIRST)) {
      BITMAP *bmp = create_bitmap(scale, scale);

      if (bmp) {
	stretch_blit(ALBUM_BMP(background), bmp,
          0, 0, ALBUM_W, ALBUM_H, 0, 0, scale, scale);

        color_map = trans_dark_map;
        draw_trans_sprite(virtual, bmp,
          QTETRIS_SCREEN_W/2 - scale/2,
          QTETRIS_SCREEN_H/2 - scale/2);

        destroy_bitmap(bmp);
      }
    }
  }
  /* ...in a normal status */
  else {
    color_map = trans_dark_map;
    draw_trans_sprite(virtual, ALBUM_BMP(active_background),
      QTETRIS_SCREEN_W/2 - ALBUM_W/2,
      QTETRIS_SCREEN_H/2 - ALBUM_H/2);
  }

  /* draw the two player mode scorers */
  if ((game_mode == QTETRIS_MODE_DESTROYER) || (player2.flags & PLAYER_PLAYING)) {
    int x, y, time;

    if (player2.flags & PLAYER_PLAYING) {
      x = QTETRIS_SCREEN_W/2;
    }
    else {
      x = player1.px+BLOCK_SIZE*(PANEL_WIDTH+4);
    }

    y = player1.py + BLOCK_SIZE*6;
    time = 10 - (game_clock - lineup_time) / TPS;
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

  /* draw the two players */
  draw_player(virtual, &player1);
  draw_player(virtual, &player2);

  /* draw the active playing theme? */
  if ((midi_pos >= 0) && (midi_pos < 6)) {
    int i, x, y, index, max;

    x = QTETRIS_SCREEN_W/2;
    y = QTETRIS_SCREEN_H-(8+2)*3;

    max = MUSIC_LAST - MUSIC_FIRST + 1;
    index = last_music - MUSIC_FIRST;

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
  player1.level = 0;
  player2.level = 0;
  player1.level_lines = 0;
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

  player1.piece.index = 0;
  player2.piece.index = 0;
  next_piece(&player1);
  next_piece(&player2);

  player1.kill = 0;
  player2.kill = 0;

  player1.down_start    = player2.down_start    = game_clock;
  player1.putpiece_time = player2.putpiece_time = 0;
  player1.key_time      = player2.key_time      = 0;
  player1.rot_time      = player2.rot_time      = 0;
  player1.fast_move     = player2.fast_move     = FALSE;

  player1.flags |= PLAYER_NORMAL;
  player2.flags |= PLAYER_NORMAL;
  player1.ani_time = 0;
  player2.ani_time = 0;

  lineup_time = game_clock;
  lines_counter = 0;

  /* comenzar con la animación de entrada del fondo */
  active_background = MAX(get_level_album(player1.level),
                          get_level_album(player2.level));
  change_background = game_clock - TPS;
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
