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

#include <allegro.h>

#include "bombs.h"
#include "player.h"
#include "qtetris.h"
#include "handle.h"
#include "objects.h"
#include "data.h"



void make_megabombs(PLAYER *player)
{
  int x, y;

  if (game_mode != GAME_MODE_DESTROYER)
    return;

  for (y=0; y<PANEL_HEIGHT-1; y++) {
    for (x=0; x<PANEL_WIDTH-1; x++) {
      if (((player->panel[y  ][x  ] & 0xf0)  == BLOCK_SPECIAL) &&
          ((player->panel[y+1][x  ] & 0xf0)  == BLOCK_SPECIAL) &&
          ((player->panel[y+1][x+1] & 0xf0)  == BLOCK_SPECIAL) &&
          ((player->panel[y  ][x+1] & 0xf0)  == BLOCK_SPECIAL)) {
        player->panel[y  ][x  ] = BLOCK_SPECIAL_LT | (player->panel[y  ][x  ] & 0xff0f);
        player->panel[y+1][x  ] = BLOCK_SPECIAL_LB | (player->panel[y+1][x  ] & 0xff0f);
        player->panel[y+1][x+1] = BLOCK_SPECIAL_RB | (player->panel[y+1][x+1] & 0xff0f);
        player->panel[y  ][x+1] = BLOCK_SPECIAL_RT | (player->panel[y  ][x+1] & 0xff0f);
      }
    }
  }
}



static void create_bomb_explo(PLAYER *player, int x, int y);



static void destroy_block(PLAYER *player, int x, int y, int mega)
{
  if ((x < 0) || (y < 0) || (x >= PANEL_WIDTH) || (y >= PANEL_HEIGHT))
    return;

  if (player->panel[y][x]) {
    if (player->panel[y][x] & 0xf0) {
      create_bomb_explo(player, x, y);
    }
    else {
      add_gameobj(55+(rand()%5), create_flyblock(
        player->px + (x+1)*BLOCK_SIZE,
        player->py + y*BLOCK_SIZE,
        player->panel[y][x], mega));

      player->panel[y][x] = 0;
    }
  }
}



static void add_score(PLAYER *player, int y, int score)
{
  int i;
  
  for (i=0; i<player->kill; i++) {
    if (y == player->killines[i]) {
      player->score += score;
      break;
    }
  }
}



static void create_bomb_explo(PLAYER *player, int x, int y)
{
  int cx, cy;
  int xx, yy;

  play(EXPLO_WAV, player->px+PANEL_WIDTH*BLOCK_SIZE/2, 255);

  if ((player->panel[y][x] & 0xf0) == BLOCK_SPECIAL) {
    add_gameobj(60+(rand()%10), create_explosion(
      player->px + x*BLOCK_SIZE + BLOCK_SIZE/2,
      player->py + y*BLOCK_SIZE + BLOCK_SIZE/2, FALSE));
    player->panel[y][x] = 0;

    add_score(player, y, SCORE_BOMB);

    for (yy=-1; yy<=1; yy++)
      for (xx=-1; xx<=1; xx++)
        destroy_block(player, x+xx, y+yy, FALSE);
  }
  else {
    cx = cy = -1;

    if ((player->panel[y][x] & 0xf0) == BLOCK_SPECIAL_LT) {
      cx = 1;
      cy = 1;
      player->panel[y  ][x  ] = player->panel[y  ][x+1] =
      player->panel[y+1][x  ] = player->panel[y+1][x+1] = 0;
    }
    else if ((player->panel[y][x] & 0xf0) == BLOCK_SPECIAL_RT) {
      cx = 0;
      cy = 1;
      player->panel[y  ][x-1] = player->panel[y  ][x  ] =
      player->panel[y+1][x-1] = player->panel[y+1][x  ] = 0;
    }
    else if ((player->panel[y][x] & 0xf0) == BLOCK_SPECIAL_LB) {
      cx = 1;
      cy = 0;
      player->panel[y-1][x  ] = player->panel[y-1][x+1] =
      player->panel[y  ][x  ] = player->panel[y  ][x+1] = 0;
    }
    else if ((player->panel[y][x] & 0xf0) == BLOCK_SPECIAL_RB) {
      cx = 0;
      cy = 0;
      player->panel[y-1][x-1] = player->panel[y-1][x  ] =
      player->panel[y  ][x-1] = player->panel[y  ][x  ] = 0;
    }

    if (cx >= 0) {
      add_gameobj(70+(rand()%10), create_explosion(
        player->px + (x+cx)*BLOCK_SIZE,
        player->py + (y+cy)*BLOCK_SIZE, TRUE));

      add_score(player, y, SCORE_MEGABOMB);

      for (yy=-3; yy<=4; yy++)
        for (xx=-3; xx<=4; xx++)
          destroy_block(player, x+cx+xx, y+cy+yy, TRUE);
    }
  }
}



void create_bombs_explosion(PLAYER *player)
{
  int x, y, i;

  for (i=0; i<player->kill; i++) {
    y = player->killines[i];

    for (x=0; x<PANEL_WIDTH; x++) {
      if (player->panel[y][x] & 0xf0)
        create_bomb_explo(player, x, y);
    }
  }

  update_gameobj_list();
}




