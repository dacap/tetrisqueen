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

#include <stdio.h>
#include <string.h>
#include <allegro.h>

#include "hallfame.h"
#include "qtetris.h"
#include "graphics.h"
#include "handle.h"
#include "player.h"
#include "data.h"



#define MAX_PLAYERS   14



typedef struct HALLFAME
{
  char name[3];
  int score, lines, level;
} HALLFAME;


static HALLFAME hallfame_classic[MAX_PLAYERS];
static HALLFAME hallfame_destroyer[MAX_PLAYERS];
static HALLFAME *hallfame = NULL;

static HALLFAME default_hallfame_classic[MAX_PLAYERS] =
{
  { "ARG",      5470,   143,    22 },
  { "$$$",      4660,   105,    16 },
  { "AMD",      4300,   169,    26 },
  { "ERR",      2630,   30,     5  },
  { "CPU",      2480,   105,    17 },
  { "WWW",      2360,   72,     12 },
  { "CQC",      1670,   83,     13 },
  { "AH!",      850,    16,     3  },
  { "Y2K",      620,    33,     5  },
  { "OJO",      360,    24,     4  },
  { "`I'",      190,    13,     2  },
  { "COM",      90,     6,      1  },
  { "286",      80,     3,      0  },
  { "#!@",      10,     0,      0  },
};

static HALLFAME default_hallfame_destroyer[MAX_PLAYERS] =
{
  { "ARG",      9670,   190,    29 },
  { "$$$",      2320,   52,     8 },
  { "AMD",      1870,   39,     7 },
  { "ERR",      1540,   30,     6 },
  { "CPU",      1530,   25,     5 },
  { "WWW",      1410,   28,     7 },
  { "CQC",      1380,   18,     3 },
  { "AH!",      810,    20,     4 },
  { "Y2K",      720,    17,     3 },
  { "OJO",      670,    11,     3 },
  { "`I'",      650,    15,     3 },
  { "COM",      530,    14,     3 },
  { "286",      520,    13,     3 },
  { "#!@",      320,    8,      4 },
};


static int game_over = FALSE;
static int sel;


char hof_file[256];



int load_records(void)
{
  PACKFILE *f = pack_fopen(hof_file, F_READ);

  if (!f) {
    reset_high_scores(QTETRIS_MODE_CLASSIC);
    reset_high_scores(QTETRIS_MODE_DESTROYER);
    return FALSE;
  }
  else {
    pack_fread(hallfame_classic,   sizeof(hallfame_classic),   f);
    pack_fread(hallfame_destroyer, sizeof(hallfame_destroyer), f);
    pack_fclose(f);
    return TRUE;
  }
}



int save_records(void)
{
  PACKFILE *f = pack_fopen(hof_file, F_WRITE);

  if (!f) {
    return FALSE;
  }
  else {
    pack_fwrite(hallfame_classic,   sizeof(hallfame_classic),   f);
    pack_fwrite(hallfame_destroyer, sizeof(hallfame_destroyer), f);
    pack_fclose(f);
    return TRUE;
  }
}



void reset_high_scores(int game_mode)
{
  if (game_mode == QTETRIS_MODE_CLASSIC)
    memcpy(hallfame_classic, default_hallfame_classic, sizeof(hallfame_classic));
  else if (game_mode == QTETRIS_MODE_DESTROYER)
    memcpy(hallfame_destroyer, default_hallfame_destroyer, sizeof(hallfame_destroyer));
}



int make_a_new_record(PLAYER *player, int game_mode)
{
  HALLFAME *hallfame = (game_mode == QTETRIS_MODE_CLASSIC  )? hallfame_classic:
                       (game_mode == QTETRIS_MODE_DESTROYER)? hallfame_destroyer:
                       NULL;
  int i;

  if (!hallfame)
    return FALSE;

  for (i=0; i<MAX_PLAYERS; i++)
    if (player->score > hallfame[i].score)
      return TRUE;

  return FALSE;
}



void add_new_record(PLAYER *player, int game_mode)
{
  HALLFAME *hallfame = (game_mode == QTETRIS_MODE_CLASSIC  )? hallfame_classic:
                       (game_mode == QTETRIS_MODE_DESTROYER)? hallfame_destroyer:
                       NULL;
  HALLFAME temp;
  int i, j;

  if (!hallfame)
    return;

  /* agregar el nuevo record al final */
  i = MAX_PLAYERS-1;
  strcpy(hallfame[i].name, player->name);
  hallfame[i].score = player->score;
  hallfame[i].lines = player->lines;
  hallfame[i].level = player->level;

  /* acomodar la lista */
  for (i=0; i<MAX_PLAYERS-1; i++) {
    for (j=i+1; j<MAX_PLAYERS; j++) {
      if (hallfame[i].score < hallfame[j].score) {
        temp = hallfame[i];
        hallfame[i] = hallfame[j];
        hallfame[j] = temp;
      }
    }
  }
}



static int is_in_the_hall(PLAYER *player, int game_mode)
{
  HALLFAME *hallfame = (game_mode == QTETRIS_MODE_CLASSIC  )? hallfame_classic:
                       (game_mode == QTETRIS_MODE_DESTROYER)? hallfame_destroyer:
                       NULL;
  int i;

  if (!hallfame)
    return FALSE;

  for (i=0; i<MAX_PLAYERS; i++)
    if ((strcmp(player->name, hallfame[i].name) == 0) &&
        (player->score == hallfame[i].score) &&
        (player->lines == hallfame[i].lines) &&
        (player->level == hallfame[i].level))
      return TRUE;

  return FALSE;
}



int merge_records(const char *filename)
{
  PACKFILE *f = pack_fopen(filename, F_READ);
  HALLFAME hallfame[MAX_PLAYERS];
  PLAYER player;
  int i;

  if (!f)
    return -1;
  else {
    pack_fread(&hallfame, sizeof(hallfame), f);

    for (i=0; i<MAX_PLAYERS; i++) {
      strcpy(player.name, hallfame[i].name);
      player.score = hallfame[i].score;
      player.lines = hallfame[i].lines;
      player.level = hallfame[i].level;

      if (!is_in_the_hall(&player, QTETRIS_MODE_CLASSIC) &&
          make_a_new_record(&player, QTETRIS_MODE_CLASSIC))
        add_new_record(&player, QTETRIS_MODE_CLASSIC);
    }

    pack_fread(&hallfame, sizeof(hallfame), f);

    for (i=0; i<MAX_PLAYERS; i++) {
      strcpy(player.name, hallfame[i].name);
      player.score = hallfame[i].score;
      player.lines = hallfame[i].lines;
      player.level = hallfame[i].level;

      if (!is_in_the_hall(&player, QTETRIS_MODE_DESTROYER) &&
          make_a_new_record(&player, QTETRIS_MODE_DESTROYER))
        add_new_record(&player, QTETRIS_MODE_DESTROYER);
    }

    pack_fclose(f);
    return 0;
  }
}



static int move(void *null)
{
  int scan = 0;

  (void)null;

  if (keypressed())
    scan = (readkey() >> 8);
    
  if (!fadeout_start && (scan == KEY_ESC))
    fadeout_start = game_clock;

  /* mover la selección hacia arriba... */
  if ((scan == KEY_UP) || (scan == KEY_8_PAD)) {
    if (sel>0)
      sel--;
    else
      sel = MAX_PLAYERS-1;

    qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
  }
  /* ...o hacia abajo */
  else if ((scan == KEY_DOWN) || (scan == KEY_2_PAD)) {
    if (sel<MAX_PLAYERS-1)
      sel++;
    else
      sel = 0;
      
    qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
  }
  /* cambiar de salón */
  else if ((scan == KEY_LEFT)  || (scan == KEY_RIGHT) ||
           (scan == KEY_4_PAD) || (scan == KEY_6_PAD)) {
    if (hallfame == hallfame_classic)
      hallfame = hallfame_destroyer;
    else
      hallfame = hallfame_classic;
      
    qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
  }

  return 0;
}



static void draw(void *null)
{
  FONT *f = datafile[FONTGAME_PCX].dat;
  char *str;
  int i, y;

  (void)null;

  blit(datafile[HALLFAME_BMP].dat, virtual, 0, 0, 0, 0, QTETRIS_SCREEN_W, QTETRIS_SCREEN_H);

  text_mode(-1);

  textout_centre(virtual, datafile[FONTBIG_PCX].dat, "HALL OF FAME",
    QTETRIS_SCREEN_W/2, 0, -1);

  str = ((hallfame == hallfame_classic)? "CLASSIC": "DESTROYER");
  y = text_height(datafile[FONTBIG_PCX].dat)-6;

  textout_centre(virtual, f, str, QTETRIS_SCREEN_W/2+1, y, 0);
  textout_centre(virtual, f, str, QTETRIS_SCREEN_W/2-1, y, 0);
  textout_centre(virtual, f, str, QTETRIS_SCREEN_W/2, y+1, 0);
  textout_centre(virtual, f, str, QTETRIS_SCREEN_W/2, y-1, 0);
  textout_centre(virtual, f, str, QTETRIS_SCREEN_W/2, y, -1);

  color_map = trans_map;
  drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
  rectfill(virtual, 8*2, 8*4-1, 8*8,  8*5+1, 15);
  rectfill(virtual, 8*9, 8*4-1, 8*36, 8*5+1, 15);
  solid_mode();

  textout_lit(virtual, f, "Player", 8*2,   8*4, PAL_YELLOW);
  textout_lit(virtual, f, "Score",  8*9,   8*4, PAL_ORANGE);
  textout_lit(virtual, f, "Lines",  8*20,  8*4, PAL_GREEN);
  textout_lit(virtual, f, "Level",  8*31,  8*4, PAL_BLUE);

  y = 8*5+1+4;
  for (i=0; i<MAX_PLAYERS; i++) {
    color_map = trans_map;
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    rectfill(virtual, 8*2, y, 8*8, y+8+2,
      (sel == i)? makecol(255, 255, 0): makecol(192, 192, 192));
      
    rectfill(virtual, 8*9, y, 8*36, y+8+2,
      (sel == i)? makecol(255, 255, 0): makecol(128, 128, 128));
      
    solid_mode();
  
    textout_centre_lit(virtual, f, hallfame[i].name, 8*5, y+1, -1);

    textprintf_lit(virtual, f, 8*9,  y+1, -1, "%6d", hallfame[i].score);
    textprintf_lit(virtual, f, 8*20, y+1, -1, "%6d", hallfame[i].lines);

    if (hallfame[i].level <= 50)
      textprintf_lit(virtual, f, 8*30, y+1, -1, " %02d/50", hallfame[i].level);
    else
      textprintf_lit(virtual, f, 8*30, y+1, -1, " FINAL");

    y += 1+8+1+4;
  }
}



int play_hall_of_fame(void)
{
  GAMEOBJ *old_list = gameobj_list;

  gameobj_list = NULL;

  qtetris_push_clock();
  qtetris_music(MUSIC_HOF, TRUE);
  qtetris_pop_clock();

  hallfame = hallfame_classic;
  sel = 0;

  game_over = FALSE;
  fadeout_start = 0;

  add_gameobj(10, create_gameobj(move, draw, NULL));
  handle_game();
  delete_gameobj_list();
  gameobj_list = old_list;

  return D_O_K;
}



