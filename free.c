#include "tetris.h"

void	free_dubble_ptr(char **figure){

	size_t i = 0;
	while (figure[i] != NULL){
		free(figure[i]);
		i++;
	}
	free(figure);
}

void	destroy_tetrimino_fiure(t_tetrimino shape){
	free_dubble_ptr(shape.figure);
}



