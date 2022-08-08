#include "tetris.h"

static bool can_move_left(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->col+ j < 0 && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

static bool can_move_right(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->col + j >= FIELD_COL && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

static bool can_move_bottom(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->row + i >= FIELD_ROW && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

static bool can_move_not_overlapping(t_tetris *tetris, int i, int j){
	const t_tetrimino *tetrimino = tetris->tetrimino;
	printf("d1--can_move_x----\n");

	if (tetris->playing_field[tetrimino->row + i][tetrimino->col + j] && tetrimino->figure[i][j])
		return FALSE;
	printf("d2--can_move_x----\n");
	return TRUE;
}

// x,yに
int can_move_field(t_tetris *tetris, t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			if (!can_move_left(tetrimino, i, j))
				return FALSE;
			if (!can_move_right(tetrimino, i, j))
				return FALSE;
			if (!can_move_bottom(tetrimino, i, j))
				return FALSE;
			printf("c--can_move_field----\n");
			if (!can_move_not_overlapping(tetris, i, j))
				return FALSE;
		}
	}
	return TRUE;
}