#ifndef MAIN_TETRIS
# define MAIN_TETRIS

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>

//x,yに
# define FIELD_ROW	20
# define FIELD_COL	15
# define TRUE		1
# define FALSE		0
# define MILLION	1000000
# define TOP_ROW	0
# define DROP_KEY 	's'
# define RIGHT_KEY 	'd'
# define LEFT_KEY 	'a'
# define ROTATE_KEY 'w'

//# define FALL_VELOCITY_INTERVAL	50000
# define FALL_VELOCITY_INTERVAL	400000
# define INTERVAL_DECREASE	1000

struct timeval before_now, now;

typedef enum s_game_status {
	GAME_OVER = 0,
	GAME_PLAY,
} t_game_status;

typedef struct {
    char 	**figure;
    int 	width_and_height;
	int 	row;
	int 	col;
} t_tetrimino;

typedef struct {
	int 		score;
	char 		game_status;
	t_tetrimino *tetrimino;
	suseconds_t time_to_update;
	int 		decrease;
	char		playing_field[FIELD_ROW][FIELD_COL];
	int 		input_from_keyboard;
} t_tetris;

//begin.c
void set_timeout_millisecond(int time);
void init_tetris(t_tetris *tetris);
void init_game(t_tetris *tetris);

//can_move.c
int can_move_field(t_tetris *tetris, t_tetrimino *tetrimino);

//finish.c
void finish_game(t_tetris *tetris,t_tetrimino current);
void finish_ncurses();

//key_command.c
void roteta_tetrimino(t_tetrimino *tetrimino);
//void move_tetrimino_with_key(t_tetris *tetris, bool update);
void move_tetrimino_with_key(t_tetris *tetris, t_tetrimino *tetrimino, bool update);
void move_case_key_d(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg);
//void move_case_d(t_tetris *tetris, t_tetrimino *temp);
void move_case_key_a(t_tetris *tetris, t_tetrimino *temp);
void move_case_key_w(t_tetris *tetris, t_tetrimino *temp,t_tetrimino current);
	//case s
void fix_tetrimino_on_the_field(t_tetris *tetris);
void make_the_next_tetrimino(t_tetris *tetris);
bool check_overlap_other_pieces(t_tetrimino *tetrimino, int i, int j);
int count_blocks_of_line(t_tetris *tetris, int y);
void lower_the_upper_block(t_tetris *tetris, int y);
void clear_line(t_tetris *tetris, int y);
void drop_placed_block_one_rank(t_tetris *tetris, int y);
int count_completed_lines_and_erase(t_tetris *tetris);
void move_case_key_s(t_tetris *tetris, t_tetrimino *temp, bool update);

//tmake_and_destroy_tetrimino.c
t_tetrimino *copy_tetrimino_type(t_tetrimino *type_tetrimino);
t_tetrimino create_new_tetrimino(t_tetrimino *type_tetrimino);
void destroy_tetrimino(t_tetrimino *tetrimino);

//refresh
void refresh_game_screen(t_tetris *tetris, t_tetrimino *current);
void get_current_position(t_tetris *tetris, \
							char next_playing_field[FIELD_ROW][FIELD_COL]);
void print_game_screen(t_tetris *tetris, \
						char next_playing_field[FIELD_ROW][FIELD_COL]);

//time.c
suseconds_t get_millisecond(struct timeval timevalue);
bool need_update(t_tetris *tetris);

#endif 