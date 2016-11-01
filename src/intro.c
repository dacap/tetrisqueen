/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#include <allegro.h>

#include "intro.h"
#include "qtetris.h"
#include "graphics.h"
#include "data.h"



void play_intro(void)
{
#define COL(index,red,green,blue) \
  if ((index>=min) && (index<=max)) { \
    pal[index].r = (red);             \
    pal[index].g = (green);           \
    pal[index].b = (blue);            \
  }

#define FADE(speed) \
  fade_from(source, pal, speed); \
  get_palette(source)

#define NORMAL() \
  min = 0;         \
  max = PAL_SIZE-1

  BITMAP *bg = (BITMAP *)datafile[MYLOGO_BMP].dat;
  PALETTE source, pal;
  int n, n2;
  int min, max;

  /* play the introduction theme */
  qtetris_music(MUSIC_INTRO, FALSE);

  n = 0;
  NORMAL();

  set_palette(black_palette);
  get_palette(source);
  get_palette(pal);

  /* DAC *********************************/
  clear(virtual);
  blit(bg, virtual, 0, 0,
    QTETRIS_SCREEN_W/2 - bg->w/2,
    QTETRIS_SCREEN_H/2 - bg->h/2, bg->w, bg->h);
  qtetris_blit(virtual);
  FADE(1);

  /* David A. Capello */
  /* fg */
  min = 1;
  max = 28;
  for (n2=0, n=min; n<=max+2; n2=n, n+=2) {
    COL(n2,  0,  0,  0);
    COL(n,   32, 32, 63);
    COL(n+1, 63, 63, 63);
    FADE(32);
  }

  /* bg */
  min = 32;
  max = 45;
  for (n=max; n>=min-4; n--) {
    NORMAL();
    for (n2=1; n2<=28; n2+=2) {
      COL(n2+1, 63-(-63*(n-45)/(45-32+4)),
                63-(-63*(n-45)/(45-32+4)),
                63-(-63*(n-45)/(45-32+4)));
      COL(n2, -63*(n-45)/(45-32+4), 0, 0);
    }

    min = 32;
    max = 45;
    COL(n+4, 63, 63, 63);
    COL(n+2, 63,  0,  0);
    COL(n,   63, 63,  0);

    FADE(64);
  }

  /* Present */
  NORMAL();
  COL(253, 63, 63, 63);
  COL(254, 32, 32, 32);
  COL(255, 16, 16, 16);
  FADE(4);

  /* fin de la primer etapa **************/
  fade_out(2);

  /* QUEEN LOGO **************************/
  fade_out(2);

  clear(virtual);
  blit(datafile[QUEENLOG_BMP].dat, virtual, 0, 0,
    QTETRIS_SCREEN_W/2-((BITMAP *)datafile[QUEENLOG_BMP].dat)->w/2,
    QTETRIS_SCREEN_H/2-((BITMAP *)datafile[QUEENLOG_BMP].dat)->h/2,
    ((BITMAP *)datafile[QUEENLOG_BMP].dat)->w,
    ((BITMAP *)datafile[QUEENLOG_BMP].dat)->h);
  qtetris_blit(virtual);

  fade_in(datafile[PALETTE_BMP].dat, 1);
  get_palette(pal);
  get_palette(source);
  FADE(2);
  fade_out(2);

  /* TETRIS ******************************/
  set_palette(black_palette);

  get_palette(source);
  get_palette(pal);

  NORMAL();
  for (n=0; n<PAL_SIZE; n++) {
    COL(n, 63, 63, 63);
  }
  FADE(2);

  /* mainscreen */
  clear(virtual);
  drawing_mode(DRAW_MODE_COPY_PATTERN, datafile[TETRISBG_BMP].dat, 0, 0);
  rectfill(virtual, 0, 0, QTETRIS_SCREEN_W, QTETRIS_SCREEN_H, -1);

  color_map = shadow_map;
  drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
  draw_trans_sprite(virtual, datafile[TETRIS_BMP].dat,
    QTETRIS_SCREEN_W/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->w/2 + 6,
    QTETRIS_SCREEN_H/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->h/2 + 12);
  solid_mode();

  draw_sprite(virtual, datafile[TETRIS_BMP].dat,
    QTETRIS_SCREEN_W/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->w/2,
    QTETRIS_SCREEN_H/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->h/2);
  qtetris_blit(virtual);

  for (n=15; n<112; n++) {
    COL(n, 0, 0, 0);
  }
  FADE(2);
  FADE(2);

  fade_from(pal, datafile[PALETTE_BMP].dat, 2);
}
