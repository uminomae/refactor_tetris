#include "tetris.h"

static void print_string_to_window(char *str,...){
	printw(str);
}

//--------------------------------------------------------
// refresh_game_screen
//--------------------------------------------------------
static void get_current_position(t_tetris *tetris, \
							t_tetrimino *tetrimino, \
							char next_playing_field[FIELD_ROW][FIELD_COL]){
	const int n = tetrimino->width_and_height;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(tetrimino->figure[i][j])
				next_playing_field[tetrimino->row+i][tetrimino->col+j] = tetrimino->figure[i][j];
		}
	}
}

static void print_header(){
	for(int i = 0; i < FIELD_COL - 9; i++)
		print_string_to_window(" ");
	print_string_to_window("42 Tetris\n");
}

static void print_game_field(t_tetris *tetris, \
						char next_playing_field[FIELD_ROW][FIELD_COL]){
	for(int i = 0; i < FIELD_ROW ;i++){
		for(int j = 0; j < FIELD_COL ; j++){
			if (tetris->playing_field[i][j] + next_playing_field[i][j])
				print_string_to_window("%c ", '#');
			else
				print_string_to_window("%c ", '.');
		}
		print_string_to_window("\n");
	}
}

static void print_footer(t_tetris *tetris){
	print_string_to_window("\nScore: %d\n", tetris->score);
}

static void print_game_screen(t_tetris *tetris, \
						char next_playing_field[FIELD_ROW][FIELD_COL]){
	print_header();
	print_game_field(tetris, next_playing_field);
	print_footer(tetris);
}

void refresh_game_screen(t_tetris *tetris, t_tetrimino *tetrimino){
	char next_playing_field[FIELD_ROW][FIELD_COL] = {0};
	
	//tetris->tetrimino = current;
	get_current_position(tetris, tetrimino ,next_playing_field);
	clear();
	print_game_screen(tetris, next_playing_field);
}
//--------------------------------------------------------
// refresh_game_screen
//--------------------------------------------------------