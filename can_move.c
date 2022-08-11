
# include "main.h"


//void judge_the_end_of_game(t_tetris *tetris, t_tetrimino current){
//	if(!can_move_tetrimino(tetris, &current)){
//		tetris->game_status = GAME_OVER;
//	}
//}

//--------------------------------------------------------
//can_move_tetrimino
//--------------------------------------------------------
static bool can_move_left(t_tetrimino figure, int y, int x){
	if (figure.col+ x < 0)
		return FALSE;
	return TRUE;
}

static bool can_move_right(t_tetrimino figure, int y, int x){
	if (figure.col + x >= FIELD_X_COL)
		return FALSE;
	return TRUE;
}

static bool can_move_bottom(t_tetrimino figure, int y, int x){
	if (figure.row + y >= FIELD_Y_ROW)
		return FALSE;
	return TRUE;
}

static bool can_move_not_overlapping(t_tetris *tetris, t_tetrimino figure, int y, int x){

	if (tetris->playing_field[figure.row + y][figure.col + x])
		return FALSE;
	return TRUE;
}

int can_move_tetrimino(t_tetris *tetris, t_tetrimino shape){
	const int n = shape.width;

	for (int y = 0; y < n; y++){
		for (int x = 0; x < n; x++){
			if (!shape.array[y][x])
				continue;
			if (!can_move_left(shape, y, x))
				return FALSE;
			if (!can_move_right(shape, y, x))
				return FALSE;
			if (!can_move_bottom(shape, y, x))
				return FALSE;
			if (!can_move_not_overlapping(tetris, shape, y, x))
				return FALSE;	
		}
	}
	return TRUE;
}

//動いてたコード
//int can_move_tetrimino(t_tetris *tetris, t_tetrimino shape){
////int can_move_tetrimino t_tetrimino shape){
//	char **array = shape.array;

//	int i, j;
//	for(i = 0; i < shape.width;i++) {
//		for(j = 0; j < shape.width ;j++){
//			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
//				//if(shape.array[i][j])
//				if(array[i][j])
//					return FALSE;
				
//			}
//			//else if(tetris->playing_field[shape.row+i][shape.col+j] && shape.array[i][j])
//			else if(tetris->playing_field[shape.row+i][shape.col+j] && array[i][j])
//				return FALSE;
//		}
//	}
//	return TRUE;
//}


//--------------------------------------------------------
//end of can_move_tetrimino
//--------------------------------------------------------
