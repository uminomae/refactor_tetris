#include "tetris.h"

void get_char_from_keyboad(t_tetris *tetris){
	tetris->input_from_keyboard = getch();
}

//--------------------------------------------------------
// key_command
//--------------------------------------------------------

void move_case_key_d(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge)
{
	temp_for_judge->col++;
	if(can_move_field(tetris, temp_for_judge))
		tetrimino->col++;
}

void move_case_key_a(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge)
{
	temp_for_judge->col--;
	if(can_move_field(tetris, temp_for_judge))
		tetrimino->col--;
}

void move_case_key_w(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge)
{
	rotate_tetrimino(temp_for_judge);
	if(can_move_field(tetris, temp_for_judge))
		rotate_tetrimino(tetrimino);
}

void move_case_key_s(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge, bool update){
	temp_for_judge->row++;
	if(can_move_field(tetris, temp_for_judge))
		tetrimino->row++;
	else {
		fix_tetrimino_on_the_field(tetris);
		int completed_lines = count_completed_lines_and_erase(tetris);
		if (update == false)
			tetris->score += 100 * completed_lines;
		switch_to_next_tetrimino(tetris, tetrimino);
	}
}

//--------------------------------------------------------
// end of key_command
//--------------------------------------------------------

void move_by_key_case(t_tetris *tetris, \
						t_tetrimino *tetrimino, \
						t_tetrimino *temp_for_judge, \
						bool update, \
						int key){
	if (key == DROP_KEY){
		move_case_key_s(tetris, tetrimino, temp_for_judge, update);
	}else if (key == RIGHT_KEY){
		move_case_key_d(tetris, tetrimino, temp_for_judge);
	}else if (key == LEFT_KEY){
		move_case_key_a(tetris, tetrimino, temp_for_judge);
	}else if (key == ROTATE_KEY){
		move_case_key_w(tetris, tetrimino, temp_for_judge);
	}
}

void move_tetrimino(t_tetris *tetris, t_tetrimino *tetrimino, bool update){
	int key = tetris->input_from_keyboard;
	t_tetrimino temp_for_judge = copy_tetrimino_type(tetrimino);
	
	move_by_key_case(tetris, tetrimino, &temp_for_judge, update, key);
	refresh_game_screen(tetris, tetrimino);
}