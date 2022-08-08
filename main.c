#include "tetris.h"
//#include "tetrimino.h"

//t_tetrimino current;

int main() {
	t_tetris tetris;

	begin_game(&tetris);
	run_game(&tetris);
	finish_game(&tetris);
    return (0);
}

//--------------------------------------------------------
//sub
//--------------------------------------------------------

void begin_game(t_tetris *tetris){
	init_game(tetris);
	tetris->tetrimino = create_new_tetrimino(tetris->type);
	judge_the_end_of_game(tetris);
	printf("b2--begin----\n");
    refresh_game_screen(tetris, tetris->tetrimino);
}

//void get_char_input_from_keyboad(t_tetris *tetris){
//	tetris->input_from_keyboard = getch();
//}

void run_game(t_tetris *tetris){
		printf("e--if need----\n");
	while(tetris->game_status == GAME_PLAY){
		get_char_input_from_keyboad(tetris);
		if (tetris->input_from_keyboard != ERR) 
			move_tetrimino_with_key(tetris, tetris->tetrimino, false);
		gettimeofday(&tetris->time->now, NULL);
		if (need_update(tetris)) {
			tetris->input_from_keyboard = 's';
			move_tetrimino_with_key(tetris, tetris->tetrimino, true);
			gettimeofday(&tetris->time->before_now, NULL);
		}
	}
}

void finish_game(t_tetris *tetris)
{
	destroy_tetrimino(tetris->tetrimino);
	finish_ncurses();
	print_resulting_to_standard_output(tetris);
}

//--------------------------------------------------------
//end of sub
//--------------------------------------------------------