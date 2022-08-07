#include "tetris.h"

// constの設定がうまくいかないので質問する
void copy_figure(t_tetrimino *new_tetrimino, char **type_tetrimino_figure)
{
	const int n = new_tetrimino->width_and_height;

	for(int x = 0; x < n; x++){
		new_tetrimino->figure[x] = (char*)malloc(sizeof(char) * n);
		for(int y = 0; y < n; y++) {
			new_tetrimino->figure[x][y] = type_tetrimino_figure[x][y];
		}
	}
}

//構造体型はmalloc失敗時にNULL返す方法を質問する
t_tetrimino create_tetrimino(const t_tetrimino type_tetrimino){
	const int y_size = type_tetrimino.width_and_height;
	t_tetrimino new_type_tetrimino = type_tetrimino;

	new_type_tetrimino.figure = (char**)malloc(sizeof(char *) * y_size);
	copy_figure(&new_type_tetrimino, type_tetrimino.figure);
    return (new_type_tetrimino);
}

//destroy
void destroy_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

    for(int i = 0; i < n; i++){
		free(tetrimino->figure[i]);
    }
    free(tetrimino->figure);
}
