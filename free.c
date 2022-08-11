#include "main.h"

void destroy_tetrimino(t_tetrimino shape){
	const int n = shape.width;

    for(int i = 0; i < n; i++){
		free(shape.array[i]);
    }
    free(shape.array);
}