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

#ifndef PLAYER_H
#define PLAYER_H

#include "block.h"
#include "piece.h"



#define PANEL_WIDTH             10
#define PANEL_HEIGHT            24

#define PLAYER_PLAYING          0x0001
#define PLAYER_OVER             0x0002
#define PLAYER_MENU             00004
#define PLAYER_NORMAL           0x0008
#define PLAYER_LEFT             0x0010
#define PLAYER_RIGHT            0x0020
#define PLAYER_ROTATION_LEFT    0x0040
#define PLAYER_ROTATION_RIGHT   0x0080
#define PLAYER_PREPUTPIECE      0x0100
#define PLAYER_PUTPIECE         0x0200
#define PLAYER_PANELDOWN        0x0400
#define PLAYER_FINISH           0x0800
#define PLAYER_RECORD           0x1000
#define PLAYER_WAITING          0x2000

#define SCORE_SINGLE            10
#define SCORE_DOUBLE            50
#define SCORE_TRIPLE            200
#define SCORE_TETRIS            500
#define SCORE_BOMB              10
#define SCORE_MEGABOMB          50



typedef struct PLAYER
{
  char name[3];                 /* iniciales del jugador */
  int name_pos;                 /* usado en PLAYER_RECORD */
  BLOCK panel[PANEL_HEIGHT][PANEL_WIDTH];
  int flags;                    /* propiedades */
  int score, lines, level;      /* puntaje */
  int level_lines;
  int px, py;                   /* posición del panel */
  int block_type;               /* tipo de bloque */
  int winner;                   /* indica si jugador ganó o perdió */

  struct {
    int left, right, down;
    int rot_left, rot_right;
  } control;

  struct {
    int left, right, down;
    int rot_left, rot_right;
  } state;

  struct {
    int index;                  /* índice de la pieza en la lista */
    int shape;                  /* tipo de pieza (ver: <piece.c> "pieces[]" ) */
    int x, dx;                  /* posición */
    float y;
    int rot;                    /* rotación */
    BLOCK block[4];             /* color y forma de los bloques */
    int bx[4], by[4];           /* posición de cada bloque */
    BITMAP *bmp;                /* bitmap temporario para hacer... */
    int bmp_x, bmp_y;           /* ...diferentes animaciones */
  } piece;                      /* pieza actual */

  unsigned char killines[4], kill;

  int fast_move;
  int down_start;
  int putpiece_time;
  int key_time;
  int rot_time;
  int rot_ani_time;
  int ani_time;
} PLAYER;


extern PLAYER player1, player2;

extern int main_menu_option;
extern int lineup_time;
extern int lines_counter;


int player_death(PLAYER *player);

int move_player(PLAYER *player);
void draw_player(BITMAP *bmp, PLAYER *player);



#endif /* #ifndef PLAYER_H */

