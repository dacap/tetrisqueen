/*
 * TETRIS Queen - Version 1.3
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



#define TYPE_END      -1
#define TYPE_TITLE     0
#define TYPE_TEXT      1
#define TYPE_LINK      2



int final_credits = FALSE;


static int game_over = FALSE;
static int text_y;
static int fadein;



static int move(void *null)
{
  (void)null;

  if (!fadeout_start && keypressed()) {
    if ((readkey() >> 8) == KEY_ESC)
      fadeout_start = game_clock;
  }

  text_y -= 2;
  if (text_y < ((24-56*8) << 3)) {
    text_y = ((24-56*8) << 3);
    if (!(fadein) && !(final_credits))
      fadein = 1;
  }

  if (!fadeout_start && fadein > 0) {
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
  static struct {
    char type;
    char *text;
  } info[] = {
	{ TYPE_TITLE, "TETRIS Queen" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "(version " GAME_VER ")" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Programmer, Graphics," },
	{ TYPE_TEXT, "Sounds, Documents, Tester:" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "David Alfredo Capello" },
	{ TYPE_LINK, AUTHOR_EMAIL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Translation of the docs." },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Grzegorz Adam Hankiewicz" },
	{ TYPE_LINK, "http://welcome.to/gogosoftware/" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Musics:" },
	{ TYPE_LINK, "http://www.queentrivia.mcmail.com/" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Thanks to:" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Shawn Hargreaves" },
	{ TYPE_TEXT, "for ALLEGRO library" },
	{ TYPE_LINK, "http://www.talula.demon.co.uk/allegro/" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "DJ Delorie" },
	{ TYPE_TEXT, "for DJGPP compiler" },
	{ TYPE_LINK, "http://www.delorie.com/djgpp/" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Robert Hohne" },
	{ TYPE_TEXT, "for RHIDE" },
	{ TYPE_LINK, "http://www.lanet.lv/~pavenis/rhide.html" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, "Charles W Sandmann" },
	{ TYPE_TEXT, "for CWSDPMI" },
	{ TYPE_LINK, "sandmann@clio.rice.edu" },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL },
	{ TYPE_TEXT, NULL }, { TYPE_TEXT,  NULL }, { TYPE_TEXT,  NULL },
	{ TYPE_TEXT, NULL }, { TYPE_TEXT,  NULL }, { TYPE_TEXT,  NULL },
	{ TYPE_TEXT, NULL }, { TYPE_TEXT,  NULL }, { TYPE_TEXT,  NULL },
	{ TYPE_TEXT, NULL }, { TYPE_TEXT,  NULL }, { TYPE_TEXT,  NULL },
	{ TYPE_TEXT, "David Alfredo Capello" },
	{ TYPE_TEXT, "Copyright (C) " GAME_DATE },
	{ TYPE_TEXT, NULL },
	{ TYPE_LINK, AUTHOR_WEB },
	{ TYPE_END, NULL }
  };

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

  for (i=0; info[i].type != TYPE_END; i++) {
    if (info[i].text) {
      f = datafile[(info[i].type == TYPE_TITLE)? FONTBIG_PCX: FONTGAME_PCX].dat;

      textout_centre_lit(virtual, f, info[i].text,
        SCREEN_W/2, (text_y >> 3)+i*8,
        (info[i].type == TYPE_LINK)? PAL_BLUE: -1);
    }
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

  text_y = (SCREEN_H+16) << 3;

  game_over = FALSE;
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

  if (!final_credits) {
    push_clock();
    fade_interpolate(ALBUM_PAL(23), black_palette, pal, 32, 128, PAL_SIZE-1);
    fade_from_range(ALBUM_PAL(23), pal, 2, 128, PAL_SIZE-1);
    pop_clock();
  }
  else {
    push_clock();
    get_palette(pal);
    fade_from(pal, datafile[FINALPAL_BMP].dat, 2);
    sel_palette(datafile[FINALPAL_BMP].dat);
    pop_clock();
  }

  add_gameobj(50, create_gameobj(move, draw, NULL));
  handle_game();
  delete_gameobj_list();
  gameobj_list = old_list;

  clear(screen);
  clear_keybuf();
  return D_O_K;
}



