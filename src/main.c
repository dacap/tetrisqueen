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

#include <stdio.h>

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <allegro.h>

#include "tetris.h"
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



static int game_clock_stack;
static int speed_counter_stack;


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
      play_sample(datafile[id].dat, vol * digi_volume / MAX_VOLUME, 255 * pan_x / (SCREEN_W-1), 1000, FALSE);
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
  blit(virtual, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}



static void usage(void)
{
  char buf[256];

  get_executable_name(buf, 256);

  allegro_message(
    "\n" GAME_NAME " v" GAME_VERSION ", Copyright (C) " GAME_DATE ", by David A. Capello\n"
    "\n"
    "Use: %s [OPTIONS]\n"
    "\n"
    "Options:\n"
    "  -i, --nointro   doesn't display the introduction\n"
    "  -s, --nosound   doesn't install sounds\n"
    "  -j, --nojoy     doesn't install joystick\n"
    "  -?, --help      shows the program's help\n"
    "\nReport bugs to " AUTHOR_EMAIL ".\n", buf);
}



int main(int argc, char *argv[])
{
  int intro = TRUE;
  int sound = TRUE;
  int joystick = TRUE;
  char buf[256], path[256];
  int c;

  srand(time(NULL));

  allegro_init();
  set_window_title(GAME_NAME);

  for (c=1; c<argc; c++) {
    if ((stricmp(argv[c], "-i") == 0) || (stricmp(argv[c], "--nointro") == 0))
      intro = FALSE;

    if ((stricmp(argv[c], "-s") == 0) || (stricmp(argv[c], "--nosound") == 0))
      sound = FALSE;
      
    if ((stricmp(argv[c], "-j") == 0) || (stricmp(argv[c], "--nojoy") == 0))
      joystick = FALSE;

    if ((stricmp(argv[c], "-?") == 0) || (stricmp(argv[c], "--help") == 0)) {
      usage();
      return 0;
    }
  }

  get_executable_name(path, 256);
  set_config_file(replace_filename(buf, path, "qtetris.cfg", 256));

  /* cambiar el modo de video */
  set_color_depth(8);
  if (set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0) < 0) {
    allegro_message("Error setting 320x240 8 bpp display mode:\n%s\n", allegro_error);
    return 1;
  }

  text_mode(-1);
  textout(screen, font, "Loading...", 0, 0, makecol(255, 255, 255));

  install_timer();
  install_keyboard();

  if (joystick)
    install_joystick(JOY_TYPE_AUTODETECT);

  /* sonido */
  if (sound)
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

  if (digi_driver->id == DIGI_NONE)
    digi_volume = 0;
  else
    digi_volume = get_config_int("tetris", "digi_volume", MAX_VOLUME);

  if (midi_driver->id == MIDI_NONE)
    midi_volume = 0;
  else
    midi_volume = get_config_int("tetris", "midi_volume", MAX_VOLUME);

  digi_volume = MID(0, digi_volume, MAX_VOLUME);
  midi_volume = MID(0, midi_volume, MAX_VOLUME);

  update_volume();

  /* instalar las cosas del juego */
  LOCK_VARIABLE(game_clock);
  LOCK_VARIABLE(speed_counter);
  LOCK_FUNCTION(increment_game_clock);
  LOCK_FUNCTION(increment_speed_counter);

  install_int_ex(increment_game_clock, BPS_TO_TIMER(TICKS_PER_SEC));
  install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));

  /* cargar las puntuaciones del juego */
  get_executable_name(path, 256);
  replace_filename(hof_file, path, "qtetris.hof", 256);
  
  load_records();

  /* cargar los datos del juego */
  get_executable_name(path, 256);
  datafile = load_datafile(replace_filename(buf, path, "qtetris.dat", 256));
  if (!datafile) {
    allegro_exit();
    allegro_message("Error loading data file `qtetris.dat'...\n");
    return 1;
  }

  load_midi_patches();

  clear(screen);

  create_color_maps();
  sel_palette(NULL);

  virtual = create_bitmap(SCREEN_W, SCREEN_H);

  /* player names */
  strcpy(player1.name, "ABC");
  strcpy(player2.name, "ABC");

  /* controls */
  get_player_control(&player1, "player1",
    KEY_4_PAD, KEY_6_PAD, KEY_2_PAD, KEY_DEL, KEY_END);

  get_player_control(&player2, "player2",
    KEY_A, KEY_D, KEY_S, KEY_1, KEY_2);

  /* comenzar el juego */
  play_music(MUSIC20_MID, TRUE);

  if (intro)
    play_intro();

  play_menu();

  /* guardar la configuraci¢n actual */
  if (digi_driver->id != DIGI_NONE)
    set_config_int("tetris", "digi_volume", digi_volume);

  if (midi_driver->id != MIDI_NONE)
    set_config_int("tetris", "midi_volume", midi_volume);

  save_player_control(&player1, "player1");
  save_player_control(&player2, "player2");

  /* ok */
  destroy_bitmap(virtual);
  destroy_color_maps();

  if (datafile)
    unload_datafile(datafile);
  
  clear(screen);
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

  #ifndef DEBUGMODE

    allegro_message(
      "\n" GAME_NAME " - Version " GAME_VERSION "\n"
      "Copyright (C) " GAME_DATE ", by David A. Capello (" AUTHOR_EMAIL ")\n\n"
      "This game is FREEWARE (totaly free), and you can update from:\n"
      "Este juego es FREEWARE (totalmente gratuito), y lo puede actualizar desde:\n\n"
      GAME_URL "\n\n");

    #ifdef ALLEGRO_CONSOLE_OK

      clear_keybuf();
      readkey();

    #endif

  #endif
  return 0;
}

END_OF_MAIN();


