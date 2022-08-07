#include "tetris.h"
#include "tetrimino.h"

t_tetrimino make_new_tetrimino(const t_tetrimino *type_tetrimino);
void refresh_game_screen(t_tetris *tetris);
void end_of_game(t_tetris *tetris,t_tetrimino current);

char playing_field[FIELD_ROW][FIELD_COL] = {0};
suseconds_t timer = 400000;
int decrease = 1000;
t_tetrimino current;


bool check_left(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->col+ j < 0 && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

bool check_right(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->col + j >= FIELD_COL && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

bool check_bottom(t_tetrimino *tetrimino, int i, int j){
	if (tetrimino->row + i >= FIELD_ROW && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

bool check_overlap_other_pieces(t_tetrimino *tetrimino, int i, int j){
	if (playing_field[tetrimino->row + i][tetrimino->col + j] && tetrimino->figure[i][j])
		return FALSE;
	return TRUE;
}

//exists_in_fieldでtrueにしたい
int can_move_field(t_tetrimino *tetrimino){
//int can_move_field(t_tetris *tetris, t_tetrimino tetrimino){
	const int n = tetrimino->width_and_height;
	//tetris->playing_field = playing_field;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			if (!check_left(tetrimino, i, j))
				return FALSE;
			if (!check_right(tetrimino, i, j))
				return FALSE;
			if (!check_bottom(tetrimino, i, j))
				return FALSE;
			if (!check_overlap_other_pieces(tetrimino, i, j))
				return FALSE;
		}
	}
	return TRUE;
}

//int can_move_field(t_tetrimino tetrimino){
//	const int n = tetrimino.width_and_height;
//	char **array = tetrimino.figure;

//	for(int i = 0; i < n; i++) {
//		for(int j = 0; j < n; j++){
//			if((tetrimino.col+j < 0 || tetrimino.col+j >= FIELD_COL || tetrimino.row+i >= FIELD_ROW)){
//				if(array[i][j])
//					return FALSE;
//			}
//			else if(playing_field[tetrimino.row+i][tetrimino.col+j] && array[i][j])
//				return FALSE;
//		}
//	}
//	return TRUE;
//}

void FunctionRS(t_tetrimino shape){
	t_tetrimino temp = create_tetrimino(shape);
	int i, j, k, width_and_height;
	width_and_height = shape.width_and_height;
	for(i = 0; i < width_and_height ; i++){
		for(j = 0, k = width_and_height-1; j < width_and_height ; j++, k--){
				shape.figure[i][j] = temp.figure[k][i];
		}
	}
	destroy_tetrimino(&temp);
}


//struct timeval before_now, now;
//struct timeval {
//    time_t      tv_sec;     /* 秒 */
//    suseconds_t tv_usec;    /* マイクロ秒 */
//};
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
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
	FunctionRS(temp);
	if(can_move_field(&temp))
		FunctionRS(current);
}

//initscr()： スクリーンを初期化する． （curses を利用する場合，最初に呼び出さなければならない．）
void init_game(t_tetris *tetris)
{
	tetris->score = 0;
	tetris->game_status = GAME_PLAY;
	initscr();
	gettimeofday(&before_now, NULL);
	set_timeout_millisecond(1);
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
    	int input_from_keyboard;
		if ((input_from_keyboard = getch()) != ERR) {
			t_tetrimino temp = create_tetrimino(current);
			switch(input_from_keyboard){
				case 's':
					temp.row++;  //move down
					if(can_move_field(&temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width_and_height ;i++){
							for(j = 0; j < current.width_and_height ; j++){
								if(current.figure[i][j])
									playing_field[current.row+i][current.col+j] = current.figure[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<FIELD_ROW;n++){
							sum = 0;
							for(m=0;m< FIELD_COL;m++) {
								sum+=playing_field[n][m];
							}
							if(sum==FIELD_COL){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<FIELD_COL;l++)
										playing_field[k][l]=playing_field[k-1][l];
								for(l=0;l<FIELD_COL;l++)
									playing_field[k][l]=0;
								timer-=decrease--;
							}
						}
						tetris.score += 100*count;
						//final += 100*count;
						t_tetrimino new_shape = create_tetrimino(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(FIELD_COL-new_shape.width_and_height+1);
						new_shape.row = 0;
						destroy_tetrimino(&current);
						current = new_shape;
						if(!can_move_field(&current)){
							tetris.game_status = GAME_OVER;
						}
					}
					break;
				case 'd':
					case_d(temp);
					break;
				case 'a':
					case_a(temp);
					break;
				case 'w':
					case_w(temp,current);
					break;
			}
			destroy_tetrimino(&temp);
			refresh_game_screen(&tetris);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			t_tetrimino temp = create_tetrimino(current);
			switch('s'){
				case 's':
					temp.row++;
					if(can_move_field(&temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width_and_height ;i++){
							for(j = 0; j < current.width_and_height ; j++){
								if(current.figure[i][j])
									playing_field[current.row+i][current.col+j] = current.figure[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<FIELD_ROW;n++){
							sum = 0;
							for(m=0;m< FIELD_COL;m++) {
								sum+=playing_field[n][m];
							}
							if(sum==FIELD_COL){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<FIELD_COL;l++)
										playing_field[k][l]=playing_field[k-1][l];
								for(l=0;l<FIELD_COL;l++)
									playing_field[k][l]=0;
								timer-=decrease--;
							}
						}
						t_tetrimino new_shape = create_tetrimino(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(FIELD_COL-new_shape.width_and_height+1);
						new_shape.row = 0;
						destroy_tetrimino(&current);
						current = new_shape;
						if(!can_move_field(&current)){
							tetris.game_status = GAME_OVER;
						}
					}
					break;
				case 'd':
					case_d(temp);
					break;
				case 'a':
					case_a(temp);
					break;
				case 'w':
					case_w(temp,current);
					break;
			}
			destroy_tetrimino(&temp);
			refresh_game_screen(&tetris);
			gettimeofday(&before_now, NULL);
		}
	}
	end_of_game(&tetris,current);
    return 0;
}



//--------------------------------------------------------
//
//

//7種類の形
//0 + rand() % 10) // 最小値:0 取得個数:10個
t_tetrimino make_new_tetrimino(const t_tetrimino *type_tetrimino)
{
	t_tetrimino new_figure = create_tetrimino(type_tetrimino[rand()%7]);

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