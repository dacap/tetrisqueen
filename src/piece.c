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

#include <math.h>
#include <stdlib.h>
#include <allegro.h>

#include "piece.h"
#include "tetris.h"
#include "player.h"



int pieces[MAX_PIECES][4][8] =
{
  /* Shape: I (PAL_RED)
   *                  [0]                   [3]
   * [0][1].[2][3]   .[1]         .         [2].
   *                  [2]   [3][2] [1][0]   [1]
   *                  [3]                   [0]
   */
  { { 3, 0,   4, 0,   5, 0,   6, 0 },
    { 5,-1,   5, 0,   5, 1,   5, 2 },
    { 6, 1,   5, 1,   4, 1,   3, 1 },
    { 4, 2,   4, 1,   4, 0,   4,-1 } },
  /* Shape: T (PAL_GREEN)
   *
   *    [2]      [1]                     [3]
   * [1](0)[3]   (0)[2]   [3](0)[1]   [2](0)
   *             [3]         [2]         [1]
   */
  { { 4, 1,   3, 1,   4, 0,   5, 1 },
    { 4, 1,   4, 0,   5, 1,   4, 2 },
    { 4, 1,   5, 1,   4, 2,   3, 1 },
    { 4, 1,   4, 2,   3, 1,   4, 0 } },
  /* Shape: O (PAL_BLUE)
   *
   * [0].[1]   [3].[0]   [2].[3]   [1].[2]
   * [3] [2]   [2] [1]   [1] [0]   [0] [3]
   */
  { { 4, 0,   5, 0,   5, 1,   4, 1 },
    { 5, 0,   5, 1,   4, 1,   4, 0 },
    { 5, 1,   4, 1,   4, 0,   5, 0 },
    { 4, 1,   4, 0,   5, 0,   5, 1 } },
  /* Shape: J (PAL_YELLOW)
   *
   * [0]        [1][0]                  [3]
   * [1](2)[3]  (2)      [3](2)[1]      (2)
   *            [3]            [0]   [0][1]
   */
  { { 3, 0,   3, 1,   4, 1,   5, 1 },
    { 5, 0,   4, 0,   4, 1,   4, 2 },
    { 5, 2,   5, 1,   4, 1,   3, 1 },
    { 3, 2,   4, 2,   4, 1,   4, 0 } },
  /* Shape: L (PAL_MAGENTA)
   *
   *       [3]   [0]                  [3][2]
   * [0](1)[2]   (1)      [2](1)[0]      (1)
   *             [2][3]   [3]            [0]
   */
  { { 3, 1,   4, 1,   5, 1,   5, 0 },
    { 4, 0,   4, 1,   4, 2,   5, 2 },
    { 5, 1,   4, 1,   3, 1,   3, 2 },
    { 4, 2,   4, 1,   4, 0,   3, 0 } },
  /* Shape: Z (PAL_ORANGE)
   *
   *                [0]   [3][2]         [3]
   * [0](1)      [2](1)      (1)[0]   (1)[2]
   *    [2][3]   [3]                  [0]
   */
  { { 3, 0,   4, 0,   4, 1,   5, 1 },
    { 4,-1,   4, 0,   3, 0,   3, 1 },
    { 5, 0,   4, 0,   4,-1,   3,-1 },
    { 4, 1,   4, 0,   5, 0,   5,-1 } },
  /* Shape: S (PAL_LIGHTBLUE)
   *
   *             [0]         [1][0]   [3]
   *    (2)[3]   [1](2)   [3](2)      (2)[1]
   * [0][1]         [3]                  [0]
   */
  { { 3, 1,   4, 1,   4, 0,   5, 0 },
    { 3,-1,   3, 0,   4, 0,   4, 1 },
    { 5,-1,   4,-1,   4, 0,   3, 0 },
    { 5, 1,   5, 0,   4, 0,   4,-1 } },
};



unsigned short pieces_list[PIECE_BUFFER_SIZE];



/* obtiene una nueva pieza */
static int get_new_piece(void)
{
  static int last = -1, last2 = -1;
  int n;

  n = rand()%MAX_PIECES;

  if ((n == last) && (n == last2)) {
    while (n == last)
      n = rand()%MAX_PIECES;
  }
  
  last2 = last;
  last  = n;

  if (game_mode == GAME_MODE_DESTROYER)
    return n | ((rand()%6) << 4);
  else
    return n;
}



/* resetea la lista de piezas */
void reset_pieces_list(void)
{
  int c;
  for (c=0; c<PIECE_BUFFER_SIZE; c++)
    pieces_list[c] = get_new_piece();
}



/* pasa a la pr¢xima pieza */
void next_piece(PLAYER *player)
{
  PLAYER *other = (player == &player1)? &player2: &player1;
  int c;

  /* 1 player */
  if (!(player2.flags & PLAYER_PLAYING)) {
    for (c=0; c<PIECE_BUFFER_SIZE-1; c++)
      pieces_list[c] = pieces_list[c+1];

    pieces_list[PIECE_BUFFER_SIZE-1] = get_new_piece();

    player->piece.shape = pieces_list[player->piece.index = 0];
  }
  /* 2 players */
  else {
    if (player->piece.index >= other->piece.index)
      player->piece.shape = pieces_list[++player->piece.index];
    else {
      for (c=0; c<PIECE_BUFFER_SIZE-1; c++)
	pieces_list[c] = pieces_list[c+1];

      pieces_list[PIECE_BUFFER_SIZE-1] = get_new_piece();

      other->piece.index--;
      player->piece.shape = pieces_list[player->piece.index];
    }
  }

  get_start_piece_pos(player);
}



/* obtiene la posici¢n de donde debe comenzar la pieza actual */
void get_start_piece_pos(PLAYER *player)
{
  player->piece.x   = 0;
  player->piece.y   = -BLOCK_SIZE;
  player->piece.rot = 0;
}



/* obtiene la posici¢n y las caracter¡sticas de cada bloque de la pieza;
   asign ndole cada valor a las variables "player->bx", "player->by" y
   a "player->block" */
void get_piece_blocks(PLAYER *player)
{
  int c, *piece = &pieces[player->piece.shape & 0x0f][player->piece.rot][0];
  int num = (player->piece.shape & 0xf0) >> 4;
  int piece_y = (int)floor(player->piece.y);

  for (c=0; c<4; c++) {
    player->piece.block[c] = ((player->piece.shape & 0x0f)+1);
      
    if (game_mode == GAME_MODE_DESTROYER) {
      if ((num == c) || (num == 4))
	player->piece.block[c] |= BLOCK_SPECIAL; // | (player->piece.shape & 0xf00);
    }

    player->piece.bx[c] = player->piece.x + piece[c*2  ]*BLOCK_SIZE;
    player->piece.by[c] =	  piece_y + piece[c*2+1]*BLOCK_SIZE;
  }
}



/* obtiene el tama¤o y la posici¢n de la pieza actual del jugador (en pixels) */
void get_piece_metrics(struct PLAYER *player, int *x, int *y, int *w, int *h)
{
  int xmax, ymax;
  int xmin, ymin;
  int c, piece_y = (int)floor(player->piece.y);
  
  /* encontrar los bloques que esten en los extremos */
  xmax = player->piece.x;
  ymax =	 piece_y;
  xmin = player->piece.x+PANEL_WIDTH *BLOCK_SIZE;
  ymin =	 piece_y+PANEL_HEIGHT*BLOCK_SIZE;
  for (c=0; c<4; c++) {
    if (xmax < player->piece.bx[c])
	xmax = player->piece.bx[c];
    if (xmin > player->piece.bx[c])
	xmin = player->piece.bx[c];
    if (ymax < player->piece.by[c])
	ymax = player->piece.by[c];
    if (ymin > player->piece.by[c])
	ymin = player->piece.by[c];
  }

  /* posici¢n de la pieza (relativa a player->px, player->py) */
  if (x) *x = xmin;
  if (y) *y = ymin;

  /* calcular el tama¤o de la pieza */
  if (w) *w = xmax - xmin + BLOCK_SIZE;
  if (h) *h = ymax - ymin + BLOCK_SIZE;
}



/* crea un bitmap con la pieza actual */
BITMAP *create_piece_bitmap(PLAYER *player, int *xout, int *yout)
{
  BITMAP *bmp;
  int c, x, y, w, h;

  get_piece_blocks(player);
  get_piece_metrics(player, &x, &y, &w, &h);

  /* crear el bitmap */
  bmp = create_bitmap(w, h);
  if (!bmp)
    return NULL;

  /* limpiar el bitmap con el color m scara actual */
  clear_to_color(bmp, bitmap_mask_color(bmp));

  /* dibujar cada bloque de la pieza en el bitmap */
  for (c=0; c<4; c++)
    draw_block(bmp, player->piece.bx[c]-x,
		    player->piece.by[c]-y, player->piece.block[c], FALSE);

  /* posiciones absolutas de la pieza;
     si se usa draw_sprite() con estas posiciones, el bitmap se
     dibujar  en el mismo sitio donde est  la pieza actual */
  if (xout) *xout = player->px+x;
  if (yout) *yout = player->py+y;

  return bmp;
}




