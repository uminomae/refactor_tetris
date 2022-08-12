#ifndef TETRIS
# define TETRIS

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
# define GAME_OVER 0
# define IN_GAME 1
# define INTERVAL_DECREASE	1000
# define NUM_OF_TYPE	7
# define FALL_VELOCITY_INTERVAL	400000

typedef struct s_tetrimino{
    char 	**array;
    int 	side_length;
	int 	row;
	int 	col;
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
} t_tetris;

void init_game(t_tetris *tetris, t_tetrimino *type, t_time *timer);
void begin_game(t_tetris *tetris, t_tetrimino *current, t_tetrimino *type);
void run_game(t_tetris *tetris, t_tetrimino *current, const t_tetrimino *type, t_time *timer);
void finish_game(t_tetris *tetris, t_tetrimino *current);
t_tetrimino copy_tetrimino(t_tetrimino shape);
void destroy_tetrimino_fiure(t_tetrimino shape);
t_tetrimino create_new_tetrimino();
t_tetrimino replace_next_tetrimino(t_tetrimino *current, const t_tetrimino *type);
int can_move_tetrimino(t_tetris *tetris, t_tetrimino shape);
void judge_the_end_of_game(t_tetris *tetris, t_tetrimino current);
void refresh_game_screen(t_tetris *tetris, t_tetrimino *current);
int count_completed_lines_and_erase(t_tetris *tetris, int *completed_lines);
void move_case_key_s(t_tetris *tetris, t_tetrimino *current, t_tetrimino *temp_for_judge, const t_tetrimino *type);
void move_case_key_w(t_tetris *tetris, t_tetrimino *current, t_tetrimino *temp_for_judge);
void move_case_key_a(t_tetris *tetris, t_tetrimino *current, t_tetrimino *temp_for_judge);
void move_case_key_d(t_tetris *tetris, t_tetrimino *current, t_tetrimino *temp_for_judge);
void print_resulting_to_standard_output(t_tetris *tetris);

#endif 