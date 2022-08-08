#include "tetris.h"

void finish_ncurses(){
	endwin();
}

//--------------------------------------------------------
//print_resulting_to_standard_output
//--------------------------------------------------------

static void print_field_result(t_tetris *tetris){
	for(int i = 0; i < FIELD_ROW ;i++){
		for(int j = 0; j < FIELD_COL ; j++){
			if (tetris->playing_field[i][j])
				printf("%c ", '#');
			else
				printf("%c ", '.');
		}
		printf("\n");
	}
}

static void print_result_footer(t_tetris *tetris){
	printf("\nGame over!\n");
	printf("\nScore: %d\n", tetris->score);
}

void print_resulting_to_standard_output(t_tetris *tetris){
	print_field_result(tetris);
	print_result_footer(tetris);
}

//--------------------------------------------------------
//end of print_resulting_to_standard_output
//--------------------------------------------------------