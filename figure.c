//#include "tetris.h"
//#include "tetrimino.h"


//t_tetrimino create_shape(t_tetrimino shape){
//	t_tetrimino new_shape = shape;
//	char **copyshape = shape.array;
//	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
//    int i, j;
//    for(i = 0; i < new_shape.width; i++){
//		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
//		for(j=0; j < new_shape.width; j++) {
//			new_shape.array[i][j] = copyshape[i][j];
//		}
//    }
//    return new_shape;
//}




////destroy
//void destroy_shape(t_tetrimino shape){
//    int i;
//    for(i = 0; i < shape.width; i++){
//		free(shape.array[i]);
//    }
//    free(shape.array);
//}

//7種類の形
//0 + rand() % 10) // 最小値:0 取得個数:10個
