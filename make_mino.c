# include "main.h"
//# include "type.h"


//i=x,j=y
//--------------------------------------------------------
// copy_tetrimino
//--------------------------------------------------------

static char **get_alloc_figure_array(int one_side){
	char **array = (char**)malloc(sizeof(char *) * one_side);

	for(int x = 0; x < one_side; x++){
		array[x] = (char*)malloc(sizeof(char) * one_side);
	}
	return (array);
}

static void copy_figure_array(char **dst, char **src, int one_side){
	const int n = one_side;

	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++) 
			dst[x][y] = src[x][y];
	}
}

t_tetrimino copy_tetrimino(t_tetrimino shape){
	t_tetrimino new_shape = shape;
	int one_side = shape.width;
	
	new_shape.array = get_alloc_figure_array(one_side);
	copy_figure_array(new_shape.array, shape.array, one_side);
    return new_shape;
}

//// memcpyが動かなかった
//t_tetrimino copy_tetrimino(t_tetrimino shape){
//	t_tetrimino new_shape = shape;
//	int one_side = shape.width;
	
//	new_shape.array = get_alloc_figure_array(one_side);
//    memcpy(new_shape.array, shape.array, sizeof(shape.array) * 1);
//    return new_shape;
//}

//--------------------------------------------------------
// endo of copy_tetrimino
//--------------------------------------------------------

//--------------------------------------------------------
// create_new_tetrimino
//--------------------------------------------------------

static t_tetrimino select_type_tetrimino(const t_tetrimino *type){
	const int i = rand() % NUM_OF_TYPE;
	t_tetrimino	select = type[i];

	return (select);
}

t_tetrimino create_new_tetrimino(const t_tetrimino *type){
	t_tetrimino temp_type = select_type_tetrimino(type);
	t_tetrimino new = copy_tetrimino(temp_type);

    new.col = rand() % (FIELD_X_COL - new.width + 1);
    new.row = 0;
	return (new);
}
//--------------------------------------------------------
// end of create_new_tetrimino
//--------------------------------------------------------


//--------------------------------------------------------
// replace_next_tetrimino
//--------------------------------------------------------

static void destroy_tetrimino_dubble_pointer(t_tetrimino **shape){
	const int n = (*shape)->width;

    for(int i = 0; i < n; i++){
		free((*shape)->array[i]);
    }
    free((*shape)->array);
}

t_tetrimino replace_next_tetrimino(t_tetrimino *current, \
									const t_tetrimino *type){
	t_tetrimino new_shape = create_new_tetrimino(type);

	destroy_tetrimino_dubble_pointer(&current);
	return (new_shape);
}
//--------------------------------------------------------
// end of replace_next_tetrimino
//--------------------------------------------------------