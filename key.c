# include "main.h"

//void get_char_input_from_keyboad(t_tetris *tetris){
//	tetris->input_from_keyboard = getch();
//}

//void move_by_key_case(t_tetris *tetris, \
//						t_tetrimino *current, \
//						t_tetrimino *temp_for_judge, \
//						const t_tetrimino *type){
//	int key = tetris->input_from_keyboard;
//	if (key == DROP_KEY){
//		move_case_key_s(tetris, current, temp_for_judge, type);
//	}else if (key == RIGHT_KEY){
//		move_case_key_d(tetris, current, temp_for_judge);
//	}else if (key == LEFT_KEY){
//		move_case_key_a(tetris, current, temp_for_judge);
//	}else if (key == ROTATE_KEY){
//		move_case_key_w(tetris, current, temp_for_judge);
//	}
//}

//--------------------------------------------------------
// key_command
//--------------------------------------------------------

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

//void switch_to_next_tetrimino(t_tetris *tetris, t_tetrimino *tetrimino){
//	t_tetrimino *new = create_new_tetrimino(tetris->type);

//	destroy_tetrimino(tetrimino);
//	tetrimino = new;
//	judge_the_end_of_game(tetris);
//}

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

//updateはいつ使う？
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
		//if (update == false)
		tetris->score += 100 * completed_lines;
		*current = replace_next_tetrimino(current, type);
		judge_the_end_of_game(tetris, *current);
		//switch_to_next_tetrimino(tetris, tetrimino);
	}
}

//--------------------------------------------------------
// key_command
//--------------------------------------------------------


