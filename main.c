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
		if (tetris->input_from_keyboard != ERR) 
			move_tetrimino(tetris, &tetrimino, false);
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



// 19:26 構造体を実体でやるスタイルに変更直後
//void begin_game(t_tetris *tetris){
//	//tetris->tetrimino = create_new_tetrimino(tetris->type);
//	judge_the_end_of_game(tetris);
//    //refresh_game_screen(tetris, tetris->tetrimino);
////}
//void finish_game(t_tetris *tetris)
//{
//	//destroy_tetrimino(tetris->tetrimino);
//	finish_ncurses();
//	print_resulting_to_standard_output(tetris);
//}