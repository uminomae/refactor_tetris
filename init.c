#include "tetris.h"
#include "tetrimino.h"

void init_ncurses_window(){
	initscr();
}

void init_type_tetrimino(t_tetrimino *type){
	t_tetrimino type_tetlimino[] = {
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

static void init_struct_tetris(t_tetris **tetris){
	const size_t type_size = sizeof(char) * ONE_SIDE_SQUARE_MAX * ONE_SIDE_SQUARE_MAX + sizeof(int) * 3;
	const size_t field_size = sizeof(char) * FIELD_ROW * FIELD_COL;
	
	(*tetris)->score = 0;
	(*tetris)->game_status = GAME_PLAY;
	(*tetris)->time_to_update = FALL_VELOCITY_INTERVAL;
	(*tetris)->decrease = INTERVAL_DECREASE;
	init_type_tetrimino((*tetris)->type);
	memset(&(*tetris)->type, 0, type_size);
	memset((*tetris)->playing_field, 0, field_size);
	(*tetris)->input_from_keyboard = 0;
}

static void set_timeout_millisecond(int time) {
	timeout(time);
}

void init_game(t_tetris *tetris)
{
	t_time timer;
	
	srand(time(NULL));
	init_struct_tetris(&tetris);
	gettimeofday(&timer.before_now, NULL);
	tetris->timer = &timer;
	set_timeout_millisecond(1);
}

//--------------------------------------------------------
//end of init_game
//--------------------------------------------------------


