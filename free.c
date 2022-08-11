#include "tetris.h"

void	destroy_tetrimino(t_tetrimino shape){
	const int	n = shape.width;

	for (int i = 0; i < n; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}

// TODO
// destroy()の共通化
//
void	destroy_tetrimino_dubble_pointer(t_tetrimino **shape){
	const int	n = (*shape)->width;

	for (int i = 0; i < n; i++){
		free((*shape)->array[i]);
	}
	free((*shape)->array);
}
