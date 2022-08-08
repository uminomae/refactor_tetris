#include "tetris.h"
#include "tetrimino.h"

t_tetrimino current;

int main() {
	t_tetris tetris;

	begin_game(&tetris);
	run_game(&tetris);
	finish_game(&tetris, current);
    return (0);
}

//--------------------------------------------------------
//sub
//--------------------------------------------------------

void begin_game(t_tetris *tetris){
	init_game(tetris);
	current = create_new_tetrimino(type_tetrimino);
	if(!can_move_field(tetris, &current)){
		tetris->game_status = GAME_OVER;
	}
    refresh_game_screen(tetris, &current);
}

void run_game(t_tetris *tetris){
	while(tetris->game_status == GAME_PLAY){
    	tetris->input_from_keyboard = getch();
		if (tetris->input_from_keyboard != ERR) 
			move_tetrimino_with_key(tetris, &current, false);
		gettimeofday(&now, NULL);
		if (need_update(tetris)) {
			tetris->input_from_keyboard = 's';
			move_tetrimino_with_key(tetris, &current, true);
			gettimeofday(&before_now, NULL);
		}
	}
}

void finish_game(t_tetris *tetris, t_tetrimino current)
{
	destroy_tetrimino(&current);
	finish_ncurses();
	print_resulting_to_standard_output(tetris);
}

//--------------------------------------------------------
//end of sub
//--------------------------------------------------------