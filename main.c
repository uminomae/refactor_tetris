#include "tetris.h"
#include "tetrimino.h"

t_tetrimino current;

void begin_game(t_tetris *tetris){
	init_game(tetris);
	current = create_new_tetrimino(type_tetrimino);
	if(!can_move_field(tetris, &current)){
		tetris->game_status = GAME_OVER;
	}
    refresh_game_screen(tetris, &current);
}

void move_tetrimino_with_key(t_tetris *tetris, t_tetrimino *tetrimino, bool update){
	int key = tetris->input_from_keyboard;
	t_tetrimino for_judg_move = *copy_tetrimino_type(&current);

	if (key == DROP_KEY){
		move_case_key_s(tetris, &current, &for_judg_move, update);
	}else if (key == RIGHT_KEY){
		move_case_key_d(tetris, &current, &for_judg_move);
	}else if (key == LEFT_KEY){
		move_case_key_a(tetris, &current, &for_judg_move);
	}else if (key == ROTATE_KEY){
		move_case_key_w(tetris, &current, &for_judg_move);
	}
	destroy_tetrimino(&for_judg_move);
	refresh_game_screen(tetris, &current);
}

void run_game(t_tetris *tetris){
	while(tetris->game_status == GAME_PLAY){
    	tetris->input_from_keyboard = getch();
		if (tetris->input_from_keyboard != ERR) {
			move_tetrimino_with_key(tetris, &current, false);
		}
		gettimeofday(&now, NULL);
		if (need_update(tetris)) {
			tetris->input_from_keyboard = 's';
			move_tetrimino_with_key(tetris, &current, true);
			gettimeofday(&before_now, NULL);
		}
	}
}

int main() {
	t_tetris tetris;

	begin_game(&tetris);
	run_game(&tetris);
	finish_game(&tetris, current);
    return 0;
}


//--------------------------------------------------------
//case s move
//
void fix_tetrimino_on_the_field(t_tetris *tetris){
	const int n = tetris->tetrimino->width_and_height;
	const int row = tetris->tetrimino->row;
	const int col = tetris->tetrimino->col;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(tetris->tetrimino->figure[i][j])
				tetris->playing_field[row+i][col+j] = tetris->tetrimino->figure[i][j];
		}
	}
}

int count_blocks_of_line(t_tetris *tetris, int y){
	int blocks = 0;

	for(int x = 0; x < FIELD_COL; x++) {
		blocks += tetris->playing_field[y][x];
	}
	return (blocks);
}

void lower_the_upper_block(t_tetris *tetris, int y){
	for( ; y >= 1; y--)
		for(int x = 0; x < FIELD_COL; x++)
			tetris->playing_field[y][x] = tetris->playing_field[y-1][x];
}

void clear_line(t_tetris *tetris, int y){
	for(int x = 0; x < FIELD_COL; x++)
		tetris->playing_field[y][x] = 0;
}

void drop_placed_block_one_rank(t_tetris *tetris, int y){
	lower_the_upper_block(tetris, y);
	clear_line(tetris, TOP_ROW);
}

int count_completed_lines_and_erase(t_tetris *tetris){
	int number_of_completed_lines = 0;
	for(int y = 0; y < FIELD_ROW; y++){
		if(count_blocks_of_line(tetris, y) == FIELD_COL){
			drop_placed_block_one_rank(tetris, y);
			tetris->time_to_update -= tetris->decrease--;
			number_of_completed_lines++;
		}
	}
	return (number_of_completed_lines);
}

void make_next_tetrimino(t_tetris *tetris, t_tetrimino *tetlimino){
//void make_next_tetrimino(t_tetris *tetris){
	t_tetrimino new_shape = *copy_tetrimino_type(&type_tetrimino[rand() % 7]);
	new_shape.col = rand() % (FIELD_COL - new_shape.width_and_height+1);
	new_shape.row = 0;
	destroy_tetrimino(tetlimino);
	tetlimino = &new_shape;
	//destroy_tetrimino(&current);
	//current = new_shape;
	if(!can_move_field(tetris, &tetlimino)){
		tetris->game_status = GAME_OVER;
	}
}

void move_case_key_s(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg, bool update){
//void move_case_key_s(t_tetris *tetris, t_tetrimino *temp, bool update){
	temp_for_judg->row++;
	if(can_move_field(tetris, temp_for_judg))
		tetrimino->row++;
	else {
		fix_tetrimino_on_the_field(tetris);
		int completed_lines = count_completed_lines_and_erase(tetris);
		if (update == false)
			tetris->score += 100 * completed_lines;
		make_next_tetrimino(tetris, tetrimino);
	}
	//temp->row++;
	//if(can_move_field(tetris, temp))
	//	current.row++;
	//else {
	//	fix_tetrimino_on_the_field(tetris);
	//	int completed_lines = count_completed_lines_and_erase(tetris);
	//	if (update == false)
	//		tetris->score += 100 * completed_lines;
	//	make_next_tetrimino(tetris);
	//}
}