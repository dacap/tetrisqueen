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

#ifndef TETRIS_H
#define TETRIS_H



#define GAME_NAME		"TETRIS Queen"
#define GAME_VERSION		"1.3.1"
#define GAME_DATE		"1999 - 2001"
#define GAME_URL		"http://qtetris.sourceforge.net/"

#define AUTHOR_NAME		"David A. Capello"
#define AUTHOR_EMAIL		"davidcapello@yahoo.com"
#define AUTHOR_URL		"http://www.davidcapello.com.ar/"

#define GAME_MODE_CLASSIC	0
#define GAME_MODE_DESTROYER	1

#define TICKS_PER_SEC		1000

#define TIMEOUT(time, limit)	(((game_clock) - (time)) > (limit))

#define ALBUM_MAX		24 /* 0 - 23 */
#define ALBUM_BMP(n)		((BITMAP *)(((DATAFILE *)datafile[BGBMP_DAT].dat)[(n)].dat))
#define ALBUM_PAL(n)		((RGB    *)(((DATAFILE *)datafile[BGPAL_DAT].dat)[(n)].dat))
#define ALBUM_W			170
#define ALBUM_H			170

#define MAX_VOLUME		100


extern DATAFILE *datafile;

extern BITMAP *virtual;

extern volatile int game_clock;
extern volatile int speed_counter;

extern int digi_volume;
extern int midi_volume;
extern int last_music;

extern int game_mode;



void push_clock();
void pop_clock();

void update_volume(void);
void play(int id, int pan_x, int vol);
void play_music(int id, int loop);

void flip_to_screen(void);



#endif /* #ifndef TETRIS_H */

