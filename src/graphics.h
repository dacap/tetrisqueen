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

#ifndef GRAPHICS_H
#define GRAPHICS_H



#define PAL_GRAY	0
#define PAL_RED		1
#define PAL_GREEN	2
#define PAL_BLUE	3
#define PAL_YELLOW	4
#define PAL_MAGENTA	5
#define PAL_ORANGE	6
#define PAL_LIGHTBLUE	7



extern COLOR_MAP *tint_map;
extern COLOR_MAP *tint_dark_map;
extern COLOR_MAP *trans_map;
extern COLOR_MAP *trans_dark_map;
extern COLOR_MAP *shadow_map;


int create_color_maps(void);
void destroy_color_maps(void);

void sel_palette(RGB *pal);

void textout_lit(BITMAP *bmp, FONT *f, char *str, int x, int y, int color);
void textout_centre_lit(BITMAP *bmp, FONT *f, char *str, int x, int y, int color);
void textprintf_lit(BITMAP *bmp, FONT *f, int x, int y, int color, char *format, ...);
void textprintf_centre_lit(BITMAP *bmp, FONT *f, int x, int y, int color, char *format, ...);

void capture_screen(void);



#endif /* #ifndef GRAPHICS_H */

