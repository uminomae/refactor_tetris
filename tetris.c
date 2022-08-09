#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>

# include <string.h>
# include <stdbool.h>
# include "main.h"
# include "figure.h"


# define FALL_VELOCITY_INTERVAL		50000
//# define FALL_VELOCITY_INTERVAL	400000
# define INTERVAL_DECREASE	1000
# define NUM_OF_TYPE	7



#define R 20
#define C 15
#define T 1
#define F 0

char Table[R][C] = {0};
int final = 0;
char GameOn = T;
suseconds_t timer = FALL_VELOCITY_INTERVAL;
//suseconds_t timer = 400000;
int decrease = 1000;

typedef struct {
    char figure[4][4];
    int width_and_height, row, col;
} t_tetrimino;

typedef struct s_tetris{
	int 		score;
	//char 		game_status;
	//struct s_tetrimino *tetrimino;
	//struct t_tetrimino type[NUM_OF_TYPE];
	//suseconds_t time_to_update;
	//int 		decrease;
	//char		playing_field[FIELD_ROW][FIELD_COL];
	//int 		input_from_keyboard;
	//struct s_time *timer;
} t_tetris;

const t_tetrimino type_tetrimino[] = {
	{S_FIGURE},{Z_FIGURE},{T_FIGURE},{L_FIGURE},{J_FIGURE},{O_FIGURE},{I_FIGURE}
};

t_tetrimino FunctionCreateSape(t_tetrimino shape){
	t_tetrimino new_shape = shape;
	int len = shape.width_and_height;

	memcpy(new_shape.figure, shape.figure, sizeof(char) * len * len);
    //int i, j;
    //for(i = 0; i < new_shape.width_and_height; i++){
	//	for(j=0; j < new_shape.width_and_height; j++) {
	//		new_shape.figure[i][j] = shape.figure[i][j];
	//	}
    //}
    return new_shape;
}


int FunctionCanmovePos(t_tetrimino shape){
	int i, j;
	for(i = 0; i < shape.width_and_height;i++) {
		for(j = 0; j < shape.width_and_height ;j++){
			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
				if(shape.figure[i][j])
					return F;
			}
			else if(Table[shape.row+i][shape.col+j] && shape.figure[i][j])
				return F;
		}
	}
	return T;
}

void FunctionRotateS(t_tetrimino shape){
	t_tetrimino temp1 = FunctionCreateSape(shape);
	int i, j, k, width_and_height;
	width_and_height = shape.width_and_height;
	for(i = 0; i < width_and_height ; i++){
		for(j = 0, k = width_and_height-1; j < width_and_height ; j++, k--){
				shape.figure[i][j] = temp1.figure[k][i];
		}
	}
}

void FunctionRotateCurrent(t_tetrimino *current){
	t_tetrimino temp1 = FunctionCreateSape(*current);
	int i, j, k, width_and_height;
	width_and_height = current->width_and_height;
	for(i = 0; i < width_and_height ; i++){
		for(j = 0, k = width_and_height-1; j < width_and_height ; j++, k--){
				current->figure[i][j] = temp1.figure[k][i];
		}
	}
}

void FunctionPrintTscreen(t_tetrimino *current){
	char Buffer[R][C] = {0};
	int i, j;
	for(i = 0; i < current->width_and_height ;i++){
		for(j = 0; j < current->width_and_height ; j++){
			if(current->figure[i][j])
				Buffer[current->row+i][current->col+j] = current->figure[i][j];
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
	t_tetrimino new_shape = FunctionCreateSape(type_tetrimino[rand()%7]);
    new_shape.col = rand()%(C-new_shape.width_and_height+1);
    new_shape.row = 0;
	t_tetrimino current = new_shape;
	if(!FunctionCanmovePos(current)){
		GameOn = F;
	}
    FunctionPrintTscreen(&current);
	while(GameOn){
		if ((c = getch()) != ERR) {
			t_tetrimino temp = FunctionCreateSape(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(FunctionCanmovePos(temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width_and_height ;i++){
							for(j = 0; j < current.width_and_height ; j++){
								if(current.figure[i][j])
									Table[current.row+i][current.col+j] = current.figure[i][j];
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
						t_tetrimino new_shape = FunctionCreateSape(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width_and_height+1);
						new_shape.row = 0;
						current = new_shape;
						if(!FunctionCanmovePos(current)){
							GameOn = F;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCanmovePos(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCanmovePos(temp))
						current.col--;
					break;
				case 'w':
					FunctionRotateS(temp);
					if(FunctionCanmovePos(temp))
						FunctionRotateCurrent(&current);
						//FunctionRotateS(current);
					break;
			}
			FunctionPrintTscreen(&current);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			t_tetrimino temp = FunctionCreateSape(current);
			switch('s'){
				case 's':
					temp.row++;
					if(FunctionCanmovePos(temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width_and_height ;i++){
							for(j = 0; j < current.width_and_height ; j++){
								if(current.figure[i][j])
									Table[current.row+i][current.col+j] = current.figure[i][j];
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
						t_tetrimino new_shape = FunctionCreateSape(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width_and_height+1);
						new_shape.row = 0;
						current = new_shape;
						if(!FunctionCanmovePos(current)){
							GameOn = F;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCanmovePos(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCanmovePos(temp))
						current.col--;
					break;
				case 'w':
					FunctionRotateS(temp);
					if(FunctionCanmovePos(temp))
						FunctionRotateS(current);
					break;
			}
			FunctionPrintTscreen(&current);
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
