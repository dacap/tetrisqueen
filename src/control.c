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

#include <allegro.h>

#include "control.h"
#include "player.h"



/* guarda la informaci¢n del control de un jugador */
void save_player_control(PLAYER *player, char *section)
{
  set_config_int(section, "left",      player->control.left);
  set_config_int(section, "right",     player->control.right);
  set_config_int(section, "down",      player->control.down);
  set_config_int(section, "rot_left",  player->control.rot_left);
  set_config_int(section, "rot_right", player->control.rot_right);
}



/* obtiene la configuraci¢n de los controles de un jugador */
void get_player_control(PLAYER *player, char *section,
  int left, int right, int down, int rot_left, int rot_right)
{
  left      = get_config_int(section, "left", left);
  right     = get_config_int(section, "right", right);
  down      = get_config_int(section, "down", down);
  rot_left  = get_config_int(section, "rot_left", rot_left);
  rot_right = get_config_int(section, "rot_right", rot_right);

  player->control.left      = MID(CONTROL_FIRST, left,      CONTROL_LAST);
  player->control.right     = MID(CONTROL_FIRST, right,     CONTROL_LAST);
  player->control.down      = MID(CONTROL_FIRST, down,      CONTROL_LAST);
  player->control.rot_left  = MID(CONTROL_FIRST, rot_left,  CONTROL_LAST);
  player->control.rot_right = MID(CONTROL_FIRST, rot_right, CONTROL_LAST);
}



/* obtiene el estado del `control' correspondiente */
int get_control_state(int control)
{
  if ((control >= CONTROL_KEY_FIRST) && (control <= CONTROL_KEY_LAST))
    return key[control];
  else {
    int state;

    switch (control) {
      case CONTROL_JOY_LEFT:   state = joy[0].stick[0].axis[0].d1; break;
      case CONTROL_JOY_RIGHT:  state = joy[0].stick[0].axis[0].d2; break;
      case CONTROL_JOY_UP:     state = joy[0].stick[0].axis[1].d1; break;
      case CONTROL_JOY_DOWN:   state = joy[0].stick[0].axis[1].d2; break;
      case CONTROL_JOY_B1:     state = joy[0].button[0].b;         break;
      case CONTROL_JOY_B2:     state = joy[0].button[1].b;         break;
      case CONTROL_JOY2_LEFT:  state = joy[1].stick[0].axis[0].d1; break;
      case CONTROL_JOY2_RIGHT: state = joy[1].stick[0].axis[0].d2; break;
      case CONTROL_JOY2_UP:    state = joy[1].stick[0].axis[1].d1; break;
      case CONTROL_JOY2_DOWN:  state = joy[1].stick[0].axis[1].d2; break;
      case CONTROL_JOY2_B1:    state = joy[1].button[0].b;         break;
      case CONTROL_JOY2_B2:    state = joy[1].button[1].b;         break;
      default:                 state = FALSE;                      break;
    }

    return state;
  }
}



/* obtiene el nombre del `control' correspondiente */
char *get_control_name(int control)
{
static char *key_name[] =
{
  "NULL",
  "KEY A",
  "KEY B",
  "KEY C",
  "KEY D",
  "KEY E",
  "KEY F",
  "KEY G",
  "KEY H",
  "KEY I",
  "KEY J",
  "KEY K",
  "KEY L",
  "KEY M",
  "KEY N",
  "KEY O",
  "KEY P",
  "KEY Q",
  "KEY R",
  "KEY S",
  "KEY T",
  "KEY U",
  "KEY V",
  "KEY W",
  "KEY X",
  "KEY Y",
  "KEY Z",
  "KEY 0",
  "KEY 1",
  "KEY 2",
  "KEY 3",
  "KEY 4",
  "KEY 5",
  "KEY 6",
  "KEY 7",
  "KEY 8",
  "KEY 9",
  "KEY 0 PAD",
  "KEY 1 PAD",
  "KEY 2 PAD",
  "KEY 3 PAD",
  "KEY 4 PAD",
  "KEY 5 PAD",
  "KEY 6 PAD",
  "KEY 7 PAD",
  "KEY 8 PAD",
  "KEY 9 PAD",
  "KEY F1",
  "KEY F2",
  "KEY F3",
  "KEY F4",
  "KEY F5",
  "KEY F6",
  "KEY F7",
  "KEY F8",
  "KEY F9",
  "KEY F10",
  "KEY F11",
  "KEY F12",
  "KEY ESC",
  "KEY TILDE",
  "KEY MINUS",
  "KEY EQUALS",
  "KEY BACKSPACE",
  "KEY TAB",
  "KEY OPENBRACE",
  "KEY CLOSEBRACE",
  "KEY ENTER",
  "KEY COLON",
  "KEY QUOTE",
  "KEY BACKSLASH",
  "KEY BACKSLASH2",
  "KEY COMMA",
  "KEY STOP",
  "KEY SLASH",
  "KEY SPACE",
  "KEY INSERT",
  "KEY DEL",
  "KEY HOME",
  "KEY END",
  "KEY PGUP",
  "KEY PGDN",
  "KEY LEFT",
  "KEY RIGHT",
  "KEY UP",
  "KEY DOWN",
  "KEY SLASH PAD",
  "KEY ASTERISK",
  "KEY MINUS PAD",
  "KEY PLUS PAD",
  "KEY DEL PAD",
  "KEY ENTER PAD",
  "KEY PRTSCR",
  "KEY PAUSE",
  "KEY KEY_ABNT_C1",
  "KEY YEN",
  "KEY_KANA",
  "KEY_CONVERT",
  "KEY_NOCONVERT",
  "KEY_AT",
  "KEY_CIRCUMFLEX",
  "KEY_COLON2",
  "KEY_KANJI",

/*"KEY MODIFIERS",*/

  "KEY LSHIFT",
  "KEY RSHIFT",
  "KEY LCONTROL",
  "KEY RCONTROL",
  "KEY ALT",
  "KEY ALTGR",
/* NO!
  "KEY LWIN",
  "KEY RWIN",
  "KEY MENU",
  "KEY SCRLOCK",
  "KEY NUMLOCK",
  "KEY CAPSLOCK",
*/
};

  if ((control >= CONTROL_KEY_FIRST) && (control <= CONTROL_KEY_LAST))
    return key_name[control];
  else {
    char *name;

    switch (control) {
      case CONTROL_JOY_LEFT:   name = "JOY1 LEFT";    break;
      case CONTROL_JOY_RIGHT:  name = "JOY1 RIGHT";   break;
      case CONTROL_JOY_UP:     name = "JOY1 UP";      break;
      case CONTROL_JOY_DOWN:   name = "JOY1 DOWN";    break;
      case CONTROL_JOY_B1:     name = "JOY1 BUTTON1"; break;
      case CONTROL_JOY_B2:     name = "JOY1 BUTTON2"; break;
      case CONTROL_JOY2_LEFT:  name = "JOY2 LEFT";    break;
      case CONTROL_JOY2_RIGHT: name = "JOY2 RIGHT";   break;
      case CONTROL_JOY2_UP:    name = "JOY2 UP";      break;
      case CONTROL_JOY2_DOWN:  name = "JOY2 DOWN";    break;
      case CONTROL_JOY2_B1:    name = "JOY2 BUTTON1"; break;
      case CONTROL_JOY2_B2:    name = "JOY2 BUTTON2"; break;
      default:                 name = "";             break;
    }

    return name;
  }
}


