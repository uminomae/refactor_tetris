#include "tetris.h"

bool check_left(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->col+ j < 0 && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

bool check_right(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->col + j >= FIELD_COL && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

bool check_bottom(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->row + i >= FIELD_ROW && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

