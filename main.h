#ifndef MAIN_TETRIS
# define MAIN_TETRIS

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>
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
# define GAME_OVER 0
# define IN_GAME 1
# define TRUE 1
# define FALSE 0
# define INTERVAL_DECREASE	1000
# define NUM_OF_TYPE	7

typedef struct {
    char **array;
	//char array[WIDTH_AND_HEIGHT_MAX][WIDTH_AND_HEIGHT_MAX];
    int width;
	int row;
	int col;
} t_tetrimino;


#endif 