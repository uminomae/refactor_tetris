#include "tetris.h"
#include "tetrimino.h"

void refresh_game_screen(t_tetris *tetris);

bool check_overlap_other_pieces(t_tetrimino *tetrimino, int i, int j);
int count_blocks_of_line(t_tetris *tetris, int y);
void lower_the_upper_block(t_tetris *tetris, int y);
void clear_line(t_tetris *tetris, int y);
void drop_placed_block_one_rank(t_tetris *tetris, int y);
int count_completed_lines_and_erase(t_tetris *tetris);
void move_case_d(t_tetris *tetris, t_tetrimino *temp);
void move_case_a(t_tetris *tetris, t_tetrimino *temp);
void move_case_w(t_tetris *tetris, t_tetrimino *temp,t_tetrimino current);
void fix_tetrimino_on_the_field(t_tetris *tetris);
void make_the_next_tetrimino(t_tetris *tetris);
void move_case_s(t_tetris *tetris, t_tetrimino *temp, bool update);
void move_tetrimino_with_key(t_tetris *tetris, bool update);

t_tetrimino current;

void refresh_game_screen(t_tetris *tetris){
	char next_playing_field[FIELD_ROW][FIELD_COL] = {0};
	
	tetris->tetrimino = &current;
	get_current_position(tetris, next_playing_field);
	clear();
	print_game_screen(tetris, next_playing_field);
}

void start_game(t_tetris *tetris){
	current = create_new_tetrimino(type_tetrimino);
	if(!can_move_field(tetris, &current)){
		tetris->game_status = GAME_OVER;
	}
    refresh_game_screen(tetris);
}

void run_game(t_tetris *tetris){
	while(tetris->game_status == GAME_PLAY){
    	tetris->input_from_keyboard = getch();
		if (tetris->input_from_keyboard != ERR) {
			move_tetrimino_with_key(tetris, false);
		}
		gettimeofday(&now, NULL);
		if (need_update(tetris)) {
			tetris->input_from_keyboard = 's';
			move_tetrimino_with_key(tetris, true);
			gettimeofday(&before_now, NULL);
		}
	}
}

int main() {
	t_tetris tetris;

	init_game(&tetris);
	start_game(&tetris);
	run_game(&tetris);
	end_game(&tetris, current);
    return 0;
}

//--------------------------------------------------------
//
//

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

void move_case_d(t_tetris *tetris, t_tetrimino *temp)
{
	temp->col++;
	if(can_move_field(tetris, temp))
		current.col++;
}

void move_case_a(t_tetris *tetris, t_tetrimino *temp)
{
	temp->col--;
	if(can_move_field(tetris, temp))
		current.col--;
}

void move_case_w(t_tetris *tetris, t_tetrimino *temp,t_tetrimino current)
{
	roteta_tetrimino(temp);
	if(can_move_field(tetris, temp))
		roteta_tetrimino(&current);
}

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

void make_the_next_tetrimino(t_tetris *tetris){
	t_tetrimino new_shape = *copy_tetrimino_type(&type_tetrimino[rand()%7]);
	new_shape.col = rand()%(FIELD_COL-new_shape.width_and_height+1);
	new_shape.row = 0;
	destroy_tetrimino(&current);
	current = new_shape;
	if(!can_move_field(tetris, &current)){
		tetris->game_status = GAME_OVER;
	}
}

void move_case_s(t_tetris *tetris, t_tetrimino *temp, bool update){
	temp->row++;
	if(can_move_field(tetris, temp))
		current.row++;
	else {
		fix_tetrimino_on_the_field(tetris);
		int completed_lines = count_completed_lines_and_erase(tetris);
		if (update == false)
			tetris->score += 100 * completed_lines;
		make_the_next_tetrimino(tetris);
	}
}

void move_tetrimino_with_key(t_tetris *tetris, bool update){
	int key = tetris->input_from_keyboard;
	t_tetrimino for_judg_move = *copy_tetrimino_type(&current);

	if (key == DROP_KEY){
		move_case_s(tetris, &for_judg_move, update);
	}else if (key == RIGHT_KEY){
		move_case_d(tetris, &for_judg_move);
	}else if (key == LEFT_KEY){
		move_case_a(tetris, &for_judg_move);
	}else if (key == ROTATE_KEY){
		move_case_w(tetris, &for_judg_move, current);
	}
	destroy_tetrimino(&for_judg_move);
	refresh_game_screen(tetris);
}