# include "main.h"

//--------------------------------------------------------
// refresh_game_screen
//--------------------------------------------------------

static void print_string_to_window(char *str,...){
	printw(str);
}

static void get_current_position(t_tetris *tetris, \
							t_tetrimino *current, \
							char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	const int n = current->width;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(current->array[i][j])
				next_playing_field[current->row+i][current->col+j] \
				 = current->array[i][j];
		}
	}
}

static void print_header(){
	for(int i = 0; i < FIELD_X_COL - 9; i++)
		print_string_to_window(" ");
	print_string_to_window("42 Tetris\n");
}

static void print_game_field(t_tetris *tetris, \
						char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	for(int i = 0; i < FIELD_Y_ROW ;i++){
		for(int j = 0; j < FIELD_X_COL ; j++){
			if (tetris->playing_field[i][j] + next_playing_field[i][j])
				print_string_to_window("%c ", '#');
			else
				print_string_to_window("%c ", '.');
		}
		print_string_to_window("\n");
	}
}

static void print_footer(t_tetris *tetris){
	//printw("\nScore: %d\n", tetris.score);
	print_string_to_window("\nScore: %d\n", tetris->score);
}

static void print_game_screen(t_tetris *tetris, \
						char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	print_header();
	print_game_field(tetris, next_playing_field);
	print_footer(tetris);
}

void put_screen(t_tetris *tetris, t_tetrimino *current){
//void refresh_game_screen(t_tetris *tetris, t_tetrimino *current){
	char next_playing_field[FIELD_Y_ROW][FIELD_X_COL] = {0};
	
	//tetris->tetrimino = current;
	get_current_position(tetris, current, next_playing_field);
	clear();
	print_game_screen(tetris, next_playing_field);
}
//--------------------------------------------------------
// refresh_game_screen
//--------------------------------------------------------


//void put_screen(t_tetris *tetris, t_tetrimino *current){
//	char Buffer[R][C] = {0};
//	int i, j;
//	for(i = 0; i < current->width ;i++){
//		for(j = 0; j < current->width ; j++){
//			if(current->array[i][j])
//				Buffer[current->row+i][current->col+j] = current->array[i][j];
//		}
//	}
//	clear();
//	for(i=0; i<C-9; i++)
//		printw(" ");
//	printw("42 Tetris\n");
//	for(i = 0; i < R ;i++){
//		for(j = 0; j < C ; j++){
//			printw("%c ", (tetris->playing_field[i][j] + Buffer[i][j])? '#': '.');
//		}
//		printw("\n");
//	}
//	printw("\nScore: %d\n", tetris.score);
//}
