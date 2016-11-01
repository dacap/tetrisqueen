/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H



#define PAL_GRAY        0
#define PAL_RED         1
#define PAL_GREEN       2
#define PAL_BLUE        3
#define PAL_YELLOW      4
#define PAL_MAGENTA     5
#define PAL_ORANGE      6
#define PAL_LIGHTBLUE   7



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
