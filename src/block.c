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

#include <allegro.h>

#include "block.h"
#include "graphics.h"
#include "tetris.h"
#include "data.h"



BITMAP *block_bmp = NULL;



void draw_block(BITMAP *bmp, int x, int y, BLOCK block, int dark)
{
  if (!block_bmp)
    block_bmp = create_bitmap(BLOCK_SIZE, BLOCK_SIZE);

  if (block) {
    if (!(block & 0xf0) || ((block & 0xf0) == BLOCK_GRAY))
      blit(datafile[BLOCK_BMP].dat, block_bmp, 0, 0, 0, 0, BLOCK_SIZE, BLOCK_SIZE);
    else {
      blit(datafile[BLOCK_BMP].dat, block_bmp,
	((block & 0xf0) >> 4) * BLOCK_SIZE, 0, 0, 0, BLOCK_SIZE, BLOCK_SIZE);

      block = PAL_GRAY;
      dark = FALSE;
    }

    color_map = (dark)? tint_dark_map: tint_map;
    draw_lit_sprite(bmp, block_bmp, x, y, (block & 0x0f));
  }
}




