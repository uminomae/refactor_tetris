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

struct timeval before_now, now;

typedef enum s_game_status {
	GAME_OVER = 0,
	GAME_PLAY,
	LOCK_DOWN,
} t_game_status;

typedef struct {
    char **figure;
    int width_and_height, row, col;
} t_tetrimino;

typedef struct {
	int score;
	char game_status;
	//char **playing_field;
} t_tetris;

void end_ncurses();
void set_timeout_millisecond(int time);
void print_string_to_window(char *str,...);
void print_game_title();

void copy_figure(t_tetrimino *new_tetrimino, char **type_tetrimino_figure);
t_tetrimino create_figure(const t_tetrimino type_tetrimino);

#endif 