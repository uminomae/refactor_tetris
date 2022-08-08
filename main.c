#include "tetris.h"
#include "tetrimino.h"

//t_tetrimino current;

int main() {
	t_tetris tetris;

	//printf("a--main----\n");
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

	printf("b--begin----\n");
	tetris->tetrimino = create_new_tetrimino(type_tetrimino);
	if(!can_move_field(tetris, tetris->tetrimino)){
		tetris->game_status = GAME_OVER;
	}
    refresh_game_screen(tetris, tetris->tetrimino);
}

int get_char_input_from_keyboad(t_tetris *tetris){
	tetris->input_from_keyboard = getch();
}

void run_game(t_tetris *tetris){
	while(tetris->game_status == GAME_PLAY){
		get_char_input_from_keyboad(tetris);
    	//tetris->input_from_keyboard = getch();
		printf("e--if need----\n");
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