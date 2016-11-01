/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "block.h"



struct GAMEOBJ;


struct GAMEOBJ *create_stars(void);
struct GAMEOBJ *create_explosion(int x, int y, int mega);
struct GAMEOBJ *create_linetype(int x, int y, int lines);
struct GAMEOBJ *create_flyblock(int x, int y, BLOCK block, int super_speed);



#endif /* #ifndef OBJECTS_H */
