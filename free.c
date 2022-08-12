#include "tetris.h"

void	destroy_tetrimino_fiure(t_tetrimino shape){
	const int	n = shape.side_length;

	for (int i = 0; i < n; i++){
		free(shape.array[i]);
	}
	free(shape.array);
}

