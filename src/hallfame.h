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

#ifndef HALLFAME_H
#define HALLFAME_H



struct PLAYER *player;



extern char hof_file[256];


int load_records(void);
int save_records(void);
void reset_high_scores(int game_mode);

int make_a_new_record(struct PLAYER *player, int game_mode);
void add_new_record(struct PLAYER *player, int game_mode);

int merge_records(const char *filename);

int play_hall_of_fame(void);



#endif /* #ifndef HALLFAME_H */

