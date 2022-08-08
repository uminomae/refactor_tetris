#include "tetris.h"
#include "tetrimino.h"

t_tetrimino *create_tetrimino(t_tetrimino *type_tetrimino);
t_tetrimino make_new_tetrimino(t_tetrimino *type_tetrimino);
void refresh_game_screen(t_tetris *tetris);
void end_game(t_tetris *tetris,t_tetrimino current);
bool check_overlap_other_pieces(t_tetrimino *tetrimino, int i, int j);
bool can_move_not_overlapping(t_tetris *tetris, int i, int j);
int can_move_field(t_tetris *tetris, t_tetrimino *tetrimino);
//suseconds_t get_millisecond(struct timeval timevalue);
//bool need_update(t_tetris *tetris);
void roteta_tetrimino(t_tetrimino *shape);
void init_game(t_tetris *tetris);
int count_blocks_of_line(t_tetris *tetris, int y);
void lower_the_upper_block(t_tetris *tetris, int y);
void clear_line(t_tetris *tetris, int y);
void drop_placed_block_one_rank(t_tetris *tetris, int y);
int count_completed_lines_and_erase(t_tetris *tetris);
void case_d(t_tetris *tetris, t_tetrimino *temp);
void case_a(t_tetris *tetris, t_tetrimino *temp);
void case_w(t_tetris *tetris, t_tetrimino *temp,t_tetrimino current);
void fix_tetrimino_on_the_field(t_tetris *tetris);
void make_the_next_tetrimino(t_tetris *tetris);
void case_s(t_tetris *tetris, t_tetrimino *temp, bool update);
void init_game(t_tetris *tetris);
void move_tetrimino_with_key(t_tetris *tetris, bool update);

t_tetrimino current;

void init_game(t_tetris *tetris)
{
	srand(time(0));
	tetris->score = 0;
	tetris->game_status = GAME_PLAY;
	tetris->time_to_update = FALL_VELOCITY_INTERVAL;
	tetris->decrease = INTERVAL_DECREASE;
	memset(tetris->playing_field, 0, sizeof(char)*FIELD_ROW*FIELD_COL);
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout_millisecond(1);
}

void refresh_game_screen(t_tetris *tetris){
	char Buffer[FIELD_ROW][FIELD_COL] = {0};
	tetris->tetrimino = &current;
	get_current_position(tetris, Buffer);
	clear();
	print_game_screen(tetris, Buffer);
}

void start_game(t_tetris *tetris){
	current = make_new_tetrimino(type_tetrimino);
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

void end_game(t_tetris *tetris, t_tetrimino current)
{
	destroy_tetrimino(&current);
	end_ncurses();
	int i, j;
	for(i = 0; i < FIELD_ROW ;i++){
		for(j = 0; j < FIELD_COL ; j++){
			printf("%c ", tetris->playing_field[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", tetris->score);
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
t_tetrimino *create_tetrimino(t_tetrimino *type_tetrimino){
	const int y_size = type_tetrimino->width_and_height;
	t_tetrimino new_type_tetrimino = *type_tetrimino;

	new_type_tetrimino.figure = (char**)malloc(sizeof(char *) * y_size);
	copy_figure(&new_type_tetrimino, type_tetrimino->figure);
    return (&new_type_tetrimino);
}

t_tetrimino make_new_tetrimino(t_tetrimino *type_tetrimino)
{
	t_tetrimino new_figure = *create_tetrimino(&type_tetrimino[rand()%7]);

    new_figure.col = rand()%(FIELD_COL-new_figure.width_and_height+1);
    new_figure.row = 0;
	return (new_figure);
}

bool can_move_not_overlapping(t_tetris *tetris, int i, int j){
	const t_tetrimino *tetrimino = tetris->tetrimino;
	//const t_tetrimino *tetrimino = &current;;
	if (tetris->playing_field[tetrimino->row + i][tetrimino->col + j] && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

int can_move_field(t_tetris *tetris, t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			if (!can_move_left(tetrimino, i, j))
				return FALSE;
			if (!can_move_right(tetrimino, i, j))
				return FALSE;
			if (!can_move_bottom(tetrimino, i, j))
				return FALSE;
			if (!can_move_not_overlapping(tetris, i, j))
				return FALSE;
		}
	}
	return TRUE;
}

void roteta_tetrimino(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;
	t_tetrimino *temp = create_tetrimino(tetrimino);
	int i, j, k;

	for(i = 0; i < n ; i++){
		for(j = 0, k = n - 1; j < n ; j++, k--){
				tetrimino->figure[i][j] = temp->figure[k][i];
		}
	}
	destroy_tetrimino(temp);
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

void case_d(t_tetris *tetris, t_tetrimino *temp)
{
	temp->col++;
	if(can_move_field(tetris, temp))
		current.col++;
}

void case_a(t_tetris *tetris, t_tetrimino *temp)
{
	temp->col--;
	if(can_move_field(tetris, temp))
		current.col--;
}

void case_w(t_tetris *tetris, t_tetrimino *temp,t_tetrimino current)
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
	t_tetrimino new_shape = *create_tetrimino(&type_tetrimino[rand()%7]);
	new_shape.col = rand()%(FIELD_COL-new_shape.width_and_height+1);
	new_shape.row = 0;
	destroy_tetrimino(&current);
	current = new_shape;
	if(!can_move_field(tetris, &current)){
		tetris->game_status = GAME_OVER;
	}
}

void case_s(t_tetris *tetris, t_tetrimino *temp, bool update){
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

//void move_tetrimino_with_key(t_tetris *tetris, bool update){
//	int key = tetris->input_from_keyboard;
//	t_tetrimino temp_for_change_whith_key = *create_tetrimino(&current);

//	if (key == DROP_KEY){
//		case_s(tetris, &temp_for_change_whith_key, update);
//	}else if (key == RIGHT_KEY){
//		case_d(tetris, &temp_for_change_whith_key);
//	}else if (key == LEFT_KEY){
//		case_a(tetris, &temp_for_change_whith_key);
//	}else if (key == ROTATE_KEY){
//		case_w(tetris, &temp_for_change_whith_key, current);
//	}
//	destroy_tetrimino(&temp_for_change_whith_key);
//	refresh_game_screen(tetris);
//}
void move_tetrimino_with_key(t_tetris *tetris, bool update){
	int key = tetris->input_from_keyboard;
	t_tetrimino for_judg_move = *create_tetrimino(&current);

	if (key == DROP_KEY){
		case_s(tetris, &for_judg_move, update);
	}else if (key == RIGHT_KEY){
		case_d(tetris, &for_judg_move);
	}else if (key == LEFT_KEY){
		case_a(tetris, &for_judg_move);
	}else if (key == ROTATE_KEY){
		case_w(tetris, &for_judg_move, current);
	}
	destroy_tetrimino(&for_judg_move);
	refresh_game_screen(tetris);
}