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

#include "objects.h"
#include "tetris.h"
#include "handle.h"
#include "graphics.h"
#include "block.h"
#include "data.h"



#define MPI		3.14159265358979323846


#define MAX_STARS    1024



typedef struct STAR_OBJECT
{
  fixed x, y, z;
  int ox, oy;
} STAR_OBJECT;



static int move_stars(STAR_OBJECT *data)
{
  int c, x, y, ix, iy;

  for (c=0; c<MAX_STARS; c++) {
    if (data[c].z <= itofix(1)) {
      x = itofix(rand()&0xff);
      y = itofix(((rand()&3)+1)*SCREEN_W);

      data[c].x = fmul(fcos(x), y);
      data[c].y = fmul(fsin(x), y);
      data[c].z = itofix((rand() & 0x1f) + 1);
    }

    x = fdiv(data[c].x, data[c].z);
    y = fdiv(data[c].y, data[c].z);

    ix = (int)(x>>16) + SCREEN_W/2;
    iy = (int)(y>>16) + SCREEN_H/2;

    if ((ix >= 0) && (ix < SCREEN_W) && (iy >= 0) && (iy <= SCREEN_H)) {
      data[c].ox = ix;
      data[c].oy = iy;
      data[c].z -= 4096;
    }
    else {
      data[c].ox = -1;
      data[c].oy = -1;
      data[c].z = 0;
    }
  }
  
  return 0;
}



static void draw_stars(STAR_OBJECT *data)
{
  int c, c2;
  
  for (c=0; c<MAX_STARS; c++) {
    c2 = 15 - (int)(data[c].z>>17);
    putpixel(virtual, data[c].ox, data[c].oy, MID(0, c2, 15));
  }
}



GAMEOBJ *create_stars(void)
{
  STAR_OBJECT *data;
  int c;

  data = malloc(sizeof(STAR_OBJECT) * MAX_STARS);

  for (c=0; c<MAX_STARS; c++) {
    data[c].z = 0;
    data[c].ox = data[c].oy = -1;
  }
  
  return create_gameobj(move_stars, draw_stars, data);
}



typedef struct EXPLOSION_OBJECT
{
  int x, y, w, h;
  int explo_id;
  int time, ani_time;
} EXPLOSION_OBJECT;



static int move_explosion(EXPLOSION_OBJECT *data)
{
  if (TIMEOUT(data->ani_time, data->time))
    del_gameobj(active_gameobj);
    
  return 0;
}



static void draw_explosion(EXPLOSION_OBJECT *data)
{
  DATAFILE *explo = (DATAFILE *)datafile[data->explo_id].dat;
  int i = 63 * (game_clock - data->ani_time) / (data->time);

  i = MID(0, i, 63);

  stretch_sprite(virtual, (BITMAP *)explo[i].dat,
    data->x-data->w/2, data->y-data->h/2, data->w, data->h);
}



GAMEOBJ *create_explosion(int x, int y, int mega)
{
  EXPLOSION_OBJECT *data;
  
  data = malloc(sizeof(EXPLOSION_OBJECT));

  data->x = x;
  data->y = y;
  data->w = (!mega)? (rand()%64)+32: 192;
  data->h = (!mega)? (rand()%64)+32: 192;
  data->explo_id = rand()%4;
  data->explo_id = (data->explo_id == 0)? EXPLO1_DAT:
		   (data->explo_id == 1)? EXPLO2_DAT:
		   (data->explo_id == 2)? EXPLO3_DAT: EXPLO4_DAT;

  data->time = (!mega)?
    (rand()%(TICKS_PER_SEC/4)) + (TICKS_PER_SEC/4): (TICKS_PER_SEC*3/4);
  data->ani_time = game_clock;

  return create_gameobj(move_explosion, draw_explosion, data);
}



typedef struct LINETYPE_OBJECT
{
  int x, y;
  int lines;
  int ani_time;
} LINETYPE_OBJECT;



static int move_linetype(LINETYPE_OBJECT *data)
{
  if (TIMEOUT(data->ani_time, TICKS_PER_SEC))
    del_gameobj(active_gameobj);
    
  return 0;
}



static void draw_linetype(LINETYPE_OBJECT *data)
{
  int c, x, y, w, h;
  BITMAP *sprite = (data->lines == 2)? datafile[LDOUBLE_BMP].dat:
		   (data->lines == 3)? datafile[LTRIPLE_BMP].dat:
		   (data->lines == 4)? datafile[LTETRIS_BMP].dat: NULL;

  /* dibujar el sprite */
  if (sprite) {
    float scale;
      
    /* calcular la posici¢n del bitmap */
    x = data->x;
    y = data->y;

    /* tiempo que lleva el sprite en pantalla */
    c = (game_clock - data->ani_time);

    /* dibujar el sprite agrand ndose */
    if (c <= (TICKS_PER_SEC/8)) {
      scale = 2.0 * c / (TICKS_PER_SEC/8);

      w = scale * sprite->w;
      h = scale * sprite->h;
      stretch_sprite(virtual, sprite, x - w/2, y - h/2, w, h);
    }
    /* dibujar el sprite achic ndose al tama¤o normal */
    else {
      c -= TICKS_PER_SEC/8;
      if (c <= (TICKS_PER_SEC/8)) {
	scale = 2.0 - 1.0 * c / (TICKS_PER_SEC/8);

	w = scale * sprite->w;
	h = scale * sprite->h;
	stretch_sprite(virtual, sprite, x - w/2, y - h/2, w, h);
      }
      /* dibujar el sprite quieto un rato */
      else {
	c -= TICKS_PER_SEC/8;
	if (c <= (TICKS_PER_SEC/3)) {
	  draw_sprite(virtual, sprite, x - sprite->w/2, y - sprite->h/2);
	}
	/* dibujar el sprite aplast ndose */
	else {
	  c -= TICKS_PER_SEC/3;
	  if (c <= (TICKS_PER_SEC/4)) {
	    scale = 1.0 * c / (TICKS_PER_SEC/4);

	    w = (1.0 + scale) * sprite->w;
	    h = (1.0 - scale) * sprite->h;
	    stretch_sprite(virtual, sprite, x - w/2, y - h/2, w, h);
	  }
	}
      }
    }
  }
}



GAMEOBJ *create_linetype(int x, int y, int lines)
{
  LINETYPE_OBJECT *data;
  
  data = malloc(sizeof(LINETYPE_OBJECT));

  data->x = x;
  data->y = y;
  data->lines = lines;
  data->ani_time = game_clock;

  return create_gameobj(move_linetype, draw_linetype, data);
}



typedef struct FLYBLOCK_OBJECT
{
  int x, y;
  int startx;
  int starty;
  BLOCK block;
  float speed;
  float angle;
  float draw_angle;
  float scale;
  int ani_time;
} FLYBLOCK_OBJECT;


#define WIND	((float)0.0)
#define WEIGHT	((float)60.0)


static int calculate_flyblock_pos(FLYBLOCK_OBJECT *data)
{
  float time = ((float)2.5) * (float)(game_clock - data->ani_time) / (float)(TICKS_PER_SEC);
  float x, y;

  x = (data->speed * cos(MPI*data->angle/(float)(180.0)) * time) + ((float)(0.5) * WIND   * time * time);
  y = (data->speed * sin(MPI*data->angle/(float)(180.0)) * time) - ((float)(0.5) * WEIGHT * time * time);

  data->x = ((int) (x)+data->startx);
  data->y = ((int)-(y)+data->starty);

  if ((data->x < -BLOCK_SIZE) || (data->x >= SCREEN_W) || (data->y >= SCREEN_H))
    return -1;

  return 0;
}



static int move_flyblock(FLYBLOCK_OBJECT *data)
{
  if (calculate_flyblock_pos(data) != 0)
    del_gameobj(active_gameobj);

  data->draw_angle += SGN(data->x - SCREEN_W/2) * ((data->speed) / (float)(10.0));
    
  return 0;
}



static void draw_flyblock(FLYBLOCK_OBJECT *data)
{
  fixed scale = itofix(1) +
    ftofix(0.5) * (game_clock - data->ani_time) / TICKS_PER_SEC;
  
  draw_block(block_bmp, 0, 0, data->block, TRUE);

  scale -= ftofix(0.25) * ABS(data->x - SCREEN_W/2) / (SCREEN_W/2);
  scale += ftofix(data->scale);

  rotate_scaled_sprite(virtual, block_bmp, data->x, data->y,
    ftofix(data->draw_angle), scale);
}



GAMEOBJ *create_flyblock(int x, int y, BLOCK block, int super_speed)
{
  FLYBLOCK_OBJECT *data;
  
  data = malloc(sizeof(FLYBLOCK_OBJECT));

  data->startx = x;
  data->starty = y;
  data->block  = block;

  data->angle  = ((float)(rand()%900) / (float)(10.0)) + (float)(45.0);
  
  data->speed  = (super_speed)? (float)(100.0):
    ((float)(rand()%200) / (float)(10.0)) +
			   (float)(40.0) + ABS(data->angle - (float)(90.0));
  data->draw_angle = (float)0.0;
  data->scale  = ((float)(rand()%200) / (float)(1000.0)) - (float)(0.1);
  data->ani_time = game_clock;

  calculate_flyblock_pos(data);

  return create_gameobj(move_flyblock, draw_flyblock, data);
}

