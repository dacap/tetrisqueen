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

#ifndef CONTROL_H
#define CONTROL_H



struct PLAYER;



#define CONTROL_FIRST		CONTROL_KEY_FIRST
#define CONTROL_KEY_FIRST	KEY_A
#define CONTROL_KEY_LAST	KEY_ALTGR
#define CONTROL_OTHER		CONTROL_KEY_LAST
#define CONTROL_JOY_LEFT	(CONTROL_OTHER+1)
#define CONTROL_JOY_RIGHT	(CONTROL_OTHER+2)
#define CONTROL_JOY_UP		(CONTROL_OTHER+3)
#define CONTROL_JOY_DOWN	(CONTROL_OTHER+4)
#define CONTROL_JOY_B1		(CONTROL_OTHER+5)
#define CONTROL_JOY_B2		(CONTROL_OTHER+6)
#define CONTROL_JOY2_LEFT	(CONTROL_OTHER+7)
#define CONTROL_JOY2_RIGHT	(CONTROL_OTHER+8)
#define CONTROL_JOY2_UP		(CONTROL_OTHER+9)
#define CONTROL_JOY2_DOWN	(CONTROL_OTHER+10)
#define CONTROL_JOY2_B1		(CONTROL_OTHER+11)
#define CONTROL_JOY2_B2		(CONTROL_OTHER+12)
#define CONTROL_LAST		CONTROL_JOY2_B2



void save_player_control(struct PLAYER *player, char *section);

void get_player_control(struct PLAYER *player, char *section,
  int left, int right, int down, int rot_left, int rot_right);
  
int get_control_state(int control);
char *get_control_name(int control);



#endif /* #ifndef CONTROL_H */

