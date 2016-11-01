/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
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
