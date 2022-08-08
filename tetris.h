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
//# define FALL_VELOCITY_INTERVAL	50000
# define FALL_VELOCITY_INTERVAL	400000
# define INTERVAL_DECREASE	1000
# define TOP_ROW	0
# define DROP_KEY 's'
# define RIGHT_KEY 'd'
# define LEFT_KEY 'a'
# define ROTATE_KEY 'w'

struct timeval before_now, now;

typedef enum s_game_status {
	GAME_OVER = 0,
	GAME_PLAY,
	//LOCK_DOWN,
} t_game_status;

typedef struct {
    char **figure;
    int width_and_height;
	int row;
	int col;
} t_tetrimino;

typedef struct {
	int score;
	char game_status;
	t_tetrimino *tetrimino;
	suseconds_t time_to_update;
	int decrease;
	char playing_field[FIELD_ROW][FIELD_COL];
	int input_from_keyboard;
} t_tetris;


t_tetrimino *copy_tetrimino_type(t_tetrimino *type_tetrimino);
t_tetrimino create_new_tetrimino(t_tetrimino *type_tetrimino);

//can_move
int can_move_field(t_tetris *tetris, t_tetrimino *tetrimino);
void move_case_d(t_tetris *tetris, t_tetrimino *temp);
void move_case_a(t_tetris *tetris, t_tetrimino *temp);
void move_case_w(t_tetris *tetris, t_tetrimino *temp,t_tetrimino current);
void fix_tetrimino_on_the_field(t_tetris *tetris);
void make_the_next_tetrimino(t_tetris *tetris);
void move_case_s(t_tetris *tetris, t_tetrimino *temp, bool update);
void move_tetrimino_with_key(t_tetris *tetris, bool update);

//move.c
void roteta_tetrimino(t_tetrimino *tetrimino);

//init.c
void init_tetris(t_tetris *tetris);
void init_game(t_tetris *tetris);

//end.c
void finish_game(t_tetris *tetris,t_tetrimino current);
void finish_ncurses();

//time.c
suseconds_t get_millisecond(struct timeval timevalue);
bool need_update(t_tetris *tetris);

//refresh
void refresh_game_screen(t_tetris *tetris, t_tetrimino *current);

//tetrimino
void destroy_tetrimino(t_tetrimino *tetrimino);







bool check_overlap_other_pieces(t_tetrimino *tetrimino, int i, int j);
int count_blocks_of_line(t_tetris *tetris, int y);
void lower_the_upper_block(t_tetris *tetris, int y);
void clear_line(t_tetris *tetris, int y);
void drop_placed_block_one_rank(t_tetris *tetris, int y);
int count_completed_lines_and_erase(t_tetris *tetris);


void get_current_position(t_tetris *tetris, \
							char next_playing_field[FIELD_ROW][FIELD_COL]);
void print_game_screen(t_tetris *tetris, \
						char next_playing_field[FIELD_ROW][FIELD_COL]);

void set_timeout_millisecond(int time);
//void print_resulting_to_standard_output(t_tetris *tetris);

#endif 