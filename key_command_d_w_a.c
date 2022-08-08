#include "tetris.h"

void move_case_key_d(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg)
{
	temp_for_judg->col++;
	if(can_move_field(tetris, temp_for_judg))
		tetrimino->col++;
}

void move_case_key_a(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg)
{
	temp_for_judg->col--;
	if(can_move_field(tetris, temp_for_judg))
		tetrimino->col--;
}

//--------------------------------------------------------
// key_w
//--------------------------------------------------------
void move_case_key_w(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg)
{
	roteta_tetrimino(temp_for_judg);
	if(can_move_field(tetris, temp_for_judg))
		roteta_tetrimino(tetrimino);
}

void roteta_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;
	t_tetrimino *temp = copy_tetrimino_type(tetrimino);
	
	int k ;
	for(int i = 0; i < n ; i++){
		for(int j = 0, k = n - 1; j < n ; j++, k--){
				tetrimino->figure[i][j] = temp->figure[k][i];
		}
	}
	destroy_tetrimino(temp);
}

//--------------------------------------------------------
// end of key_w
//--------------------------------------------------------
