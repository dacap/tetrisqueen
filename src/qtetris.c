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

#include <stdio.h>

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <allegro.h>

#include "qtetris.h"
#include "hallfame.h"
#include "block.h"
#include "control.h"
#include "player.h"
#include "intro.h"
#include "menu.h"
#include "graphics.h"
#include "data.h"



DATAFILE *datafile = NULL;

BITMAP *virtual = NULL;

volatile int game_clock = 0;
volatile int speed_counter = 0;

int digi_volume = 0;
int midi_volume = 0;
int last_music = 0;

int game_mode;



static int see_intro = TRUE;

static int game_clock_stack;
static int speed_counter_stack;



static void increment_game_clock(void)
{
  game_clock++;
}

END_OF_STATIC_FUNCTION(increment_game_clock);



static void increment_speed_counter(void)
{
  speed_counter++;
}

END_OF_STATIC_FUNCTION(increment_speed_counter);



void push_clock()
{
  game_clock_stack = game_clock;
  speed_counter_stack = speed_counter;
}



void pop_clock()
{
  game_clock = game_clock_stack;
  speed_counter = speed_counter_stack;
}



void update_volume(void)
{
  if (!midi_volume)
    stop_midi();

  set_volume(255, 255 * midi_volume / MAX_VOLUME);
}


  
void play(int id, int pan_x, int vol)
{
  if (digi_driver->id != DIGI_NONE) {
    if (digi_volume > 0)
      play_sample(datafile[id].dat,
        vol * digi_volume / MAX_VOLUME,
        255 * pan_x / (GAME_SCREEN_W-1),
        1000, FALSE);
  }
}



void play_music(int id, int loop)
{
  last_music = id;

  if (midi_volume > 0)
    play_midi((MIDI *)datafile[id].dat, loop);
  else
    stop_midi();
}



void flip_to_screen(void)
{
  /* blit the virtual bitmap to the screen */
  if ((GAME_SCREEN_W == SCREEN_W) && (GAME_SCREEN_H == SCREEN_H))
    blit(virtual, screen, 0, 0, 0, 0, GAME_SCREEN_W, GAME_SCREEN_H);
  else
    stretch_blit(virtual, screen,
      0, 0, GAME_SCREEN_W, GAME_SCREEN_H,
      0, 0, SCREEN_W, SCREEN_H);
}



static void usage(char *name, int status)
{
  if (!status) {
    fprintf(stdout, "\
%s, Copyright (C) %s, by %s\n\
\n\
Usage:\n\
  %s [OPTIONS]\n\
\n\
Options:\n\
  -r, --resolution WIDTH HEIGHT   use a special resolution (in 8 bpp)\n\
  -i, --nointro                   doesn't display the introduction\n\
  -s, --nosound                   doesn't install sounds\n\
  -j, --nojoy                     doesn't install joystick\n\
  -m, --merge HOF_FILE            add the hall of fame and exit\n\
  -h, --help                      display this help and exit\n\
      --version                   output version information and exit\n\
\n\
Report bugs to <%s>.\n\
", GAME_NAME, GAME_DATE, AUTHOR_NAME, name, AUTHOR_EMAIL);
  }
  else {
    fprintf(stderr, "Try `%s --help' for more information.\n", name);
  }

  exit(status);
}



void qtetris_init(int argc, char *argv[])
{
  int sound = TRUE;
  int joystick = TRUE;
  char buf[256], path[256];
  int i, w, h;

  w = 320;
  h = 240;

  for (i=1; i<argc; i++) {
    if ((stricmp(argv[i], "-r") == 0) || (stricmp(argv[i], "--resolution") == 0)) {
      if (i+2 >= argc) {
        fprintf(stderr, "%s: `%s' need two extra parameters\n", argv[0], argv[i]);
        usage(argv[0], 1);
      }
      else {
        w = strtol(argv[++i], (char **)NULL, 10);
        h = strtol(argv[++i], (char **)NULL, 10);
      }
    }
    else if ((stricmp(argv[i], "-i") == 0) || (stricmp(argv[i], "--nointro") == 0))
      see_intro = FALSE;
    else if ((stricmp(argv[i], "-s") == 0) || (stricmp(argv[i], "--nosound") == 0))
      sound = FALSE;
    else if ((stricmp(argv[i], "-j") == 0) || (stricmp(argv[i], "--nojoy") == 0))
      joystick = FALSE;
    else if ((stricmp(argv[i], "-m") == 0) || (stricmp(argv[i], "--merge") == 0)) {
      if (i+1 >= argc) {
        fprintf(stderr, "%s: `%s' need one extra parameter\n", argv[0], argv[i]);
        usage(argv[0], 1);
      }
      else {
        char *filename = argv[++i];
        fprintf(stdout, "Merging `%s'...\n", filename);

        allegro_init();
        get_executable_name(path, sizeof(path));
        replace_filename(hof_file, path, "qtetris.hof", sizeof(hof_file));
        load_records();

        if (merge_records(filename) != 0) {
          fprintf(stdout, "Error!\n");
          exit(1);
        }
        else {
          save_records();
          fprintf(stdout, "Done!\n");
          exit(0);
        }
      }
    }
    else if ((stricmp(argv[i], "-?") == 0) ||
             (stricmp(argv[i], "-h") == 0) ||    
             (stricmp(argv[i], "--help") == 0)) {
      usage(argv[0], 0);
    }
    else if (stricmp(argv[i], "--version") == 0) {
      fprintf(stdout, "%s %s\n", GAME_NAME, GAME_VERSION);
      exit(0);
    }
    else {
      fprintf(stderr, "%s: unrecognized option `%s'\n", argv[0], argv[i]);
      usage(argv[0], 1);
    }
  }

  srand(time(NULL));

  allegro_init();
  set_window_title(GAME_NAME);

  get_executable_name(path, sizeof(path));
  set_config_file(replace_filename(buf, path, "qtetris.cfg", sizeof(buf)));

  /* set the graphics mode */
  set_color_depth(8);
  if (set_gfx_mode(GFX_AUTODETECT, w, h, 0, 0) < 0) {
    allegro_message("Error setting %dx%d 8 bpp display mode:\n%s\n", w, h, allegro_error);
    exit(1);
  }

  text_mode(-1);
  textout(screen, font, GAME_NAME ": loading...", 0, 0, makecol(255, 255, 255));

  install_timer();
  install_keyboard();

  if (joystick)
    install_joystick(JOY_TYPE_AUTODETECT);

  /* install the sound handler */
  if (sound)
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

  if (digi_driver->id == DIGI_NONE)
    digi_volume = 0;
  else
    digi_volume = get_config_int("qtetris", "digi_volume", MAX_VOLUME);

  if (midi_driver->id == MIDI_NONE)
    midi_volume = 0;
  else
    midi_volume = get_config_int("qtetris", "midi_volume", MAX_VOLUME);

  digi_volume = MID(0, digi_volume, MAX_VOLUME);
  midi_volume = MID(0, midi_volume, MAX_VOLUME);

  update_volume();

  /* install some stuff of the game */
  LOCK_VARIABLE(game_clock);
  LOCK_VARIABLE(speed_counter);
  LOCK_FUNCTION(increment_game_clock);
  LOCK_FUNCTION(increment_speed_counter);

  install_int_ex(increment_game_clock, BPS_TO_TIMER(TICKS_PER_SEC));
  install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));

  /* load the game records */
  get_executable_name(path, sizeof(path));
  replace_filename(hof_file, path, "qtetris.hof", sizeof(hof_file));

  load_records();

  /* load the main data file */
  get_executable_name(path, sizeof(path));
  datafile = load_datafile(replace_filename(buf, path, "qtetris.dat", sizeof(buf)));
  if (!datafile) {
    allegro_exit();
    allegro_message("Error loading data file `qtetris.dat'...\n");
    exit(1);
  }

  load_midi_patches();

  clear(screen);
  create_color_maps();
  sel_palette(NULL);

  /* the main virtual screen (for double-buffered) */
  virtual = create_bitmap(GAME_SCREEN_W, GAME_SCREEN_H);

  /* player names */
  strcpy(player1.name, "ABC");
  strcpy(player2.name, "ABC");

  /* get controls configuration */
  get_player_control(&player1, "player1", KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_DEL, KEY_END);
  get_player_control(&player2, "player2", KEY_A, KEY_D, KEY_S, KEY_1, KEY_2);
}



void qtetris_main(void)
{
  /* the player want see the intro? */
  if (see_intro)
    play_intro();

  /* execute the main menu loop */
  play_menu();
}



void qtetris_exit(void)
{
  /* save the actual configuration */
  if (digi_driver->id != DIGI_NONE)
    set_config_int("qtetris", "digi_volume", digi_volume);

  if (midi_driver->id != MIDI_NONE)
    set_config_int("qtetris", "midi_volume", midi_volume);

  save_player_control(&player1, "player1");
  save_player_control(&player2, "player2");

  /* free all memory */
  destroy_bitmap(virtual);
  destroy_color_maps();

  if (datafile)
    unload_datafile(datafile);

  /* clear the screen */
  clear(screen);

  /* set to the standard text mode */
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

  /* print a simple copyright message */
  allegro_message(
    GAME_NAME " - Version " GAME_VERSION "\n"
    "Copyright (C) " GAME_DATE " by David A. Capello <" AUTHOR_EMAIL ">\n\n"
    "This game is FREEWARE (totaly free), and you can update from:\n"
    "Este juego es FREEWARE (totalmente gratuito), y lo puede actualizar desde:\n\n"
    GAME_URL "\n\n");
}


