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
# define TOP_Y_ROW	0
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

# define FALL_VELOCITY_INTERVAL	400000
//# define FALL_VELOCITY_INTERVAL	400000

typedef struct {
    char **array;
	//char array[WIDTH_AND_HEIGHT_MAX][WIDTH_AND_HEIGHT_MAX];
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
	char 		game_status;
	suseconds_t time_to_update;
	int 		decrease;
	char		playing_field[FIELD_Y_ROW][FIELD_X_COL];
	int 		input_from_keyboard;
	struct s_time	*time;
} t_tetris;

void begin_game(t_tetris *tetris, t_tetrimino *current, t_tetrimino *type);

t_tetrimino copy_tetrimino(t_tetrimino shape);
void destroy_tetrimino(t_tetrimino shape);
void init_game(t_tetris *tetris);

t_tetrimino create_new_tetrimino();
t_tetrimino replace_next_tetrimino(t_tetrimino *current, const t_tetrimino *type);
int can_move_tetrimino(t_tetris *tetris, t_tetrimino shape);
void judge_the_end_of_game(t_tetris *tetris, t_tetrimino current);
void refresh_game_screen(t_tetris *tetris, t_tetrimino *current);
#endif 