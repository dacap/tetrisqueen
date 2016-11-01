/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#include <stdlib.h>
#include <allegro.h>
#include <allegro/aintern.h>

#include "handle.h"
#include "qtetris.h"
#include "graphics.h"
#include "data.h"



GAMEOBJ *gameobj_list = NULL;
GAMEOBJ *active_gameobj = NULL;

int fadeout_start = 0;


static int update_list = FALSE;


static int qsort_game_list(const void *e1, const void *e2)
{
  GAMEOBJ *o1 = *(GAMEOBJ **)e1;
  GAMEOBJ *o2 = *(GAMEOBJ **)e2;
  return (o1->priority - o2->priority);
}



static void resort_gameobj_list(void)
{
  GAMEOBJ *pos;

  if ((gameobj_list) && (gameobj_list->next)) {
    GAMEOBJ **list;
    int c = 0, num = 0;

    pos = gameobj_list;
    while (pos) {
      num++;
      pos = pos->next;
    }

    list = malloc(sizeof(GAMEOBJ *) * num);
    pos = gameobj_list;
    while (pos) {
      list[c++] = pos;
      pos = pos->next;
    }

    qsort(list, num, sizeof(GAMEOBJ *), qsort_game_list);

    gameobj_list = pos = list[0];
    for (c=1; c<num; c++) {
      pos->next = list[c];
      pos = pos->next;
    }
    pos->next = NULL;

    free(list);
  }
}



int handle_init(void)
{
  return 0;
}



void handle_exit(void)
{
}



static int fadeout_a_frame(void)
{
  PALETTE pal;
  int c, r, g, b;

  if (_digi_volume > 0) _digi_volume = MAX(0, _digi_volume-8);
  if (_midi_volume > 0) _midi_volume = MAX(0, _midi_volume-8);
  set_volume(_digi_volume, _midi_volume);

  qtetris_push_clock();
  get_palette(pal);
  for (c=0; c<PAL_SIZE; c++) {
    r = pal[c].r - 2;
    g = pal[c].g - 2;
    b = pal[c].b - 2;
    pal[c].r = MAX(0, r);
    pal[c].g = MAX(0, g);
    pal[c].b = MAX(0, b);
  }
  set_palette(pal);
  qtetris_pop_clock();

  if ((game_clock - fadeout_start) > TPS/2) {
    fadeout_start = 0;
    qtetris_push_clock();
    clear(screen);
    qtetris_clear_keybuf();
    stop_midi();
    qtetris_update_volume();
    qtetris_pop_clock();
    return -1;
  }

  return 0;
}



void handle_game(void)
{
  GAMEOBJ *pos, *next;
  GAMEOBJ *old_gameobj = active_gameobj;
  int game_over = FALSE;

  resort_gameobj_list();

  qtetris_clear_keybuf();

  fadeout_start = 0;
  speed_counter = 0;

  while (!game_over) {
    while ((speed_counter > 0) && !(game_over)) {
      poll_keyboard();
      poll_joystick();

      /* abortar el juego */
      if (key[KEY_Q] && (key_shifts & KB_CTRL_FLAG)) {
        exit(1);
      }

      /* pausa */
      if (key[KEY_F11]) {
        static char pause[] = "- PAUSE -";
        FONT *f = (FONT *)datafile[FONTBIG_PCX].dat;
        int x = SCREEN_W/2;
        int y = SCREEN_H/2-text_height(f)/2;

        qtetris_push_clock();

        qtetris_clear_keybuf();

        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        color_map = trans_dark_map;
        rectfill(screen, 0, 0, SCREEN_W-1, SCREEN_H-1, makecol(0, 0, 0));
        solid_mode();

        text_mode(-1);
        textout_centre(screen, f, pause, x-1, y, 0);
        textout_centre(screen, f, pause, x+1, y, 0);
        textout_centre(screen, f, pause, x, y-1, 0);
        textout_centre(screen, f, pause, x, y+1, 0);
        textout_centre(screen, f, pause, x, y, -1);

        do {
          poll_keyboard();
        } while (!keypressed());

        qtetris_clear_keybuf();

        qtetris_pop_clock();
      }

      /* capturar la pantalla */
      if (key[KEY_F12]) {
        qtetris_push_clock();

        capture_screen();

        do {
          poll_keyboard();
        } while (key[KEY_F12]);

        qtetris_pop_clock();
      }

      /* realizar un fundido de la pantalla */
      if (fadeout_start)
        game_over = fadeout_a_frame();

      /* mover los objetos */
      pos = gameobj_list;
      while ((pos) && !(game_over)) {
        next = pos->next;
        active_gameobj = pos;
        game_over = pos->move(pos->data);
        pos = next;
      }

      speed_counter--;
    }

    if (update_list) {
      resort_gameobj_list();
      update_list = FALSE;
    }

    /* borrar la pantalla virtual */
    clear(virtual);

    /* dibujar los objetos en la pantalla virtual */
    pos = gameobj_list;
    while (pos) {
      active_gameobj = pos;
      pos->draw(pos->data);
      pos = pos->next;
    }

    /* pasar todo lo dibujado a la pantalla */
    qtetris_blit(virtual);
  }

  active_gameobj = old_gameobj;
  qtetris_clear_keybuf();
}



GAMEOBJ *create_gameobj(void *move, void *draw, void *data)
{
  GAMEOBJ *obj;

  obj = malloc(sizeof(GAMEOBJ));

  obj->priority = 0;
  obj->move = move;
  obj->draw = draw;
  obj->data = data;
  obj->next = NULL;

  return obj;
}



void add_gameobj(int priority, GAMEOBJ *obj)
{
  if (obj) {
    obj->priority = priority;
    obj->next = gameobj_list;
    gameobj_list = obj;
  }
}



void del_gameobj(GAMEOBJ *obj)
{
  GAMEOBJ *pos, *prev;

  prev = NULL;
  pos = gameobj_list;
  while (pos) {
    if (pos == obj) {
      if (!prev)
        gameobj_list = pos->next;
      else
        prev->next = pos->next;

      if (pos == active_gameobj)
        active_gameobj = NULL;

      free(pos->data);
      free(pos);
      break;
    }
    prev = pos;
    pos = pos->next;
  }
}



void delete_gameobj_list(void)
{
  GAMEOBJ *pos, *next;

  pos = gameobj_list;
  while (pos) {
    next = pos->next;
    free(pos->data);
    free(pos);
    pos = next;
  }
  gameobj_list = NULL;
}



void update_gameobj_list(void)
{
  update_list = TRUE;
}
