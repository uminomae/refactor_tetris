#include "tetris.h"

void print_header(){
	for(int i = 0; i < FIELD_COL - 9; i++)
		print_string_to_window(" ");
	print_string_to_window("42 Tetris\n");
}

void print_game_field(t_tetris *tetris, \
						char buffer[FIELD_ROW][FIELD_COL]){
	for(int i = 0; i < FIELD_ROW ;i++){
		for(int j = 0; j < FIELD_COL ; j++){
			if (tetris->playing_field[i][j] + buffer[i][j])
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
						char buffer[FIELD_ROW][FIELD_COL]){
	print_header();
	print_game_field(tetris, buffer);
	print_footer(tetris);
}

void get_current_position(t_tetris *tetris, \
							char buffer[FIELD_ROW][FIELD_COL]){
	const int n = tetris->tetrimino->width_and_height;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(tetris->tetrimino->figure[i][j])
				buffer[tetris->tetrimino->row+i][tetris->tetrimino->col+j] = tetris->tetrimino->figure[i][j];
		}
	}
}

//void refresh_game_screen(t_tetris *tetris){
//	char next_playing_field[FIELD_ROW][FIELD_COL] = {0};
	
//	tetris->tetrimino = &current;
//	get_current_position(tetris, next_playing_field);
//	clear();
//	print_game_screen(tetris, next_playing_field);
//}