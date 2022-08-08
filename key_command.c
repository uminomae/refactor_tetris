#include "tetris.h"


void roteta_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

	t_tetrimino *temp = copy_tetrimino_type(tetrimino);
	
		int k ;
		//int k = n - 1;
	for(int i = 0; i < n ; i++){
		//for(int j = 0; j < n ; j++, k--){
		for(int j = 0, k = n - 1; j < n ; j++, k--){
				tetrimino->figure[i][j] = temp->figure[k][i];
		}
	}
	destroy_tetrimino(temp);
}

//--------------------------------------------------------
// move
//
void move_case_key_d(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg)
{
	temp_for_judg->col++;
	if(can_move_field(tetris, temp_for_judg))
		//current.col++;
		tetrimino->col++;
}

void move_case_key_a(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg)
//void move_case_key_a(t_tetris *tetris, t_tetrimino *temp)
{
	//temp->col--;
	//if(can_move_field(tetris, temp))
	//	current.col--;
	temp_for_judg->col--;
	if(can_move_field(tetris, temp_for_judg))
		tetrimino->col--;
}

void move_case_key_w(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg)
//void move_case_key_w(t_tetris *tetris, t_tetrimino *temp, t_tetrimino current)
{
	roteta_tetrimino(temp_for_judg);
	if(can_move_field(tetris, temp_for_judg))
		roteta_tetrimino(&tetrimino);
	//roteta_tetrimino(temp);
	//if(can_move_field(tetris, temp))
	//	roteta_tetrimino(&current);
}