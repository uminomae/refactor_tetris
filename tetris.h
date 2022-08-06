#ifndef MAIN_TETRIS
# define MAIN_TETRIS

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>

# define FIELD_ROW	20
# define FIELD_COL	15
# define TRUE		1
# define FALSE		0

//char playing_field[FIELD_ROW][FIELD_COL] = {0};

typedef enum s_game_status {
	GAME_OVER = 0,
	GAME_PLAY,
	LOCK_DOWN,
} t_game_status;

typedef struct {
    char **array;
    int width, row, col;
} t_tetrimino;

typedef struct {
	int score;
	char game_status;
	//char playing_field[FIELD_ROW][FIELD_COL] = {0};
} t_tetris;


#endif 