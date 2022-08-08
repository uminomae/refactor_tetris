#include "tetris.h"

void print_header(){
	for(int i = 0; i < FIELD_COL - 9; i++)
		print_string_to_window(" ");
	print_string_to_window("42 Tetris\n");
}

void print_game_field(t_tetris *tetris, \
						char Buffer[FIELD_ROW][FIELD_COL]){
	for(int i = 0; i < FIELD_ROW ;i++){
		for(int j = 0; j < FIELD_COL ; j++){
			if (tetris->playing_field[i][j] + Buffer[i][j])
				print_string_to_window("%c ", '#');
			else
				print_string_to_window("%c ", '.');
		}
		print_string_to_window("\n");
	}
}

void print_footer(t_tetris *tetris){
	print_string_to_window("\nScore: %d\n", tetris->score);
}

void print_game_screen(t_tetris *tetris, \
						char Buffer[FIELD_ROW][FIELD_COL]){
	print_header();
	print_game_field(tetris, Buffer);
	print_footer(tetris);
}

void get_current_position(t_tetris *tetris, \
							char Buffer[FIELD_ROW][FIELD_COL]){
	const int n = tetris->tetrimino->width_and_height;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(tetris->tetrimino->figure[i][j])
				Buffer[tetris->tetrimino->row+i][tetris->tetrimino->col+j] = tetris->tetrimino->figure[i][j];
		}
	}
}
