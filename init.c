# include "main.h"

//--------------------------------------------------------
//init_game
//--------------------------------------------------------

static void init_ncurses_window(){
	initscr();
}

static void init_struct_tetris(t_tetris *tetris){
	tetris->score = 0;
	tetris->game_status = IN_GAME;
	tetris->time_to_update = FALL_VELOCITY_INTERVAL;
	tetris->decrease = INTERVAL_DECREASE;
	memset(tetris->playing_field, 0, sizeof(char) * FIELD_Y_ROW * FIELD_X_COL);
	tetris->input_from_keyboard = 0;
}

//static void set_timeout_millisecond(int time) {
//	timeout(time);
//}

void init_game(t_tetris *tetris)
{
	srand(time(0));
	init_struct_tetris(tetris);
	//gettimeofday(&tetris->time->before_now, NULL);
	//set_timeout_millisecond(1);
	init_ncurses_window();
}

//--------------------------------------------------------
//end of init_game
//--------------------------------------------------------