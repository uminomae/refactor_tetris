#include "tetris.h"
#include "tetrimino.h"

void get_type_tetrimino(t_tetrimino *type){

	t_tetrimino type_tetlimino[7]= {
		{
			S_FIGURE
		},
		{
			Z_FIGURE
		},
		{
			T_FIGURE
		},
		{
			L_FIGURE
		},
		{
			J_FIGURE
		},
		{
			O_FIGURE
		},
		{
			I_FIGURE
		}
	};
	type = type_tetlimino;
}


//--------------------------------------------------------
//init_game
//--------------------------------------------------------

static void init_struct_tetris(t_tetris *tetris){
	tetris->score = 0;
	tetris->game_status = GAME_PLAY;
	tetris->time_to_update = FALL_VELOCITY_INTERVAL;
	tetris->decrease = INTERVAL_DECREASE;
	get_type_tetrimino(tetris->type);
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

