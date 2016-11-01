/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#ifndef QTETRIS_H
#define QTETRIS_H



/* game information */
#define QTETRIS_NAME                "TETRIS Queen"
#define QTETRIS_VERSION             "1.4"
#define QTETRIS_DATE                "1999 - 2001"
#define QTETRIS_HOSTED              "http://qtetris.sourceforge.net/"

/* author information */
#define QTETRIS_AUTHOR_NAME         "David A. Capello"
#define QTETRIS_AUTHOR_ADDRESS      "davidcapello@gmail.com"
#define QTETRIS_AUTHOR_WWW          "http://davidcapello.com/"

/* game modes */
#define QTETRIS_MODE_CLASSIC        0
#define QTETRIS_MODE_DESTROYER      1

/* virtual screen size */
#define QTETRIS_SCREEN_W            320
#define QTETRIS_SCREEN_H            240

/* number of levels */
#define QTETRIS_LEVELS              50

/* game speed */
#define FPS                         60    /* frames per second */
#define TPS                         1000  /* ticks per second */

/* animation control */
#define TIMEOUT(time, limit)        (((game_clock) - (time)) > (limit))

/* musics */
#define MUSIC_FIRST                 MUSIC01_MID
#define MUSIC_LAST                  MUSIC34_MID
#define MUSIC_INTRO                 MUSIC20_MID
#define MUSIC_MENU                  MUSIC_INTRO
#define MUSIC_FINAL                 MUSIC02_MID
#define MUSIC_HOF                   MUSIC17_MID
#define MUSIC_CREDITS               MUSIC19_MID

/* albums */
#define ALBUM_FIRST                 BGBMP_DAT_BG00_PCX
#define ALBUM_LAST                  BGBMP_DAT_BG23_PCX
#define ALBUM_CREDITS               BGBMP_DAT_BG23_PCX
#define ALBUM_BMP(n)                ((BITMAP *)(((DATAFILE *)datafile[BGBMP_DAT].dat)[(n)].dat))
#define ALBUM_PAL(n)                ((RGB    *)(((DATAFILE *)datafile[BGPAL_DAT].dat)[(n)].dat))
#define ALBUM_W                     170
#define ALBUM_H                     170

/* maximun volume value */
#define MAX_VOLUME                  100



extern DATAFILE *datafile;

extern BITMAP *virtual;

extern volatile int game_clock;
extern volatile int speed_counter;

extern int digi_volume;
extern int midi_volume;
extern int last_music;

extern int game_mode;



void qtetris_push_clock();
void qtetris_pop_clock();

void qtetris_update_volume(void);
void qtetris_sound(int id, int pan_x, int vol);
void qtetris_music(int id, int loop);

void qtetris_blit(BITMAP *bmp);
void qtetris_clear_keybuf(void);

void qtetris_init(int argc, char *argv[]);
void qtetris_main(void);
void qtetris_exit(void);



#endif /* #ifndef QTETRIS_H */
