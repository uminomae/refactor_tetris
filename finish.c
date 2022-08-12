#include "tetris.h"

static void	finish_ncurses(void){
	endwin();
}

//--------------------------------------------------------
//print_resulting_to_standard_output
//--------------------------------------------------------

static void	print_field_result(t_tetris *tetris){
	for (int y = 0; y < FIELD_Y_ROW; y++){
		for (int x = 0; x < FIELD_X_COL; x++){
			if (tetris->playing_field[y][x])
				printf("%c ", '#');
			else
				printf("%c ", '.');
		}
		printf("\n");
	}
}

static void	print_result_footer(t_tetris *tetris){
	printf("\nGame over!\n");
	printf("\nScore: %d\n", tetris->score);
}

void	print_resulting_to_standard_output(t_tetris *tetris){
	print_field_result(tetris);
	print_result_footer(tetris);
}

//--------------------------------------------------------
//
//--------------------------------------------------------

void	finish_game(t_tetris *tetris, t_tetrimino *current)
{
	//destroy_tetrimino_dubble_pointer(&current);
	destroy_tetrimino(*current);
	finish_ncurses();
	print_resulting_to_standard_output(tetris);
}
