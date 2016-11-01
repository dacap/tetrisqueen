/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#include <allegro.h>

#include "block.h"
#include "graphics.h"
#include "qtetris.h"
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
