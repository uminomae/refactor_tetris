#include "tetris.h"

void	judge_the_end_of_game(t_tetris *tetris, t_tetrimino current){
	if (!can_move_tetrimino(tetris, current))
		tetris->game_status = GAME_OVER;
}

//--------------------------------------------------------
//can_move_tetrimino
//--------------------------------------------------------
static bool	can_move_left(t_tetrimino figure, int y, int x){
	return (!(figure.col + x < 0));
}

static bool	can_move_right(t_tetrimino figure, int y, int x){
	return (!(figure.col + x >= FIELD_X_COL));
}

static bool	can_move_bottom(t_tetrimino figure, int y, int x){
	return (!(figure.row + y >= FIELD_Y_ROW));
}

static bool	can_move_not_overlapping(t_tetris *tetris, \
										t_tetrimino figure, int y, int x){
	return (!(tetris->playing_field[figure.row + y][figure.col + x]));
}

int	can_move_tetrimino(t_tetris *tetris, t_tetrimino shape){
	const int	n = shape.side_length;

	for (int y = 0; y < n; y++)	{
		for (int x = 0; x < n; x++){
			if (!shape.array[y][x])
				continue ;
			if (!can_move_left(shape, y, x))
				return (FALSE);
			if (!can_move_right(shape, y, x))
				return (FALSE);
			if (!can_move_bottom(shape, y, x))
				return (FALSE);
			if (!can_move_not_overlapping(tetris, shape, y, x))
				return (FALSE);
		}
	}
	return (TRUE);
}
//--------------------------------------------------------
//
//--------------------------------------------------------
