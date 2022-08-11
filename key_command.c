# include "main.h"

void move_case_key_d(t_tetris *tetris, t_tetrimino *current, t_tetrimino *temp_for_judge)
{
	temp_for_judge->col++;
	if(can_move_tetrimino(tetris, *temp_for_judge))
		current->col++;
}

void move_case_key_a(t_tetris *tetris, t_tetrimino *current, t_tetrimino *temp_for_judge)
{
	temp_for_judge->col--;
	if(can_move_tetrimino(tetris, *temp_for_judge))
		current->col--;
}

//--------------------------------------------------------
// key_w
//--------------------------------------------------------

static void rotate_clodkwise(t_tetrimino shape){
	t_tetrimino temp = copy_tetrimino(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	destroy_tetrimino(temp);
}

void move_case_key_w(t_tetris *tetris, t_tetrimino *current, t_tetrimino *temp_for_judge)
{
	rotate_clodkwise(*temp_for_judge);
	if(can_move_tetrimino(tetris, *temp_for_judge))
		rotate_clodkwise(*current);
}
//--------------------------------------------------------
// 
//--------------------------------------------------------

//--------------------------------------------------------
// key_s
//--------------------------------------------------------

static void fix_tetrimino_on_the_field(t_tetris *tetris, t_tetrimino *current){
	const int n = current->width;
	const int row = current->row;
	const int col = current->col;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(current->array[i][j])
				tetris->playing_field[row+i][col+j] = current->array[i][j];
		}
	}
}

void move_case_key_s(t_tetris *tetris, \
						t_tetrimino *current, \
						t_tetrimino *temp_for_judge, \
						const t_tetrimino *type){
	(*temp_for_judge).row += 1;
	if(can_move_tetrimino(tetris, *temp_for_judge))
		(*current).row += 1;
	else {
		fix_tetrimino_on_the_field(tetris, current);
		int completed_lines = 0;
		count_completed_lines_and_erase(tetris, &completed_lines);
		tetris->score += 100 * completed_lines;
		*current = replace_next_tetrimino(current, type);
		judge_the_end_of_game(tetris, *current);
	}
}
//--------------------------------------------------------
// 
//--------------------------------------------------------


