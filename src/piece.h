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

#ifndef PIECE_H
#define PIECE_H



struct PLAYER;



#define MAX_PIECES              7

#define PIECE_BUFFER_SIZE       0x8000

#define ROT_0                   0
#define ROT_90                  1
#define ROT_180                 2
#define ROT_270                 3



extern int pieces[MAX_PIECES][4][8];
extern unsigned short pieces_list[PIECE_BUFFER_SIZE];



void reset_pieces_list(void);
void next_piece(struct PLAYER *player);

void get_start_piece_pos(struct PLAYER *player);
void get_piece_blocks(struct PLAYER *player);
void get_piece_metrics(struct PLAYER *player, int *x, int *y, int *w, int *h);

BITMAP *create_piece_bitmap(struct PLAYER *player, int *xout, int *yout);



#endif /* #ifndef PIECE_H */

