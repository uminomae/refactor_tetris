#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include "main.h"
#include "tetrimino.h"


# include <string.h>
# include <stdbool.h>

# define FIELD_Y_ROW	20
# define FIELD_X_COL	15
# define TRUE		1
# define FALSE		0
# define MILLION	1000000
# define TOP_ROW	0
# define DROP_KEY 	's'
# define RIGHT_KEY 	'd'
# define LEFT_KEY 	'a'
# define ROTATE_KEY 'w'
# define WIDTH_AND_HEIGHT_MAX 4

//# define FALL_VELOCITY_INTERVAL	50000
# define FALL_VELOCITY_INTERVAL	400000
# define INTERVAL_DECREASE	1000
# define NUM_OF_TYPE	7

#define R 20
#define C 15
#define T 1
#define F 0

char GameOn = T;
suseconds_t timer = FALL_VELOCITY_INTERVAL;
int decrease = 1000;

typedef char t_figure[WIDTH_AND_HEIGHT_MAX][WIDTH_AND_HEIGHT_MAX];

typedef struct {
    char **array;
    int width;
	int row;
	int col;
} t_tetrimino;

typedef struct s_time{
	struct timeval before_now;
	struct timeval now;
} t_time;

typedef struct {
	int 		score;
	//char 		game_status;
	//suseconds_t time_to_update;
	//int 		decrease;
	char		playing_field[FIELD_Y_ROW][FIELD_X_COL];
	//int 		input_from_keyboard;
	//struct s_time	*time;
} t_tetris;

int final = 0;

const t_tetrimino type_tetrimino[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

t_tetrimino copy_tetrimino(t_tetrimino shape){
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

void destroy_tetrimino(t_tetrimino shape){
    int i;
    for(i = 0; i < shape.width; i++){
		free(shape.array[i]);
    }
    free(shape.array);
}

int can_move_tetrimino(t_tetris *tetris,t_tetrimino shape){
//int can_move_tetrimino t_tetrimino shape){
	char **array = shape.array;
	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
				if(array[i][j])
					return F;
				
			}
			else if(tetris->playing_field[shape.row+i][shape.col+j] && array[i][j])
				return F;
		}
	}
	return T;
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

void put_screen(t_tetris *tetris, t_tetrimino *current){
	char Buffer[R][C] = {0};
	int i, j;
	for(i = 0; i < current->width ;i++){
		for(j = 0; j < current->width ; j++){
			if(current->array[i][j])
				Buffer[current->row+i][current->col+j] = current->array[i][j];
		}
	}
	clear();
	for(i=0; i<C-9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printw("%c ", (tetris->playing_field[i][j] + Buffer[i][j])? '#': '.');
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

	t_tetris tetris;
	t_tetrimino current;

	char playing_field[R][C] = {0};
	memcpy(tetris.playing_field, playing_field, sizeof(char) * 20*15);

    srand(time(0));
    final = 0;
    int c;
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	t_tetrimino new_shape = copy_tetrimino(type_tetrimino[rand()%7]);
    new_shape.col = rand()%(C-new_shape.width+1);
    new_shape.row = 0;
    //destroy_tetrimino(current);
	current = new_shape;
	if(!can_move_tetrimino(&tetris, current)){
		GameOn = F;
	}
    put_screen(&tetris, &current);
	while(GameOn){
		if ((c = getch()) != ERR) {
			t_tetrimino temp = copy_tetrimino(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(can_move_tetrimino(&tetris, temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									tetris.playing_field[current.row+i][current.col+j] = current.array[i][j];
							}
						}
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
						final += 100*count;
						t_tetrimino new_shape = copy_tetrimino(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						destroy_tetrimino(current);
						current = new_shape;
						if(!can_move_tetrimino(&tetris, current)){
							GameOn = F;
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
			put_screen(&tetris, &current);
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
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									tetris.playing_field[current.row+i][current.col+j] = current.array[i][j];
							}
						}
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
						t_tetrimino new_shape = copy_tetrimino(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						destroy_tetrimino(current);
						current = new_shape;
						if(!can_move_tetrimino(&tetris, current)){
							GameOn = F;
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
			put_screen(&tetris, &current);
			gettimeofday(&before_now, NULL);
		}
	}
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
	printf("\nScore: %d\n", final);
    return 0;
}
