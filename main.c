#include "tetris.h"
#include "tetrimino.h"

char playig_field[FIELD_ROW][FIELD_COL] = {0};
//int final = 0;
char game_status = GAME_PLAY;

suseconds_t timer = 400000;
int decrease = 1000;
t_tetrimino current;

//mallocするだけの関数つくる
t_tetrimino create_shape(t_tetrimino shape){
	t_tetrimino new_shape = shape;
	char **copyshape = shape.array;
	new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
		new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}

//destroy
void destroy_shape(t_tetrimino shape){
    int i;
    for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
    }
    free(shape.array);
}

//current_position?
int FunctionCP(t_tetrimino shape){
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= FIELD_COL || shape.row+i >= FIELD_ROW)){
				if(array[i][j])
					return FALSE;
				
			}
			else if(playig_field[shape.row+i][shape.col+j] && array[i][j])
				return FALSE;
		}
	}
	return TRUE;
}

void FunctionRS(t_tetrimino shape){
	t_tetrimino temp = create_shape(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	destroy_shape(temp);
}

void output_to_screen(char *str,...)
{
	printw(str);
}

//printw
void FunctionPT(t_tetris *tetris){
	char Buffer[FIELD_ROW][FIELD_COL] = {0};
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	clear();
	for(i=0; i<FIELD_COL-9; i++)
		output_to_screen(" ");
	output_to_screen("42 Tetris\n");
	for(i = 0; i < FIELD_ROW ;i++){
		for(j = 0; j < FIELD_COL ; j++){
			output_to_screen("%c ", (playig_field[i][j] + Buffer[i][j])? '#': '.');
		}
		output_to_screen("\n");
	}
	output_to_screen("\nScore: %d\n", tetris->score);
	//output_to_screen("\nScore: %d\n", final);
}

struct timeval before_now, now;
//struct timeval {
//    time_t      tv_sec;     /* 秒 */
//    suseconds_t tv_usec;    /* マイクロ秒 */
//};
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

static void end_ncurses()
{
	endwin();
}

void end_of_game(t_tetris *tetris,t_tetrimino current)
//void end_of_game(t_tetrimino current)
{
	destroy_shape(current);
	end_ncurses();
	//endwin();
	int i, j;
	for(i = 0; i < FIELD_ROW ;i++){
		for(j = 0; j < FIELD_COL ; j++){
			printf("%c ", playig_field[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", tetris->score);
	//printf("\nScore: %d\n", final);
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

void init_game(t_tetris tetris)
{
	tetris.score = 0;
}

//srand関数はrand関数の擬似乱数の発生系列を変更する関数
//initscr()： スクリーンを初期化する． （curses を利用する場合，最初に呼び出さなければならない．）
int main() {
	t_tetris tetris;

    srand(time(0));//srand((unsigned int)time(NULL));
	init_game(tetris);
    int input_from_the_keyboard;
    //tetris.score = 0;
    initscr(); //スクリーンを初期化する
	gettimeofday(&before_now, NULL);//時刻を取得する
	set_timeout(1);//1返す理由は？
	t_tetrimino new_shape = create_shape(type_tetrimino[rand()%7]);//7種類の形
    new_shape.col = rand()%(FIELD_COL-new_shape.width+1);//0 + rand() % 10) // 最小値:0 取得個数:10個
    new_shape.row = 0;//最上段
    //destroy_shape(current);//destoy
	current = new_shape;//create_shapeしたもの
	if(!FunctionCP(current)){
		game_status = GAME_OVER;
		//game_status = FALSE;
	}
	
    FunctionPT(&tetris);
	while(game_status == GAME_PLAY){
		if ((input_from_the_keyboard = getch()) != ERR) {
			t_tetrimino temp = create_shape(current);
			switch(input_from_the_keyboard){
				case 's':
					temp.row++;  //move down
					if(FunctionCP(temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									playig_field[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<FIELD_ROW;n++){
							sum = 0;
							for(m=0;m< FIELD_COL;m++) {
								sum+=playig_field[n][m];
							}
							if(sum==FIELD_COL){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<FIELD_COL;l++)
										playig_field[k][l]=playig_field[k-1][l];
								for(l=0;l<FIELD_COL;l++)
									playig_field[k][l]=0;
								timer-=decrease--;
							}
						}
						tetris.score += 100*count;
						//final += 100*count;
						t_tetrimino new_shape = create_shape(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(FIELD_COL-new_shape.width+1);
						new_shape.row = 0;
						destroy_shape(current);
						current = new_shape;
						if(!FunctionCP(current)){
							game_status = GAME_OVER;
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
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									playig_field[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<FIELD_ROW;n++){
							sum = 0;
							for(m=0;m< FIELD_COL;m++) {
								sum+=playig_field[n][m];
							}
							if(sum==FIELD_COL){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<FIELD_COL;l++)
										playig_field[k][l]=playig_field[k-1][l];
								for(l=0;l<FIELD_COL;l++)
									playig_field[k][l]=0;
								timer-=decrease--;
							}
						}
						t_tetrimino new_shape = create_shape(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(FIELD_COL-new_shape.width+1);
						new_shape.row = 0;
						destroy_shape(current);
						current = new_shape;
						if(!FunctionCP(current)){
							game_status = GAME_OVER;
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

