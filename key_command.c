#include "tetris.h"

void	move_right(t_tetris *tetris, \
						t_tetrimino *current, \
						t_tetrimino *temp_for_judge){
	temp_for_judge->col += 1;
	if (can_move_tetrimino(tetris, *temp_for_judge))
		current->col += 1;
}

void	move_left(t_tetris *tetris, \
						t_tetrimino *current, \
						t_tetrimino *temp_for_judge){
	temp_for_judge->col -= 1;
	if (can_move_tetrimino(tetris, *temp_for_judge))
		current->col -= 1;
}

//--------------------------------------------------------
// move_rotate
//--------------------------------------------------------

static void	rotate_clodkwise(t_tetrimino shape){
	t_tetrimino	temp = copy_tetrimino(shape);
	if (temp.figure == NULL)
		return ;
	int i, j, k, side_length;
	side_length = shape.side_length;
	for (i = 0; i < side_length; i++){
		for (j = 0, k = side_length - 1; j < side_length; j++, k--){
			shape.figure[i][j] = temp.figure[k][i];
		}
	}
	destroy_tetrimino_fiure(temp);
}

void	move_rotate(t_tetris *tetris, \
						t_tetrimino *current, \
						t_tetrimino *temp_for_judge){
	rotate_clodkwise(*temp_for_judge);
	if (temp_for_judge->figure == NULL)
		return ;
	if (can_move_tetrimino(tetris, *temp_for_judge))
		rotate_clodkwise(*current);
}

//--------------------------------------------------------
// move_drop
//--------------------------------------------------------

static void	fix_tetrimino_on_the_field(t_tetris *tetris, t_tetrimino *current){
	const int	n = current->side_length;
	const int	row = current->row;
	const int	col = current->col;

	for (int i = 0; i < n ;i++){
		for (int j = 0; j < n; j++){
			if (current->figure[i][j])
				tetris->playing_field[row + i][col + j] = current->figure[i][j];
		}
	}
}

void	move_drop(t_tetris *tetris, \
						t_tetrimino *current, \
						t_tetrimino *temp_for_judge, \
						const t_tetrimino *type){
	(*temp_for_judge).row += 1;
	if (can_move_tetrimino(tetris, *temp_for_judge))
		(*current).row += 1;
	else {
		fix_tetrimino_on_the_field(tetris, current);
		int	completed_lines = 0;
		count_completed_lines_and_erase(tetris, &completed_lines);
		tetris->score += 100 * completed_lines;
		*current = replace_next_tetrimino(current, type);
		if (current->figure == NULL)
			return ;
		judge_the_end_of_game(tetris, *current);
	}
}

//--------------------------------------------------------
// 
//--------------------------------------------------------


//        42 Tetris
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . move_left. . .  move_right 
//  .  . <-. . . # # . . -> . . .
//  . . . . . . # # . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . | move_drop . . .
//  . . . . . . v . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . # . . . . . . . . . # .
//  . . . # # . . . # # # # # # #
//  # # # # # . # # # # # # # . #
//  
//  Score: 0 (= completed_lines * 100)