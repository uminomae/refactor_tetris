#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

# include <string.h>
# include <stdbool.h>
# include "main.h"


# define S_FIGURE \
	.array = { \
		{0,1,1}, \
		{1,1,0}, \
		{0,0,0} \
	},\
	.width = 3,
# define Z_FIGURE \
	.array = {\
		{1,1,0},\
		{0,1,1},\
		{0,0,0}\
	}, \
	.width = 3,
# define T_FIGURE \
	.array = {\
		{0,1,0},\
		{1,1,1},\
		{0,0,0}\
	}, \
	.width = 3,
# define L_FIGURE \
	.array = {\
		{0,0,1},\
		{1,1,1},\
		{0,0,0}\
	}, \
	.width = 3,
# define J_FIGURE \
	.array = {\
		{1,0,0},\
		{1,1,1},\
		{0,0,0}\
	}, \
	.width = 3,
# define O_FIGURE \
	.array = {\
		{1,1},\
		{1,1}\
	}, \
	.width = 2,
# define I_FIGURE \
	.array = {\
		{0,0,0,0},\
		{1,1,1,1},\
		{0,0,0,0},\
		{0,0,0,0}\
	}, \
	.width = 4,

# define FALL_VELOCITY_INTERVAL	400000
# define INTERVAL_DECREASE	1000
# define NUM_OF_TYPE	7



#define R 20
#define C 15
#define T 1
#define F 0

char Table[R][C] = {0};
int final = 0;
char GameOn = T;
suseconds_t timer = 400000;
int decrease = 1000;

typedef struct {
    char array[4][4];
    //char **array;
    int width, row, col;
} Struct;

typedef struct s_tetris{
	int 		score;
	//char 		game_status;
	//struct s_tetrimino *tetrimino;
	//struct Struct type[NUM_OF_TYPE];
	//suseconds_t time_to_update;
	//int 		decrease;
	//char		playing_field[FIELD_ROW][FIELD_COL];
	//int 		input_from_keyboard;
	//struct s_time *timer;
} t_tetris;

Struct current;

const Struct StructsArray[] = {
		{
			S_FIGURE
		},
		{
			Z_FIGURE
		},
		{
			T_FIGURE
		},
		{
			L_FIGURE
		},
		{
			J_FIGURE
		},
		{
			O_FIGURE
		},
		{
			I_FIGURE
		}
	};


//const Struct StructsArray[7]= {
//	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
//	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
//	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
//	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
//	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
//	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
//	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
//};

//static void copy_figure_array(char new[4][4], \
//							char type_tetrimino_figure[4][4], \
//							int width_and_height){
//	const int n = width_and_height;

//	for(int x = 0; x < n; x++){
//		for(int y = 0; y < n; y++) {
//			new[x][y] = type_tetrimino_figure[x][y];
//		}
//	}
//}

Struct FunctionCreateSape(Struct shape){
	Struct new_shape = shape;
	//char **copyshape = shape.array;
	//new_shape.array = (char**)malloc(new_shape.width*sizeof(char*));
    int i, j;
    for(i = 0; i < new_shape.width; i++){
		//new_shape.array[i] = (char*)malloc(new_shape.width*sizeof(char));
		for(j=0; j < new_shape.width; j++) {
			new_shape.array[i][j] = shape.array[i][j];
			//new_shape.array[i][j] = copyshape[i][j];
		}
    }
    return new_shape;
}


int FunctionCPos(Struct shape){
	//char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
				if(shape.array[i][j])
				//if(array[i][j])
					return F;
				
			}
			else if(Table[shape.row+i][shape.col+j] && shape.array[i][j])
			//else if(Table[shape.row+i][shape.col+j] && array[i][j])
				return F;
		}
	}
	return T;
}

void FunctionRotateS(Struct shape){
	Struct temp = FunctionCreateSape(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
}

void FunctionPrintTscreen(){
	char Buffer[R][C] = {0};
	int i, j;
	for(i = 0; i < current.width ;i++){
		for(j = 0; j < current.width ; j++){
			if(current.array[i][j])
				Buffer[current.row+i][current.col+j] = current.array[i][j];
		}
	}
	clear();
	for(i=0; i<C-9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printw("%c ", (Table[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}

struct timeval before_now, now;
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

int main() {
    srand(time(0));
    final = 0;
    int c;
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	Struct new_shape = FunctionCreateSape(StructsArray[rand()%7]);
    new_shape.col = rand()%(C-new_shape.width+1);
    new_shape.row = 0;
	current = new_shape;
	if(!FunctionCPos(current)){
		GameOn = F;
	}
    FunctionPrintTscreen();
	while(GameOn){
		if ((c = getch()) != ERR) {
			Struct temp = FunctionCreateSape(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(FunctionCPos(temp))
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
						for(n=0;n<R;n++){
							sum = 0;
							for(m=0;m< C;m++) {
								sum+=Table[n][m];
							}
							if(sum==C){
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
						final += 100*count;
						Struct new_shape = FunctionCreateSape(StructsArray[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						current = new_shape;
						if(!FunctionCPos(current)){
							GameOn = F;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCPos(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCPos(temp))
						current.col--;
					break;
				case 'w':
					FunctionRotateS(temp);
					if(FunctionCPos(temp))
						FunctionRotateS(current);
					break;
			}
			FunctionPrintTscreen();
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			Struct temp = FunctionCreateSape(current);
			switch('s'){
				case 's':
					temp.row++;
					if(FunctionCPos(temp))
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
						for(n=0;n<R;n++){
							sum = 0;
							for(m=0;m< C;m++) {
								sum+=Table[n][m];
							}
							if(sum==C){
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
						Struct new_shape = FunctionCreateSape(StructsArray[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						current = new_shape;
						if(!FunctionCPos(current)){
							GameOn = F;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCPos(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCPos(temp))
						current.col--;
					break;
				case 'w':
					FunctionRotateS(temp);
					if(FunctionCPos(temp))
						FunctionRotateS(current);
					break;
			}
			FunctionPrintTscreen();
			gettimeofday(&before_now, NULL);
		}
	}
	endwin();
	int i, j;
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
    return 0;
}
