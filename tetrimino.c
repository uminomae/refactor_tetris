#include "tetris.h"

	
void switch_to_next_tetrimino(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *for_judge){
	t_tetrimino new = create_new_tetrimino(tetris->type);

	*tetrimino = new;
	judge_the_end_of_game(tetris, tetrimino, for_judge);
}

void rotate_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;
	t_tetrimino temp = copy_tetrimino_type(tetrimino);
	
	int k ;
	for(int i = 0; i < n ; i++){
		for(int j = 0, k = n - 1; j < n ; j++, k--){
				tetrimino->figure[i][j] = temp.figure[k][i];
		}
	}
}

void fix_tetrimino_on_the_field(t_tetris *tetris, t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;
	const int row = tetrimino->row;
	const int col = tetrimino->col;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(tetrimino->figure[i][j])
				tetris->playing_field[row+i][col+j] = tetrimino->figure[i][j];
		}
	}
}

//--------------------------------------------------------
// copy_tetrimino
//--------------------------------------------------------
static void copy_figure_array(char new[4][4], char type_tetrimino_figure[4][4], int width_and_height){
	const int n = width_and_height;

	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++) {
			new[x][y] = type_tetrimino_figure[x][y];
		}
	}
}

t_tetrimino copy_tetrimino_type(t_tetrimino *src){
	const int n = src->width_and_height;
	t_tetrimino new;

	copy_figure_array(new.figure, src->figure, n);
	new.width_and_height = src->width_and_height;
    return (new);
}
//--------------------------------------------------------
// endo of copy_tetrimino
//--------------------------------------------------------


//--------------------------------------------------------
// create_new_tetrimino
//--------------------------------------------------------

t_tetrimino create_new_tetrimino(t_tetrimino type[7]){
	const int i = rand() % NUM_OF_TYPE;
	t_tetrimino new;
	
	new = type[i];
    new.row = 0;
    new.col = rand() % (FIELD_COL - new.width_and_height + 1);
	return (new);
}
//--------------------------------------------------------
// end of create_new_tetrimino
//--------------------------------------------------------




