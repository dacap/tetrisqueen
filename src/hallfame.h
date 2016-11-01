/* TETRIS Queen
 * Copyright (C) 1999, 2000, 2001  David Capello
 *
 * This file is released under the terms of the MIT license.
 * Read LICENSE.txt for more information.
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
