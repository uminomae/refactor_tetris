#include "tetris.h"
#include "tetrimino.h"

//--------------------------------------------------------
//init_game
//--------------------------------------------------------

static void init_struct_tetris(t_tetris *tetris){
	tetris->score = 0;
	tetris->game_status = GAME_PLAY;
	tetris->time_to_update = FALL_VELOCITY_INTERVAL;
	tetris->decrease = INTERVAL_DECREASE;
	tetris->type = type_tetrimino;
	memset(tetris->playing_field, 0, sizeof(char) * FIELD_ROW * FIELD_COL);
	tetris->input_from_keyboard = 0;
}

static void set_timeout_millisecond(int time) {
	timeout(time);
}

void init_game(t_tetris *tetris)
{
	
	srand(time(0));
	init_struct_tetris(tetris);
	gettimeofday(&tetris->time->before_now, NULL);
	set_timeout_millisecond(1);
}

//--------------------------------------------------------
//end of init_game
//--------------------------------------------------------

void init_ncurses_window(){
	initscr();
}
