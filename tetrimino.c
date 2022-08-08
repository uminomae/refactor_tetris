#include "tetris.h"

static void copy_figure_array(char **new, char **type_tetrimino_figure, int width_and_height)
{
	const int n = width_and_height;

	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++) {
			new[x][y] = type_tetrimino_figure[x][y];
		}
	}
}

static char **get_alloc_figure_array(int n){
	char **figure = (char**)malloc(sizeof(char *) * n);
	for(int x = 0; x < n; x++){
		figure[x] = (char*)malloc(sizeof(char) * n);
	}
	return (figure);
}

t_tetrimino *copy_tetrimino_type(t_tetrimino *src){
	const int n = src->width_and_height;
	t_tetrimino new = *src;
	
	new.figure = get_alloc_figure_array(n);
	copy_figure_array((&new)->figure, src->figure, n);
    return (&new);
}

t_tetrimino create_new_tetrimino(t_tetrimino *type_tetrimino)
{
	t_tetrimino new_figure = *copy_tetrimino_type(&type_tetrimino[rand()%7]);

    new_figure.col = rand()%(FIELD_COL-new_figure.width_and_height+1);
    new_figure.row = 0;
	return (new_figure);
}

void destroy_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

    for(int i = 0; i < n; i++){
		free(tetrimino->figure[i]);
    }
    free(tetrimino->figure);
}