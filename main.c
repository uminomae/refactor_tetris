#include "tetris.h"
#include "tetrimino.h"

char playing_field[FIELD_ROW][FIELD_COL] = {0};
suseconds_t timer = 400000;
int decrease = 1000;
t_tetrimino current;

// constの設定がうまくいかないので質問する
void copy_figure(t_tetrimino *new_tetrimino, char **type_tetrimino_figure)
{
	const int n = new_tetrimino->width_and_height;

	for(int x = 0; x < n; x++){
		new_tetrimino->figure[x] = (char*)malloc(sizeof(char) * n);
		for(int y = 0; y < n; y++) {
			new_tetrimino->figure[x][y] = type_tetrimino_figure[x][y];
		}
	}
}

//構造体型はmalloc失敗時にNULL返す方法を質問する
t_tetrimino create_shape(const t_tetrimino type_tetrimino){
	const int n = type_tetrimino.width_and_height;
	t_tetrimino new_type_tetrimino = type_tetrimino;

	new_type_tetrimino.figure = (char**)malloc(sizeof(char *) * n);
	copy_figure(&new_type_tetrimino, type_tetrimino.figure);
    return (new_type_tetrimino);
}

//7種類の形
//0 + rand() % 10) // 最小値:0 取得個数:10個
t_tetrimino make_new_tetrimino(const t_tetrimino *type_tetrimino)
{
	t_tetrimino new_figure = create_shape(type_tetrimino[rand()%7]);
    new_figure.col = rand()%(FIELD_COL-new_figure.width_and_height+1);
    new_figure.row = 0;
	return (new_figure);
}

//destroy
void destroy_shape(t_tetrimino shape){
    int i;
    for(i = 0; i < shape.width_and_height; i++){
		free(shape.figure[i]);
    }
    free(shape.figure);
}

//current_position?
int FunctionCP(t_tetrimino shape){
	char **array = shape.figure;
	int i, j;
	for(i = 0; i < shape.width_and_height;i++) {
		for(j = 0; j < shape.width_and_height ;j++){
			if((shape.col+j < 0 || shape.col+j >= FIELD_COL || shape.row+i >= FIELD_ROW)){
				if(array[i][j])
					return FALSE;
				
			}
			else if(playing_field[shape.row+i][shape.col+j] && array[i][j])
				return FALSE;
		}
	}
	return TRUE;
}

void FunctionRS(t_tetrimino shape){
	t_tetrimino temp = create_shape(shape);
	int i, j, k, width_and_height;
	width_and_height = shape.width_and_height;
	for(i = 0; i < width_and_height ; i++){
		for(j = 0, k = width_and_height-1; j < width_and_height ; j++, k--){
				shape.figure[i][j] = temp.figure[k][i];
		}
	}
	destroy_shape(temp);
}

//printw
void FunctionPT(t_tetris *tetris){
	char Buffer[FIELD_ROW][FIELD_COL] = {0};
	int i, j;
	for(i = 0; i < current.width_and_height ;i++){
		for(j = 0; j < current.width_and_height ; j++){
			if(current.figure[i][j])
				Buffer[current.row+i][current.col+j] = current.figure[i][j];
		}
	}
	clear();
	for(i=0; i<FIELD_COL-9; i++)
		output_to_screen(" ");
	output_to_screen("42 Tetris\n");
	for(i = 0; i < FIELD_ROW ;i++){
		for(j = 0; j < FIELD_COL ; j++){
			output_to_screen("%c ", (playing_field[i][j] + Buffer[i][j])? '#': '.');
		}
		output_to_screen("\n");
	}
	output_to_screen("\nScore: %d\n", tetris->score);
}

//struct timeval before_now, now;
//struct timeval {
//    time_t      tv_sec;     /* 秒 */
//    suseconds_t tv_usec;    /* マイクロ秒 */
//};
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void end_of_game(t_tetris *tetris,t_tetrimino current)
{
	destroy_shape(current);
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

void case_d(t_tetrimino temp)
{
	temp.col++;
	if(FunctionCP(temp))
		current.col++;
}

void case_a(t_tetrimino temp)
{
	temp.col--;
	if(FunctionCP(temp))
		current.col--;
}

void case_w(t_tetrimino temp,t_tetrimino current)
{
	FunctionRS(temp);
	if(FunctionCP(temp))
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
	if(!FunctionCP(current)){
		tetris.game_status = GAME_OVER;
	}
	
    FunctionPT(&tetris);
	while(tetris.game_status == GAME_PLAY){
    	int input_from_keyboard;
		if ((input_from_keyboard = getch()) != ERR) {
			t_tetrimino temp = create_shape(current);
			switch(input_from_keyboard){
				case 's':
					temp.row++;  //move down
					if(FunctionCP(temp))
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
						t_tetrimino new_shape = create_shape(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(FIELD_COL-new_shape.width_and_height+1);
						new_shape.row = 0;
						destroy_shape(current);
						current = new_shape;
						if(!FunctionCP(current)){
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
			destroy_shape(temp);
			FunctionPT(&tetris);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			t_tetrimino temp = create_shape(current);
			switch('s'){
				case 's':
					temp.row++;
					if(FunctionCP(temp))
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
						t_tetrimino new_shape = create_shape(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(FIELD_COL-new_shape.width_and_height+1);
						new_shape.row = 0;
						destroy_shape(current);
						current = new_shape;
						if(!FunctionCP(current)){
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
			destroy_shape(temp);
			FunctionPT(&tetris);
			gettimeofday(&before_now, NULL);
		}
	}
	end_of_game(&tetris,current);
    return 0;
}

