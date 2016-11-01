/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#ifndef BLOCK_H
#define BLOCK_H



#define BLOCK_SIZE              8

#define BLOCK_SPECIAL           0x10
#define BLOCK_SPECIAL_LT        0x20
#define BLOCK_SPECIAL_RT        0x30
#define BLOCK_SPECIAL_LB        0x40
#define BLOCK_SPECIAL_RB        0x50
#define BLOCK_GRAY              0xf0



typedef unsigned char BLOCK;


extern BITMAP *block_bmp;


void draw_block(BITMAP *bmp, int x, int y, BLOCK block, int dark);



#endif /* #ifndef BLOCK_H */
