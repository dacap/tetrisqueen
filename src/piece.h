/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
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
