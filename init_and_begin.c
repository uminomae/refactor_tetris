#include "tetris.h"
#include "type.h"

const t_tetrimino type_tetrimino[7]= {
	//
	// S
	// 
	//   # # 
	// # #   
	//       
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	//
	// Z
	// # #
	//   # # 
	//
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	//
	// T
	// # # #
	//   # 
	//
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	//
	// L
	//     #
	// # # # 
	//
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	//
	// J
	// #
	// # # # 
	//
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	//
	// O
	// # #
	// # #
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	//
	// I
	// 
	// # # # #
	//
	//
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};


void	begin_game(t_tetris *tetris, t_tetrimino *current, t_tetrimino *type){
	*current = create_new_tetrimino(type);
	judge_the_end_of_game(tetris, *current);
	refresh_game_screen(tetris, current);
}

//--------------------------------------------------------
//init_game
//--------------------------------------------------------

static void	init_struct_tetris(t_tetris *tetris){
	tetris->score = 0;
	tetris->game_status = IN_GAME;
	tetris->time_to_update = FALL_VELOCITY_INTERVAL;
	tetris->decrease = INTERVAL_DECREASE;
	memset(tetris->playing_field, 0, sizeof(char) * FIELD_Y_ROW * FIELD_X_COL);
	tetris->input_from_keyboard = 0;
}

static void	init_ncurses_window(void){
	initscr();
}

static void	set_timeout_millisecond(int time_ms){
	timeout(time_ms);
}

void	init_game(t_tetris *tetris, t_tetrimino *type, t_time *timer){
	srand(time(0));
	init_struct_tetris(tetris);
	init_ncurses_window();
	gettimeofday(&timer->before_now, NULL);
	set_timeout_millisecond(1);
	memcpy(type, type_tetrimino, sizeof(t_tetrimino[7]) * 1);
}
//--------------------------------------------------------
//
//--------------------------------------------------------
