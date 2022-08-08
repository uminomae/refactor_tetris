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

