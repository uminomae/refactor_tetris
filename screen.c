#include "tetris.h"

static void	get_current_position(t_tetris *tetris, \
							t_tetrimino *current, \
							char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	const int	n = current->side_length;

	for (int i = 0; i < n ; i++){
		for (int j = 0; j < n; j++){
			if (current->figure[i][j])
				next_playing_field[current->row + i][current->col + j] \
				 = current->figure[i][j];
		}
	}
}

//--------------------------------------------------------
// print_game_screen
//--------------------------------------------------------

static void	print_header(){
	for (int i = 0; i < FIELD_X_COL - 9; i++){
		printw(" ");
	}
	printw("42 Tetris\n");
}

static void	print_game_field(t_tetris *tetris, \
						char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	for (int i = 0; i < FIELD_Y_ROW;i++){
		for (int j = 0; j < FIELD_X_COL; j++){
			if (tetris->playing_field[i][j] + next_playing_field[i][j])
				printw("%c ", '#');
			else
				printw("%c ", '.');
		}
		printw("\n");
	}
}

static void	print_footer(t_tetris *tetris){
	printw("\nScore: %d\n", tetris->score);
}

static void	print_game_screen(t_tetris *tetris, \
							char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	print_header();
	print_game_field(tetris, next_playing_field);
	print_footer(tetris);
}
//--------------------------------------------------------
// 
//--------------------------------------------------------

void	refresh_game_screen(t_tetris *tetris, t_tetrimino *current){
	char	next_playing_field[FIELD_Y_ROW][FIELD_X_COL] = {0};
	
	get_current_position(tetris, current, next_playing_field);
	clear();
	print_game_screen(tetris, next_playing_field);
}
