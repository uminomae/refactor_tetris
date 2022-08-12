#include "tetris.h"

//--------------------------------------------------------
// copy_tetrimino
//--------------------------------------------------------

static char	**get_alloc_figure(int side_length){
	char	**figure = (char**)malloc(sizeof(char *) * (side_length + 1));
	if (figure == NULL)
		exit(1);
	figure[side_length] = NULL;
	for (int x = 0; x < side_length; x++){
		figure[x] = (char *)malloc(sizeof(char) * side_length);
		if (figure[x] == NULL){
			free_dubble_ptr(figure);
			exit(1);
		}
	}
	return (figure);
}

static void	copy_figure(char **dst, char **src, int one_side){
	const int	n = one_side;

	for (int x = 0; x < n; x++){
		for (int y = 0; y < n; y++) 
			dst[x][y] = src[x][y];
	}
}

t_tetrimino	copy_tetrimino(t_tetrimino shape){
	t_tetrimino	new_shape = shape;
	int	one_side = shape.side_length;

	new_shape.figure = get_alloc_figure(one_side);
	//TODO
	//new_shape.figure =NULL;
	//
	//if (new_shape.figure == NULL)
	//	return (new_shape);
	copy_figure(new_shape.figure, shape.figure, one_side);
	return (new_shape);
}

//--------------------------------------------------------
// create_new_tetrimino
//--------------------------------------------------------

static t_tetrimino	select_type_tetrimino(const t_tetrimino *type){
	const int	i = rand() % NUM_OF_TYPE;
	t_tetrimino	select = type[i];

	return (select);
}

t_tetrimino	create_new_tetrimino(const t_tetrimino *type){
	t_tetrimino	temp_type = select_type_tetrimino(type);
	t_tetrimino	new = copy_tetrimino(temp_type);

	new.col = rand() % (FIELD_X_COL - new.side_length + 1);
	new.row = 0;
	return (new);
}

//--------------------------------------------------------
// 
//--------------------------------------------------------

t_tetrimino	replace_next_tetrimino(t_tetrimino *current, \
									const t_tetrimino *type){
	t_tetrimino	new_shape = create_new_tetrimino(type);

	//if (current->figure == NULL)
	//	return (new_shape);
	destroy_tetrimino_fiure(*current);
	return (new_shape);
}
