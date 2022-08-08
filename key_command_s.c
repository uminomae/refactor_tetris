#include "tetris.h"


//--------------------------------------------------------
//key_s
//--------------------------------------------------------
void fix_tetrimino_on_the_field(t_tetris *tetris){
	const int n = tetris->tetrimino->width_and_height;
	const int row = tetris->tetrimino->row;
	const int col = tetris->tetrimino->col;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(tetris->tetrimino->figure[i][j])
				tetris->playing_field[row+i][col+j] = tetris->tetrimino->figure[i][j];
		}
	}
}

t_tetrimino *select_type_tetrimino(t_tetrimino *src){
	const int i = rand() % NUM_OF_TYPE;
	t_tetrimino *select;
	
	select = &src[i];
	return (select);
}

void make_next_tetrimino(t_tetris *tetris, t_tetrimino *tetlimino){
	t_tetrimino next_tetrimino = *copy_tetrimino_type(select_type_tetrimino);
	next_tetrimino.col = rand() % (FIELD_COL - next_tetrimino.width_and_height+1);
	next_tetrimino.row = 0;
	destroy_tetrimino(tetlimino);
	tetlimino = &next_tetrimino;
	if(!can_move_field(tetris, &tetlimino)){
		tetris->game_status = GAME_OVER;
	}
}

void move_case_key_s(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg, bool update){
	temp_for_judg->row++;
	if(can_move_field(tetris, temp_for_judg))
		tetrimino->row++;
	else {
		fix_tetrimino_on_the_field(tetris);
		int completed_lines = count_completed_lines_and_erase(tetris);
		if (update == false)
			tetris->score += 100 * completed_lines;
		make_next_tetrimino(tetris, tetrimino);
	}
}
//--------------------------------------------------------
// end of key_s
//--------------------------------------------------------