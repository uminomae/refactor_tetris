#include "tetris.h"

//void copy_figure(t_tetrimino *new_tetrimino, char **type_tetrimino_figure)
//{
//	const int n = new_tetrimino->width_and_height;

//	for(int x = 0; x < n; x++){
//		new_tetrimino->figure[x] = (char*)malloc(sizeof(char) * n);
//		for(int y = 0; y < n; y++) {
//			new_tetrimino->figure[x][y] = type_tetrimino_figure[x][y];
//		}
//	}
//}

void destroy_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

    for(int i = 0; i < n; i++){
		free(tetrimino->figure[i]);
    }
    free(tetrimino->figure);
}
