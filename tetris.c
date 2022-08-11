
# include "main.h"
//# include "tetrimino.h"
# include "type.h"

#define R 20
#define C 15

void rotate_clodkwise(t_tetrimino shape);

int hasToUpdate();
void set_timeout(int time);

suseconds_t timer = FALL_VELOCITY_INTERVAL;
int decrease = 1000;

struct timeval before_now, now;





//void get_char_input_from_keyboad(t_tetris *tetris){
//	tetris->input_from_keyboard = getch();
//}

//void move_tetrimino_with_key(t_tetris *tetris, \
//								t_tetrimino *tetrimino, \
//								bool update){
//	int key = tetris->input_from_keyboard;
//	t_tetrimino temp_for_judge = *copy_tetrimino_type(tetrimino);
	
//	move_by_key_case(tetris, tetrimino, &temp_for_judge, update, key);
//	destroy_tetrimino(&temp_for_judge);
//	refresh_game_screen(tetris, tetrimino);
//}

//void move_by_key_case(t_tetris *tetris, \
//						t_tetrimino *tetrimino, \
//						t_tetrimino *temp_for_judge, \
//						bool update, \
//						int key){
//	if (key == DROP_KEY){
//		move_case_key_s(tetris, tetrimino, temp_for_judge, update);
//	}else if (key == RIGHT_KEY){
//		move_case_key_d(tetris, tetrimino, temp_for_judge);
//	}else if (key == LEFT_KEY){
//		move_case_key_a(tetris, tetrimino, temp_for_judge);
//	}else if (key == ROTATE_KEY){
//		move_case_key_w(tetris, tetrimino, temp_for_judge);
//	}
//}

////--------------------------------------------------------
//// key_command
////--------------------------------------------------------

//void move_case_key_d(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge)
//{
//	temp_for_judge->col++;
//	if(can_move_field(tetris, temp_for_judge))
//		tetrimino->col++;
//}

//void move_case_key_a(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge)
//{
//	temp_for_judge->col--;
//	if(can_move_field(tetris, temp_for_judge))
//		tetrimino->col--;
//}

//void move_case_key_w(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge)
//{
//	rotate_tetrimino(temp_for_judge);
//	if(can_move_field(tetris, temp_for_judge))
//		rotate_tetrimino(tetrimino);
//}



//void switch_to_next_tetrimino(t_tetris *tetris, t_tetrimino *tetrimino){
//	t_tetrimino *new = create_new_tetrimino(tetris->type);

//	destroy_tetrimino(tetrimino);
//	tetrimino = new;
//	judge_the_end_of_game(tetris);
//}

static void fix_tetrimino_on_the_field(t_tetris *tetris, t_tetrimino *current){
	const int n = current->width;
	const int row = current->row;
	const int col = current->col;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(current->array[i][j])
				tetris->playing_field[row+i][col+j] = current->array[i][j];
		}
	}
}


//void move_case_key_s(t_tetris *tetris, \
//						t_tetrimino *current, \
//						t_tetrimino *temp_for_judge, bool update){
//	temp_for_judge->row +=++;
//	if(can_move_field(tetris, temp_for_judge))
//		tetrimino->row++;
//	else {
//		fix_tetrimino_on_the_field(tetris, current);
//		int completed_lines = count_completed_lines_and_erase(tetris);
//		if (update == false)
//			tetris->score += 100 * completed_lines;
//		switch_to_next_tetrimino(tetris, tetrimino);
//	}
//}

//void get_char_input_from_keyboad(t_tetris *tetris){
//	tetris->input_from_keyboard = getch();
//}


////--------------------------------------------------------
//// count_completed_lines_and_erase
////--------------------------------------------------------
//static int count_blocks_of_line(t_tetris *tetris, int y){
//	int blocks = 0;

//	for(int x = 0; x < FIELD_X_COL; x++) {
//		blocks += tetris->playing_field[y][x];
//	}
//	return (blocks);
//}

//static void drop_block(t_tetris *tetris, int y){
//	for( ; y >= 1; y--)
//		for(int x = 0; x < FIELD_X_COL; x++)
//			tetris->playing_field[y][x] = tetris->playing_field[y-1][x];
//}

//static void clear_line(t_tetris *tetris, int y){
//	for(int x = 0; x < FIELD_X_COL; x++)
//		tetris->playing_field[y][x] = 0;
//}

////static void drop_placed_block_one_rank(t_tetris *tetris, int y){
////	drop_block(tetris, y);
////	clear_line(tetris, TOP_ROW);
////}

//int count_completed_lines_and_erase(t_tetris *tetris, int *completed_lines){
//	//int completed_lines = 0;
//	for(int y = 0; y < FIELD_Y_ROW; y++){
//		if(count_blocks_of_line(tetris, y) == FIELD_X_COL){
//			*completed_lines += 1;
//			drop_block(tetris, y);
//			clear_line(tetris, TOP_Y_ROW);
//			//drop_placed_block_one_rank(tetris, y);
//			tetris->time_to_update -= tetris->decrease--;
//		}
//	}
//	return (*completed_lines);
//}

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

//--------------------------------------------------------
// endo of count_completed_lines_and_erase
//--------------------------------------------------------

int main() {

	t_tetris tetris;
	t_tetrimino current;
	t_tetrimino type[7];
	
	init_game(&tetris);
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	memcpy(type, type_tetrimino, sizeof(type) * 1);
	begin_game(&tetris, &current, type);

//temp++を定数とか引数で設定する
    int c;
	while(tetris.game_status == IN_GAME){
		//get_char_input_from_keyboad(tetris);
		if ((c = getch()) != ERR) {
			t_tetrimino temp = copy_tetrimino(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(can_move_tetrimino(&tetris, temp))
						current.row++;
					else {
						fix_tetrimino_on_the_field(&tetris, &current);
						int count = 0;
						count_completed_lines_and_erase(&tetris, &count);
						tetris.score += 100*count;
						current = replace_next_tetrimino(&current, type);
						if(!can_move_tetrimino(&tetris, current)){
							tetris.game_status = GAME_OVER;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(can_move_tetrimino(&tetris, temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(can_move_tetrimino(&tetris, temp))
						current.col--;
					break;
				case 'w':
					rotate_clodkwise(temp);
					if(can_move_tetrimino(&tetris, temp))
						rotate_clodkwise(current);
					break;
			}
			destroy_tetrimino(temp);
			refresh_game_screen(&tetris, &current);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			t_tetrimino temp = copy_tetrimino(current);
			switch('s'){
				case 's':
					temp.row++;
					if(can_move_tetrimino(&tetris, temp))
						current.row++;
					else {
						fix_tetrimino_on_the_field(&tetris, &current);


						int n, m, sum, count=0;
						for(n=0;n<R;n++){
							sum = 0;
							for(m=0;m< C;m++) {
								sum+=tetris.playing_field[n][m];
							}
							if(sum==C){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<C;l++)
										tetris.playing_field[k][l]=tetris.playing_field[k-1][l];
								for(l=0;l<C;l++)
									tetris.playing_field[k][l]=0;
								timer-=decrease--;
							}
						}

						current = replace_next_tetrimino(&current, type);

						if(!can_move_tetrimino(&tetris, current)){
							tetris.game_status = GAME_OVER;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(can_move_tetrimino(&tetris, temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(can_move_tetrimino(&tetris, temp))
						current.col--;
					break;
				case 'w':
					rotate_clodkwise(temp);
					if(can_move_tetrimino(&tetris, temp))
						rotate_clodkwise(current);
					break;
			}
			destroy_tetrimino(temp);
			refresh_game_screen(&tetris, &current);
			gettimeofday(&before_now, NULL);
		}
	}

	// finish_game()へ
	destroy_tetrimino(current);
	endwin();
	int i, j;
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printf("%c ", tetris.playing_field[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", tetris.score);
	//
    
	return 0;
}

void begin_game(t_tetris *tetris, t_tetrimino *current, t_tetrimino *type){
	
	(void)tetris;
	*current = create_new_tetrimino(type);
	judge_the_end_of_game(tetris, *current);
	refresh_game_screen(tetris, current);
}


void rotate_clodkwise(t_tetrimino shape){
	t_tetrimino temp = copy_tetrimino(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	destroy_tetrimino(temp);
}

int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}