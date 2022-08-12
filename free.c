#include "tetris.h"

void	destroy_tetrimino(t_tetrimino shape){
	const int	n = shape.side_length;

	for (int i = 0; i < n; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}

void	destroy_tetrimino_dubble_pointer(t_tetrimino **shape){
	const int	n = (*shape)->side_length;

	for (int i = 0; i < n; i++){
		free((*shape)->array[i]);
	}
	free((*shape)->array);
}
