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

#ifndef HANDLE_H
#define HANDLE_H



typedef struct GAMEOBJ
{
  int priority;
  int (*move)(void *data);
  void (*draw)(void *data);
  void *data;
  struct GAMEOBJ *next;
} GAMEOBJ;


extern GAMEOBJ *gameobj_list;
extern GAMEOBJ *active_gameobj;

extern int fadeout_start;


int handle_init(void);
void handle_exit(void);

void handle_game(void);

GAMEOBJ *create_gameobj(void *move, void *draw, void *data);
void add_gameobj(int priority, GAMEOBJ *obj);
void del_gameobj(GAMEOBJ *obj);

void delete_gameobj_list(void);
void update_gameobj_list(void);



#endif /* #ifndef HANDLE_H */

