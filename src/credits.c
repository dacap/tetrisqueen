/*
 * TETRIS Queen
 * Copyright (C) 1999, 2000, 2001 by David A. Capello
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
#include <allegro.h>

#include "credits.h"
#include "graphics.h"
#include "handle.h"
#include "tetris.h"
#include "data.h"



int final_credits = FALSE;



#define TYPE_TITLE     0
#define TYPE_TEXT      1
#define TYPE_LINK      2



typedef struct CREDITS_LINE
{
  int next;
  char type;
  char *text;
} CREDITS_LINE;


static CREDITS_LINE credits_line[] =
{
  { 4, TYPE_TITLE, GAME_NAME },
  { 4, TYPE_TEXT, "Version " GAME_VERSION },
  { 1, TYPE_TEXT, "Programmer, Graphics," },
  { 2, TYPE_TEXT, "Sounds, Documents, Tester:" },
  { 1, TYPE_TEXT, AUTHOR_NAME },
  { 3, TYPE_LINK, AUTHOR_URL },
  { 2, TYPE_TEXT, "Translation of the docs." },
  { 1, TYPE_TEXT, "Grzegorz Adam Hankiewicz" },
  { 3, TYPE_LINK, "http://gradha.infierno.org" },
  { 1, TYPE_TEXT, "Musics:" },
  { 3, TYPE_LINK, "http://www.queentrivia.mcmail.com/" },
  { 2, TYPE_TEXT, "Thanks to:" },
  { 1, TYPE_TEXT, "Shawn Hargreaves" },
  { 1, TYPE_TEXT, "for ALLEGRO library" },
  { 2, TYPE_LINK, "http://www.talula.demon.co.uk/allegro/" },
  { 1, TYPE_TEXT, "DJ Delorie" },
  { 1, TYPE_TEXT, "for DJGPP compiler" },
  { 2, TYPE_LINK, "http://www.delorie.com/djgpp/" },
  { 1, TYPE_TEXT, "Robert Hohne" },
  { 1, TYPE_TEXT, "for RHIDE" },
  { 2, TYPE_LINK, "http://www.lanet.lv/~pavenis/rhide.html" },
  { 1, TYPE_TEXT, "Charles W Sandmann" },
  { 1, TYPE_TEXT, "for CWSDPMI" },
  {15, TYPE_LINK, "sandmann@clio.rice.edu" },
  { 1, TYPE_TEXT, AUTHOR_NAME },
  { 2, TYPE_TEXT, "Copyright (C) " GAME_DATE },
  { 1, TYPE_LINK, GAME_URL }
};


static int credits_size = sizeof(credits_line) / sizeof(CREDITS_LINE);
static int fadein;
static fixed text_y;
static fixed min_y = 0;



static int move(void *null)
{
  (void)null;

  /* si se presionar una tecla comenzar el fadeout */
  if ((!fadeout_start) && (keypressed())) {
    if ((readkey() >> 8) == KEY_ESC)
      fadeout_start = game_clock;
  }

  /* calcular el m¡nimo al que puede llegar text_y */
  if (!min_y) {
    int i, y;

    /* calcular la cantidad de pixeles que ocupa todo el texto
       de los cr‚ditos */
    y = 0;
    for (i=0; i<credits_size; i++)
      y += credits_line[i].next * text_height(font);

    /* el m¡nimo ser  desde el cuarto de pantalla para arriba */
    min_y = itofix(SCREEN_H/4 - y);
  }

  /* subir el texto 0.25 puntos */
  text_y = fsub(text_y, 0x4000);

  /* el texto lleg¢ al l¡mite? */
  if (text_y < min_y) {
    /* trabarlo */
    text_y = min_y;

    /* comenzar el fadein si es que no comenz¢ */
    if ((!fadein) && (!final_credits))
      fadein = 1;
  }

  /* realizar fadein? */
  if ((!fadeout_start) && (fadein > 0)) {
    PALETTE pal;

    push_clock();
    get_palette(pal);
    fade_from_range(pal, ALBUM_PAL(23), 2, 128, PAL_SIZE-1);
    pop_clock();

    fadein = -1;
  }

  return 0;
}



static void draw(void *null)
{
  int i, x, y;
  FONT *f;

  (void)null;

  if (!final_credits) {
    for (y=0; y<SCREEN_H; y+=10)
      for (x=0; x<SCREEN_W; x+=10)
	blit(ALBUM_BMP(23), virtual, 0, 0, x, y, 10, 10);

    blit(ALBUM_BMP(23), virtual, 0, 0,
      SCREEN_W/2-ALBUM_W/2, SCREEN_H-ALBUM_H+1, ALBUM_W, ALBUM_H);
  }
  else {
    blit(datafile[FINAL_BMP].dat, virtual, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
  }

  text_mode(-1);

  y = fixtoi(text_y);
  for (i=0; i<credits_size; i++) {
    f = datafile[(credits_line[i].type == TYPE_TITLE)? FONTBIG_PCX: FONTGAME_PCX].dat;

    textout_centre_lit(virtual, f, credits_line[i].text, SCREEN_W/2, y,
      (credits_line[i].type == TYPE_LINK)? PAL_BLUE: -1);

    y += credits_line[i].next * text_height(font);
  }
}



int play_credits(void)
{
  GAMEOBJ *old_list = gameobj_list;
  PALETTE pal;
  int c;

  gameobj_list = NULL;

  push_clock();
  play_music((!final_credits)? MUSIC19_MID: MUSIC02_MID, TRUE);
  pop_clock();

  text_y = itofix(SCREEN_H+16);

  fadeout_start = 0;
  fadein = 0;

  push_clock();
  if (!final_credits)
    sel_palette(ALBUM_PAL(23));
  else {
    PALETTE wpal;
  
    for (c=0; c<PAL_SIZE; c++)
      wpal[c].r = wpal[c].g = wpal[c].b = 63;

    get_palette(pal);
    fade_from(pal, wpal, 2);
  }
  pop_clock();
    
  draw(NULL);
  flip_to_screen();

  push_clock();
  if (!final_credits) {
    fade_interpolate(ALBUM_PAL(23), black_palette, pal, 32, 128, PAL_SIZE-1);
    fade_from_range(ALBUM_PAL(23), pal, 2, 128, PAL_SIZE-1);
  }
  else {
    get_palette(pal);
    fade_from(pal, datafile[FINALPAL_BMP].dat, 2);
    sel_palette(datafile[FINALPAL_BMP].dat);
  }
  pop_clock();

  add_gameobj(50, create_gameobj(move, draw, NULL));
  handle_game();
  delete_gameobj_list();
  gameobj_list = old_list;

  clear(screen);
  clear_keybuf();
  return D_O_K;
}



