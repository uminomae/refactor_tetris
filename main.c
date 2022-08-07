#include "tetris.h"
#include "tetrimino.h"

t_tetrimino *create_tetrimino(t_tetrimino *type_tetrimino);
t_tetrimino make_new_tetrimino(t_tetrimino *type_tetrimino);
void refresh_game_screen(t_tetris *tetris);
void end_of_game(t_tetris *tetris,t_tetrimino current);
bool check_overlap_other_pieces(t_tetrimino *tetrimino, int i, int j);
int can_move_field(t_tetrimino *tetrimino);
bool can_move_not_overlapping(t_tetrimino *tetrimino, int i, int j);
int can_move_field(t_tetrimino *tetrimino);
suseconds_t get_millisecond(struct timeval timevalue);
bool hasToUpdate();
void roteta_tetrimino(t_tetrimino shape);
void init_game(t_tetris *tetris);
int count_blocks_of_line(int y);
void lower_the_upper_block(int y);
void clear_line(int y);
void drop_placed_block_one_rank(int y);
int count_completed_lines_and_erase();
void case_d(t_tetrimino temp);
void case_a(t_tetrimino temp);
void case_w(t_tetrimino temp,t_tetrimino current);

char playing_field[FIELD_ROW][FIELD_COL] = {0};
suseconds_t timer = FALL_VELOCITY_INTERVAL;
int decrease = INTERVAL_DECREASE;
t_tetrimino current;


void fix_tetrimino_on_the_field(){
	const int n = current.width_and_height;
	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(current.figure[i][j])
				playing_field[current.row+i][current.col+j] = current.figure[i][j];
		}
	}
}

void make_the_next_tetrimino(t_tetris *tetris){
	t_tetrimino new_shape = *create_tetrimino(&type_tetrimino[rand()%7]);
	new_shape.col = rand()%(FIELD_COL-new_shape.width_and_height+1);
	new_shape.row = 0;
	destroy_tetrimino(&current);
	current = new_shape;
	if(!can_move_field(&current)){
		tetris->game_status = GAME_OVER;
	}
}

void case_s(t_tetris *tetris,t_tetrimino temp, bool update){
	temp.row++;
	if(can_move_field(&temp))
		current.row++;
	else {
		fix_tetrimino_on_the_field();
		int completed_lines = count_completed_lines_and_erase();
		if (update == false)
			tetris->score += 100 * completed_lines;
		make_the_next_tetrimino(tetris);
	}
}

void move_tetrimino_with_key(t_tetris *tetris, bool update){
	int key = tetris->input_from_keyboard;
	t_tetrimino temp = *create_tetrimino(&current);

	if (key == DROP_KEY){
		case_s(tetris, temp, update);
	}else if (key == RIGHT_KEY){
		case_d(temp);
	}else if (key == LEFT_KEY){
		case_a(temp);
	}else if (key == ROTATE_KEY){
		case_w(temp,current);
	}
	destroy_tetrimino(&temp);
	refresh_game_screen(tetris);
}

//srand関数はrand関数の擬似乱数の発生系列を変更する関数 //srand((unsigned int)time(NULL));
//getch()標準入力(キーボード)から1文字読み込み、その文字を返します。
int main() {
	t_tetris tetris;
	t_tetrimino tetrimino;

    srand(time(0));
	init_game(&tetris);
	current = make_new_tetrimino(type_tetrimino);
	if(!can_move_field(&current)){
		tetris.game_status = GAME_OVER;
	}
    refresh_game_screen(&tetris);
	while(tetris.game_status == GAME_PLAY){
    	tetris.input_from_keyboard = getch();
		if (tetris.input_from_keyboard != ERR) {
			move_tetrimino_with_key(&tetris, false);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			tetris.input_from_keyboard = 's';
			move_tetrimino_with_key(&tetris, true);
			gettimeofday(&before_now, NULL);
		}
	}
	end_of_game(&tetris,current);
    return 0;
}



//--------------------------------------------------------
//
//


//構造体型はmalloc失敗時にNULL返す方法を質問する
t_tetrimino *create_tetrimino(t_tetrimino *type_tetrimino){
	const int y_size = type_tetrimino->width_and_height;
	t_tetrimino new_type_tetrimino = *type_tetrimino;

	new_type_tetrimino.figure = (char**)malloc(sizeof(char *) * y_size);
	copy_figure(&new_type_tetrimino, type_tetrimino->figure);
    return (&new_type_tetrimino);
}


//7種類の形
//0 + rand() % 10) // 最小値:0 取得個数:10個
t_tetrimino make_new_tetrimino(t_tetrimino *type_tetrimino)
{
	t_tetrimino new_figure = *create_tetrimino(&type_tetrimino[rand()%7]);

    new_figure.col = rand()%(FIELD_COL-new_figure.width_and_height+1);
    new_figure.row = 0;
	return (new_figure);
}


////printw
////clear() スクリーンをリフレッシュする
void refresh_game_screen(t_tetris *tetris){
	
	char Buffer[FIELD_ROW][FIELD_COL] = {0};
	tetris->tetrimino = &current;
	memcpy(tetris->playing_field, playing_field, sizeof(char) * FIELD_ROW * FIELD_COL);

	get_current_position(tetris, Buffer);
	clear();
	print_game_screen(tetris, Buffer);
}


void end_of_game(t_tetris *tetris,t_tetrimino current)
{
	destroy_tetrimino(&current);
	end_ncurses();
	int i, j;
	for(i = 0; i < FIELD_ROW ;i++){
		for(j = 0; j < FIELD_COL ; j++){
			printf("%c ", playing_field[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", tetris->score);
}

bool can_move_not_overlapping(t_tetrimino *tetrimino, int i, int j){
	if (playing_field[tetrimino->row + i][tetrimino->col + j] && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

//exists_in_fieldでtrueにしたい
int can_move_field(t_tetrimino *tetrimino){
	const int n = tetrimino->width_and_height;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			if (!can_move_left(tetrimino, i, j))
				return FALSE;
			if (!can_move_right(tetrimino, i, j))
				return FALSE;
			if (!can_move_bottom(tetrimino, i, j))
				return FALSE;
			if (!can_move_not_overlapping(tetrimino, i, j))
				return FALSE;
		}
	}
	return TRUE;
}

////struct timeval {
////    time_t      tv_sec;     /* 秒 */
////    suseconds_t tv_usec;    /* マイクロ秒 */
////};
suseconds_t get_millisecond(struct timeval timevalue){
	return (timevalue.tv_sec * MILLION + timevalue.tv_usec);
}

bool hasToUpdate(){
	const suseconds_t now_ms = get_millisecond(now);
	const suseconds_t before_now_ms = get_millisecond(before_now);
	return (now_ms - before_now_ms > timer);
}


void roteta_tetrimino(t_tetrimino shape){
	const int n = shape.width_and_height;
	t_tetrimino temp = *create_tetrimino(&shape);
	int i, j, k;

	for(i = 0; i < n ; i++){
		for(j = 0, k = n - 1; j < n ; j++, k--){
				shape.figure[i][j] = temp.figure[k][i];
		}
	}
	destroy_tetrimino(&temp);
}

////struct timeval before_now, now;
//int hasToUpdate(){
//	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
//}


//initscr()： スクリーンを初期化する． （curses を利用する場合，最初に呼び出さなければならない．）
void init_game(t_tetris *tetris)
{
	tetris->score = 0;
	tetris->game_status = GAME_PLAY;
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout_millisecond(1);
}


int count_blocks_of_line(int y){
	int blocks = 0;

	for(int x = 0; x < FIELD_COL; x++) {
		blocks += playing_field[y][x];
	}
	return (blocks);
}

void lower_the_upper_block(int y){
	for( ; y >= 1; y--)
		for(int x = 0; x < FIELD_COL; x++)
			playing_field[y][x]=playing_field[y-1][x];
}

void clear_line(int y){
	for(int x = 0; x < FIELD_COL; x++)
		playing_field[y][x] = 0;
}

void drop_placed_block_one_rank(int y){
	lower_the_upper_block(y);
	clear_line(TOP_ROW);
}

int count_completed_lines_and_erase(){
	int number_of_completed_lines = 0;
	for(int y = 0; y < FIELD_ROW; y++){
		if(count_blocks_of_line(y) == FIELD_COL){
			drop_placed_block_one_rank(y);
			timer -= decrease--;
			number_of_completed_lines++;
		}
	}
	return (number_of_completed_lines);
}

void case_d(t_tetrimino temp)
{
	temp.col++;
	if(can_move_field(&temp))
		current.col++;
}

void case_a(t_tetrimino temp)
{
	temp.col--;
	if(can_move_field(&temp))
		current.col--;
}

void case_w(t_tetrimino temp,t_tetrimino current)
{
	roteta_tetrimino(temp);
	if(can_move_field(&temp))
		roteta_tetrimino(current);
}
