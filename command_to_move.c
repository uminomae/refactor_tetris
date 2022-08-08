#include "tetris.h"

//void move_case_d(t_tetris *tetris, t_tetrimino *temp)
//{
//	temp->col++;
//	if(can_move_field(tetris, temp))
//		current.col++;
//}

//void move_case_a(t_tetris *tetris, t_tetrimino *temp)
//{
//	temp->col--;
//	if(can_move_field(tetris, temp))
//		current.col--;
//}

void roteta_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

	t_tetrimino *temp = copy_tetrimino_type(tetrimino);
	
	int k = n - 1;
	for(int i = 0; i < n ; i++){
		for(int j = 0, k = n - 1; j < n ; j++, k--){
				tetrimino->figure[i][j] = temp->figure[k][i];
		}
	}
	destroy_tetrimino(temp);
}

//void move_case_w(t_tetris *tetris, t_tetrimino *temp,t_tetrimino current)
//{
//	roteta_tetrimino(temp);
//	if(can_move_field(tetris, temp))
//		roteta_tetrimino(&current);
//}
