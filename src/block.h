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

#ifndef BLOCK_H
#define BLOCK_H



#define BLOCK_SIZE		8

#define BLOCK_SPECIAL		0x10
#define BLOCK_SPECIAL_LT	0x20
#define BLOCK_SPECIAL_RT	0x30
#define BLOCK_SPECIAL_LB	0x40
#define BLOCK_SPECIAL_RB	0x50
#define BLOCK_GRAY		0xf0



typedef unsigned char BLOCK;


extern BITMAP *block_bmp;


void draw_block(BITMAP *bmp, int x, int y, BLOCK block, int dark);



#endif /* #ifndef BLOCK_H */

