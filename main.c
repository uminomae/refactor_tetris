#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

#define ROW 20
//#define R 20
#define COL 15
//#define C 15
#define TRUE 1
//#define T 1
#define FALSE 0
//#define F 0

char Table[ROW][COL] = {0};
int final = 0;
char GameOn = TRUE;
suseconds_t timer = 400000;
int decrease = 1000;

typedef struct {
    char **array;
    int width, row, col;
} Struct;
Struct current;

const Struct StructsArray[7]= {
	{
		(char *[]){
			(char []){0,1,1},
			(char []){1,1,0}, 
			(char []){0,0,0}
			}
			,3
	},
	{
		(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

//create shape
Struct FunctionCS(Struct shape){
	Struct new_shape = shape;
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
void FunctionDS(Struct shape){
    int i;
    for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
    }
    free(shape.array);
}

int FunctionCP(Struct shape){
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= COL || shape.row+i >= ROW)){
				if(array[i][j])
					return FALSE;
				
			}
			else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return FALSE;
		}
	}
	return TRUE;
}

void FunctionRS(Struct shape){
	Struct temp = FunctionCS(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	FunctionDS(temp);
}

void FunctionPT(){
	char Buffer[ROW][COL] = {0};
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	clear();
	for(i=0; i<COL-9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < ROW ;i++){
		for(j = 0; j < COL ; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
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

//srand関数はrand関数の擬似乱数の発生系列を変更する関数
//initscr()： スクリーンを初期化する． （curses を利用する場合，最初に呼び出さなければならない．）
int main() {
    srand(time(0));//srand((unsigned int)time(NULL));
    final = 0;
    int c;
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);//1返す理由は？
	Struct new_shape = FunctionCS(StructsArray[rand()%7]);//7種類の形
    new_shape.col = rand()%(COL-new_shape.width+1);//0 + rand() % 10) // 最小値:0 取得個数:10個
    new_shape.row = 0;//最上段
    FunctionDS(current);
	current = new_shape;
	if(!FunctionCP(current)){
		GameOn = FALSE;
	}
	
    FunctionPT();
	while(GameOn){
		if ((c = getch()) != ERR) {
			Struct temp = FunctionCS(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(FunctionCP(temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									Table[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<ROW;n++){
							sum = 0;
							for(m=0;m< COL;m++) {
								sum+=Table[n][m];
							}
							if(sum==COL){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<COL;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<COL;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						final += 100*count;
						Struct new_shape = FunctionCS(StructsArray[rand()%7]);
						new_shape.col = rand()%(COL-new_shape.width+1);
						new_shape.row = 0;
						FunctionDS(current);
						current = new_shape;
						if(!FunctionCP(current)){
							GameOn = FALSE;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp);
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			FunctionDS(temp);
			FunctionPT();
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			Struct temp = FunctionCS(current);
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
									Table[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<ROW;n++){
							sum = 0;
							for(m=0;m< COL;m++) {
								sum+=Table[n][m];
							}
							if(sum==COL){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<C;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<C;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						Struct new_shape = FunctionCS(StructsArray[rand()%7]);
						new_shape.col = rand()%(COL-new_shape.width+1);
						new_shape.row = 0;
						FunctionDS(current);
						current = new_shape;
						if(!FunctionCP(current)){
							GameOn = FALSE;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp);
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			FunctionDS(temp);
			FunctionPT();
			gettimeofday(&before_now, NULL);
		}
	}
	FunctionDS(current);
	endwin();
	int i, j;
	for(i = 0; i < ROW ;i++){
		for(j = 0; j < COL ; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
    return 0;
}
