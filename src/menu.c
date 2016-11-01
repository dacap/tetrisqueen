/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include <allegro/aintern.h>

#include "menu.h"
#include "qtetris.h"
#include "hallfame.h"
#include "credits.h"
#include "player.h"
#include "control.h"
#include "playgame.h"
#include "graphics.h"
#include "handle.h"
#include "data.h"



static int game_over;
static int ani_time;
static int selected;
static int player_selected;

static int background_pos = 0;

static MENU *menu, *old_menu[128];
static int menu_counter = 0;

static char sound_str[32];
static char music_str[32];

static char control_str[5][64];



static int back_proc(void);
static int exit_proc(void);
static int options_start(void);
static int controls_update(void);
static int controls_calibrate(void);
static int reconfig_control(void);
static int test_sound_proc(void);
static int select_player_proc(void);
static int play_proc(void);



static MENU sound_test_menu[] =
{
  { "LEFT",             test_sound_proc,        NULL,           0,      (void *)1 },
  { "CENTRE",           test_sound_proc,        NULL,           0,      (void *)2 },
  { "RIGHT",            test_sound_proc,        NULL,           0,      (void *)3 },
  { "FLIP PAN",         test_sound_proc,        NULL,           0,      (void *)4 },
  { "BACK",             back_proc,              NULL,           0,      NULL },
  { NULL,               NULL,                   NULL,           0,      NULL }
};



static MENU controls_config_menu[] =
{
  { control_str[0],     reconfig_control,       NULL,           0, (void *)1 },
  { control_str[1],     reconfig_control,       NULL,           0, (void *)2 },
  { control_str[2],     reconfig_control,       NULL,           0, (void *)3 },
  { control_str[3],     reconfig_control,       NULL,           0, (void *)4 },
  { control_str[4],     reconfig_control,       NULL,           0, (void *)5 },
  { "RESTORE",          reconfig_control,       NULL,           0, (void *)6 },
  { "DEFAUT",           reconfig_control,       NULL,           0, (void *)7 },
  { "BACK",             back_proc,              NULL,           0, NULL },
  { NULL,               NULL,                   NULL,           0, NULL }
};



static MENU controls_menu[] =
{
  { "PLAYER 1",         controls_update,        controls_config_menu,   0, (void *)1 },
  { "PLAYER 2",         controls_update,        controls_config_menu,   0, (void *)2 },
  { "CALIBRATE JOYSTICK",controls_calibrate,    NULL,                   0, NULL },
  { "BACK",             back_proc,              NULL,                   0, NULL },
  { NULL,               NULL,                   NULL,                   0, NULL }
};



static MENU game_mode_menu[] =
{
  { "CLASSIC",          play_proc,              NULL, 0, (void *)QTETRIS_MODE_CLASSIC },
  { "DESTROYER",        play_proc,              NULL, 0, (void *)QTETRIS_MODE_DESTROYER },
  { "BACK",             back_proc,              NULL, 0, NULL },
  { NULL,               NULL,                   NULL, 0, NULL }
};



static MENU options_menu[] =
{
  { sound_str,          NULL,                   NULL,           0, NULL },
  { music_str,          NULL,                   NULL,           0, NULL },
  { "SOUND TEST",       NULL,                   sound_test_menu,0, NULL },
  { "CONTROLS",         NULL,                   controls_menu,  0, NULL },
  { "RESET HIGH SCORES",select_player_proc,     game_mode_menu, 0, NULL },
  { "BACK",             back_proc,              NULL,           0, NULL },
  { NULL,               NULL,                   NULL,           0, NULL }
};



static MENU main_menu[] =
{
  { "1 PLAYER",         select_player_proc,     game_mode_menu,         0,              (void *)1 },
  { "2 PLAYERS",        select_player_proc,     game_mode_menu,         0,              (void *)2 },
  { "HALL OF FAME",     play_hall_of_fame,      NULL,                   D_INTERNAL,     NULL },
  { "OPTIONS",          options_start,          options_menu,           0,              NULL },
  { "CREDITS",          play_credits,           NULL,                   D_INTERNAL,     NULL },
  { "EXIT",             exit_proc,              NULL,                   0,              NULL },
  { NULL,               NULL,                   NULL,                   0,              NULL }
};



static int back_proc(void)
{
  return D_O_K;
}



static int exit_proc(void)
{
  return D_CLOSE;
}



static int options_start(void)
{
  char *s;
  int i, len;

  strcpy(sound_str, "SOUND: ");
  strcpy(music_str, "MUSIC: ");

  s = sound_str + strlen(sound_str);
  if (digi_volume) {
    len = 20 * digi_volume / MAX_VOLUME;
    for (i=0; i<len; i++) {
      *s = 'l';
      s++;
      *s = 0;
    }
  }
  else {
    strcpy(s, "OFF");
  }

  s = music_str + strlen(music_str);
  if (midi_volume) {
    len = 20 * midi_volume / MAX_VOLUME;
    for (i=0; i<len; i++) {
      *s = 'l';
      s++;
      *s = 0;
    }
  }
  else {
    strcpy(s, "OFF");
  }

  return D_O_K;
}



static PLAYER *player_s;



static int controls_update(void)
{
  if (active_menu->dp)
    player_s = (((int)active_menu->dp) == 1)? &player1: &player2;

  sprintf(control_str[0], "LEFT: %s",       get_control_name(player_s->control.left));
  sprintf(control_str[1], "RIGHT: %s",      get_control_name(player_s->control.right));
  sprintf(control_str[2], "DOWN: %s",       get_control_name(player_s->control.down));
  sprintf(control_str[3], "ROT. LEFT: %s",  get_control_name(player_s->control.rot_left));
  sprintf(control_str[4], "ROT. RIGHT: %s", get_control_name(player_s->control.rot_right));

  return D_O_K;
}



static int controls_calibrate(void)
{
  AL_CONST char *msg;
  int i;

  remove_joystick();
  install_joystick(JOY_TYPE_AUTODETECT);

  for (i=0; i<2 && i<num_joysticks; i++) {
    while (joy[i].flags & JOYFLAG_CALIBRATE) {
      msg = calibrate_joystick_name(i);

      clear(screen);

      text_mode(-1);
      textprintf_centre(screen, datafile[FONTGAME_PCX].dat, SCREEN_W/2, 48, -1,
        "Calibrating joystick %d", i+1);

      textout_centre(screen, datafile[FONTGAME_PCX].dat, msg, SCREEN_W/2, 64, -1);
      textout_centre(screen, datafile[FONTGAME_PCX].dat, "and press a key.", SCREEN_W/2, 80, -1);

      if ((readkey() & 0xFF) == 27)
        return D_O_K;

      if (calibrate_joystick(i) != 0) {
        textout_centre(screen, datafile[FONTGAME_PCX].dat,
          "Error calibrating joystick!", SCREEN_W/2, 96, -1);
        readkey();
        return D_O_K;
      }
    }
  }

  return D_O_K;
}



static int reconfig_control(void)
{
  int code = (int)active_menu->dp;
  int *control = NULL;
  int i, new_control;

  switch (code) {
    case 1: control = &player_s->control.left;          break;
    case 2: control = &player_s->control.right;         break;
    case 3: control = &player_s->control.down;          break;
    case 4: control = &player_s->control.rot_left;      break;
    case 5: control = &player_s->control.rot_right;     break;

    /* RESTORE */
    case 6:
      if (player_s == &player1)
        get_player_control(&player1, "player1", KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_DEL, KEY_END);
      else
        get_player_control(&player1, "player2", KEY_A, KEY_D, KEY_S, KEY_1, KEY_2);
      break;

    /* DEFAULT */
    case 7:
      if (player_s == &player1) {
        player1.control.left      = KEY_LEFT;
        player1.control.right     = KEY_RIGHT;
        player1.control.down      = KEY_DOWN;
        player1.control.rot_left  = KEY_DEL;
        player1.control.rot_right = KEY_END;
      }
      else {
        player2.control.left      = KEY_A;
        player2.control.right     = KEY_D;
        player2.control.down      = KEY_S;
        player2.control.rot_left  = KEY_1;
        player2.control.rot_right = KEY_2;
      }
      break;

    default:
      return D_O_K;
  }

  if (control) {
    qtetris_clear_keybuf();

    new_control = -1;
    while (new_control < 0) {
      poll_keyboard();
      poll_joystick();
      for (i=CONTROL_FIRST; i<=CONTROL_LAST; i++) {
        if (get_control_state(i)) {
          new_control = i;
          break;
        }
      }
    }
    *control = new_control;

    qtetris_clear_keybuf();
  }

  active_menu->dp = NULL;
  controls_update();
  active_menu->dp = (void *)code;
  return D_O_K;
}



static int test_sound_proc(void)
{
  switch ((int)active_menu->dp) {

    case 1:
      qtetris_sound(MENUSEL_WAV, 0, 255);
      break;

    case 2:
      qtetris_sound(MENUSEL_WAV, QTETRIS_SCREEN_W/2, 255);
      break;

    case 3:
      qtetris_sound(MENUSEL_WAV, QTETRIS_SCREEN_W-1, 255);
      break;

    case 4:
      if (!_sound_flip_pan)
        _sound_flip_pan = TRUE;
      else
        _sound_flip_pan = FALSE;
      break;
  }

  return D_O_K;
}



static int select_player_proc(void)
{
  player_selected = selected;
  return D_O_K;
}



static int play_proc(void)
{
  game_mode = (int)active_menu->dp;

  player1.flags = PLAYER_PLAYING;

  /* 1 PLAYER */
  if (player_selected == 0) {
    player2.flags = 0;

    player1.px = BLOCK_SIZE*15;
  }
  /* 2 PLAYERS */
  else if (player_selected == 1) {
    player2.flags = PLAYER_PLAYING;

    player1.px = BLOCK_SIZE*2;
    player2.px = QTETRIS_SCREEN_W-BLOCK_SIZE*PANEL_WIDTH-BLOCK_SIZE*2;
  }
  /* RESET HIGH SCORES */
  else {
    reset_high_scores(game_mode);
    return D_O_K;
  }

  player1.py =
  player2.py = BLOCK_SIZE*3;

  play_game();
  return D_O_K;
}



static int move(void *null)
{
  int max;
  int scan = 0;

  (void)null;

  /* si la música para, comenzar nuevamente */
  if (midi_pos < 0) {
    qtetris_push_clock();
    qtetris_music(MUSIC_MENU, FALSE);
    qtetris_pop_clock();
  }

  if (keypressed())
    scan = (readkey() >> 8);

  background_pos++;

  if (!TIMEOUT(ani_time, TPS*2))
    return 0;

  if (!fadeout_start) {
    /* UP: mover la selección del menú hacia arriba */
    if ((scan == KEY_UP) || (scan == KEY_8_PAD)) {
      for (max=0; menu[max].text; max++);
      max--;

      if (selected>0)
        selected--;
      else
        selected = max;

      qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
    }
    /* DOWN: bajar la selección del menú */
    else if ((scan == KEY_DOWN) || (scan == KEY_2_PAD)) {
      for (max=0; menu[max].text; max++);
      max--;

      if (selected<max)
        selected++;
      else
        selected = 0;

      qtetris_sound(MENUSET_WAV, QTETRIS_SCREEN_W/2, 255);
    }
    /* ENTER: seleccionar una opción */
    else if ((scan == KEY_ENTER) || (scan == KEY_ENTER_PAD) || (scan == KEY_SPACE)) {
      int ret = D_O_K;

      active_menu = &menu[selected];

      if ((menu[selected].proc != test_sound_proc) || (((int)active_menu->dp) == 4))
        qtetris_sound(MENUSEL_WAV, QTETRIS_SCREEN_W/2, 255);

      if (menu[selected].proc) {
        /* para la música MIDI */
        if (menu[selected].flags & D_INTERNAL)
          stop_midi();

        /* llamar el proceso */
        ret |= menu[selected].proc();
        qtetris_clear_keybuf();

        /* restaurar la paleta de colores y la música */
        if (menu[selected].flags & D_INTERNAL) {
          qtetris_push_clock();
          sel_palette(NULL);
          qtetris_pop_clock();
        }

        /* si el proceso es back_proc, significa que se quiere
           volver al menú anterior */
        if (menu[selected].proc == back_proc) {
          for (max=0; menu[max].text; max++);
          max--;
          selected = (int)menu[max].dp;
          menu = old_menu[--menu_counter];
          return 0;
        }
      }

      if (menu[selected].child) {
        /* seleccionar el menú hijo */
        old_menu[menu_counter++] = menu;
        menu = menu[selected].child;

        for (max=0; menu[max].text; max++);
        max--;
        menu[max].dp = (void *)selected;
        selected = 0;
      }

      if (ret & D_CLOSE)
        fadeout_start = game_clock;
    }
    /* LEFT & RIGHT: cambiar el volumen */
    else if ((scan == KEY_LEFT)  || (scan == KEY_RIGHT) ||
             (scan == KEY_4_PAD) || (scan == KEY_6_PAD)) {
      if ((menu[selected].text == sound_str) ||
          (menu[selected].text == music_str)) {
        int value = 0;

        if ((scan == KEY_LEFT)  || (scan == KEY_4_PAD)) value--;
        if ((scan == KEY_RIGHT) || (scan == KEY_6_PAD)) value++;

        /* el volumen fué cambiado? */
        if (value) {
          /* actualizar la barra de volumen */
          char *s = strchr(menu[selected].text, ' ')+1;
          int i, l = strlen(s);

          if (*s == 'O') /* OFF */
            l = 0;

          l = MID(0, l+value, 20);

          if (l) {
            for (i=0; i<l; i++)
              s[i] = 'l';

            s[i] = 0;
          }
          else {
            strcpy(s, "OFF");
          }

          /* actualizar el volumen */
          /* DIGI */
          if (selected == 0)
            digi_volume = MAX_VOLUME*l/20;

          /* MIDI */
          if (selected == 1)
            midi_volume = MAX_VOLUME*l/20;

          qtetris_update_volume();
        }
      }
    }
    /* ESC: cancelar */
    else if (scan == KEY_ESC) {
      for (max=0; menu[max].text; max++);
      max--;

      /* salir */
      if (menu == main_menu) {
        selected = max;
        fadeout_start = game_clock;
      }
      /* volver */
      else {
        selected = (int)menu[max].dp;
        menu = old_menu[--menu_counter];
      }
    }
  }

  return 0;
}



static void menu_textout(BITMAP *bmp, char *text, int big, int x, int y, int sel)
{
  FONT *f = datafile[(big)? FONTBIG_PCX: FONTGAME_PCX].dat;
  BITMAP *sprite;
  char buf[2];
  int c;

  x -= text_length(f, text)/2;

  for (c=0; text[c]; c++) {
    buf[0] = text[c];
    buf[1] = 0;
    sprite = create_bitmap(text_length(f, buf), text_height(f));
    text_mode(0);
    textout(sprite, f, buf, 0, 0, -1);

    color_map = shadow_map;
    draw_trans_sprite(bmp, sprite, x+4, y+4);

    if (!big) {
      text_mode(-1);
      draw_character(bmp, sprite, x-1, y, 0);
      draw_character(bmp, sprite, x+1, y, 0);
      draw_character(bmp, sprite, x, y-1, 0);
      draw_character(bmp, sprite, x, y+1, 0);
    }

    if (!sel)
      draw_sprite(bmp, sprite, x, y);
    else {
      color_map = tint_dark_map;
      draw_lit_sprite(bmp, sprite, x, y, PAL_YELLOW);
    }

    x += sprite->w;
    destroy_bitmap(sprite);
  }
}



static void draw(void *null)
{
  int i, v;

  (void)null;

  /* background */
  drawing_mode(DRAW_MODE_COPY_PATTERN, datafile[TETRISBG_BMP].dat,
    background_pos/4, background_pos/6);
  rectfill(virtual, 0, 0, QTETRIS_SCREEN_W, QTETRIS_SCREEN_H, -1);
  solid_mode();

  /* tetris logo */
  v = 80;
  if (!TIMEOUT(ani_time, TPS))
    v = v * (game_clock - ani_time) / TPS;

  /* shadow */
  color_map = shadow_map;
  drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
  draw_trans_sprite(virtual, datafile[TETRIS_BMP].dat,
    QTETRIS_SCREEN_W/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->w/2 + 6,
    QTETRIS_SCREEN_H/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->h/2 - v + 12);
  solid_mode();

  /* solid */
  draw_sprite(virtual, datafile[TETRIS_BMP].dat,
    QTETRIS_SCREEN_W/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->w/2,
    QTETRIS_SCREEN_H/2 - ((BITMAP *)datafile[TETRIS_BMP].dat)->h/2 - v);

  /* queen logo */
  v = 128;
  if (!TIMEOUT(ani_time, TPS*3/2))
    v = v * (game_clock - ani_time) / (TPS*3/2);

  v = 128 - v;

  /* shadow */
  color_map = shadow_map;
  drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
  draw_trans_sprite(virtual, datafile[QUEENMNI_BMP].dat,
    QTETRIS_SCREEN_W/2-((BITMAP *)datafile[QUEENMNI_BMP].dat)->w/2+6, 48-v+12);
  solid_mode();

  /* solid */
  draw_sprite(virtual, datafile[QUEENMNI_BMP].dat,
    QTETRIS_SCREEN_W/2-((BITMAP *)datafile[QUEENMNI_BMP].dat)->w/2, 48-v);

  /* menú */
  v = QTETRIS_SCREEN_W;
  if (!TIMEOUT(ani_time, TPS*2))
    v = v * (game_clock - ani_time) / (TPS*2);

  v = QTETRIS_SCREEN_W - v;

  for (i=0; menu[i].text; i++) {
    menu_textout(virtual, menu[i].text, (menu != controls_config_menu),
      QTETRIS_SCREEN_W/2 + ((i&1)? -v:+v), QTETRIS_SCREEN_H/2-28+i*20, (!v && (selected == i)));
  }
}



/* ejecuta la pantalla principal del juego: los menús */
void play_menu(void)
{
  GAMEOBJ *old_list = gameobj_list;

  gameobj_list = NULL;

  sel_palette(NULL);

  game_over = FALSE;
  fadeout_start = 0;

  ani_time = game_clock;
  selected = 0;

  menu = main_menu;
  menu_counter = 0;

  add_gameobj(50, create_gameobj(move, draw, NULL));
  handle_game();
  delete_gameobj_list();
  gameobj_list = old_list;
}
