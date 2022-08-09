#include "tetris.h"

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
	init_ncurses_window();
}

void run_game(t_tetris *tetris){
	t_tetrimino tetrimino = create_new_tetrimino(tetris->type);
	
	refresh_game_screen(tetris, &tetrimino);
	while(tetris->game_status == GAME_PLAY){
		get_char_from_keyboad(tetris);
		if (tetris->input_from_keyboard != ERR) {
			move_tetrimino(tetris, &tetrimino, false);
			//printw("b---\n%d\n",tetris->input_from_keyboard);
		}
	//printw("a---\n%d\n", getch());
		refresh_game_screen(tetris, &tetrimino);
		gettimeofday(&tetris->timer->now, NULL);
		if (need_update(tetris)) {
			tetris->input_from_keyboard = 's';
			move_tetrimino(tetris, &tetrimino, true);
			gettimeofday(&tetris->timer->before_now, NULL);
		}
	}
}

void finish_game(t_tetris *tetris)
{
	finish_ncurses();
	print_resulting_to_standard_output(tetris);
}

//--------------------------------------------------------
//end of sub
//--------------------------------------------------------
