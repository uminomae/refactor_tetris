# include "main.h"

//--------------------------------------------------------
// count_completed_lines_and_erase
//--------------------------------------------------------
static int count_blocks_of_line(t_tetris *tetris, int y){
	int blocks = 0;

	for(int x = 0; x < FIELD_X_COL; x++) {
		blocks += tetris->playing_field[y][x];
	}
	return (blocks);
}

static void drop_block(t_tetris *tetris, int y){
	for( ; y >= 1; y--)
		for(int x = 0; x < FIELD_X_COL; x++)
			tetris->playing_field[y][x] = tetris->playing_field[y-1][x];
}

static void clear_line(t_tetris *tetris, int y){
	for(int x = 0; x < FIELD_X_COL; x++)
		tetris->playing_field[y][x] = 0;
}

int count_completed_lines_and_erase(t_tetris *tetris, int *completed_lines){
	for(int y = 0; y < FIELD_Y_ROW; y++){
		if(count_blocks_of_line(tetris, y) == FIELD_X_COL){
			*completed_lines += 1;
			drop_block(tetris, y);
			clear_line(tetris, TOP_Y_ROW);
			tetris->time_to_update -= tetris->decrease--;
		}
	}
	return (*completed_lines);
}
//--------------------------------------------------------
// endo of count_completed_lines_and_erase
//--------------------------------------------------------


///質問すること
//returnが戻らない
//int count_completed_lines_and_erase(t_tetris *tetris){
//	int completed_lines = 0;
//	for(int y = 0; y < FIELD_Y_ROW; y++){
//		if(count_blocks_of_line(tetris, y) == FIELD_X_COL){
//			completed_lines += 1;
//			drop_block(tetris, y);
//			clear_line(tetris, TOP_Y_ROW);
//			//drop_placed_block_one_rank(tetris, y);
//			tetris->time_to_update -= tetris->decrease--;
//		}
//	}
//	return (completed_lines);
//}
