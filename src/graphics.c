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
#include <stdlib.h>
#include <allegro.h>

#include "graphics.h"
#include "qtetris.h"
#include "data.h"



COLOR_MAP *tint_map = NULL;
COLOR_MAP *tint_dark_map = NULL;
COLOR_MAP *trans_map = NULL;
COLOR_MAP *trans_dark_map = NULL;
COLOR_MAP *shadow_map = NULL;



static void create_shadow_table(COLOR_MAP *table, PALETTE pal, int r, int g, int b, void (*callback)(int pos))
{
   int tmp[768], *q;
   int x, y, i, j, k;
   unsigned char *p;
   RGB c;

   for (x=0; x<256; x++) {
      tmp[x*3]   = pal[x].r * (255-r) / 255;
      tmp[x*3+1] = pal[x].g * (255-g) / 255;
      tmp[x*3+2] = pal[x].b * (255-b) / 255;
   }

   for (y=0; y<PAL_SIZE; y++)
      table->data[0][y] = y;

   if (callback)
      (*callback)(0);

   for (x=1; x<256; x++) {
      i = 0 * r / 255;
      j = 0 * g / 255;
      k = 0 * b / 255;

      p = table->data[x];
      q = tmp;

      if (rgb_map) {
         for (y=0; y<256; y++) {
            c.r = i + *(q++);
            c.g = j + *(q++);
            c.b = k + *(q++);
            p[y] = rgb_map->data[c.r>>1][c.g>>1][c.b>>1];
         }
      }
      else {
         for (y=0; y<256; y++) {
            c.r = i + *(q++); 
            c.g = j + *(q++); 
            c.b = k + *(q++);
            p[y] = bestfit_color(pal, c.r, c.g, c.b);
         }
      }

      if (callback)
         (*callback)(x);
   }
}



int create_color_maps(void)
{
#define PUT(gamma) \
  for (i=0; i<16; i++)                        \
    tint_map->data[gamma][i] = gamma*16+i;    \
  for (i=0; i<16; i++)                        \
    tint_dark_map->data[gamma][i] = gamma*16+i*75/100

  int i, x, y;

  rgb_map        = malloc(sizeof(RGB_MAP));
  tint_map       = malloc(sizeof(COLOR_MAP));
  tint_dark_map  = malloc(sizeof(COLOR_MAP));
  trans_map      = malloc(sizeof(COLOR_MAP));
  trans_dark_map = malloc(sizeof(COLOR_MAP));
  shadow_map     = malloc(sizeof(COLOR_MAP));

  create_rgb_table(rgb_map, datafile[PALETTE_BMP].dat, NULL);

  for (y=0; y<PAL_SIZE; y++)
    for (x=0; x<PAL_SIZE; x++) {
      tint_map->data[y][x] = 0;
      tint_dark_map->data[y][x] = 0;
    }

  PUT(PAL_GRAY);
  PUT(PAL_RED);
  PUT(PAL_GREEN);
  PUT(PAL_BLUE);
  PUT(PAL_YELLOW);
  PUT(PAL_MAGENTA);
  PUT(PAL_ORANGE);
  PUT(PAL_LIGHTBLUE);

  create_shadow_table(shadow_map, datafile[PALETTE_BMP].dat, 128, 128, 128, NULL);
  return TRUE;
}



void destroy_color_maps(void)
{
  if (rgb_map)
    free(rgb_map);

  if (tint_map)
    free(tint_map);

  if (tint_dark_map)
    free(tint_dark_map);

  if (trans_map)
    free(trans_map);

  if (trans_dark_map)
    free(trans_dark_map);

  if (shadow_map)
    free(shadow_map);
}



void sel_palette(RGB *pal)
{
  PALETTE get_pal;

  set_palette_range(datafile[PALETTE_BMP].dat, 0, 127, TRUE);
  if (pal)
    set_palette_range(pal, 128, PAL_SIZE-1, TRUE);

  get_palette(get_pal);
  create_trans_table(trans_map, get_pal, 128, 128, 128, NULL);
  create_trans_table(trans_dark_map, get_pal, 192, 192, 192, NULL);
}



void textout_lit(BITMAP *bmp, FONT *f, char *str, int x, int y, int color)
{
  BITMAP *sprite;
  char buf[2];
  int c;

  color_map = tint_map;

  for (c=0; str[c]; c++) {
    buf[0] = str[c];
    buf[1] = 0;
    sprite = create_bitmap(text_length(f, buf), text_height(f));
    text_mode(0);
    textout(sprite, f, buf, 0, 0, -1);

    if (color < 0)
      draw_sprite(bmp, sprite, x, y);
    else
      draw_lit_sprite(bmp, sprite, x, y, color);

    x += sprite->w;
    destroy_bitmap(sprite);
  }
}



void textout_centre_lit(BITMAP *bmp, FONT *f, char *str, int x, int y, int color)
{
  int len;
  
  len = text_length(f, str);
  textout_lit(bmp, f, str, x - len/2, y, color);
}





void textprintf_lit(BITMAP *bmp, FONT *f, int x, int y, int color, char *format, ...)
{
  char buf[512];

  va_list ap;
  va_start(ap, format);
  uvsprintf(buf, format, ap);
  va_end(ap);

  textout_lit(bmp, f, buf, x, y, color);
}



void textprintf_centre_lit(BITMAP *bmp, FONT *f, int x, int y, int color, char *format, ...)
{
  char buf[512];

  va_list ap;
  va_start(ap, format);
  uvsprintf(buf, format, ap);
  va_end(ap);

  textout_centre_lit(bmp, f, buf, x, y, color);
}



void capture_screen(void)
{
  char filename[256];
  char path[256];
  char buf[13];
  PALETTE pal;
  int c;

  get_executable_name(path, 256);

  for (c=0; c<100; c++) {
    sprintf(buf, "tetris%02d.bmp", c);
    replace_filename(filename, path, buf, 256);

    if (!exists(buf))
      break;
  }

  get_palette(pal);

  save_bmp(filename, virtual, pal);
}


