/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#include <allegro.h>
#include "qtetris.h"



int main(int argc, char *argv[])
{
  qtetris_init(argc, argv);
  qtetris_main();
  qtetris_exit();
  return 0;
}

END_OF_MAIN();
