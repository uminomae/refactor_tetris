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
# define NUM_OF_TYPE	7

//struct timeval before_now, now;

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
	struct timeval before_now;
	struct timeval now;
} t_time;

typedef struct {
	int 		score;
	char 		game_status;
	t_tetrimino *tetrimino;
	t_tetrimino type[NUM_OF_TYPE];
	suseconds_t time_to_update;
	int 		decrease;
	char		playing_field[FIELD_ROW][FIELD_COL];
	int 		input_from_keyboard;
	t_time		*time;
} t_tetris;


void begin_game(t_tetris *tetris);
void run_game(t_tetris *tetris);

//begin.c
//void set_timeout_millisecond(int time);
//void init_tetris(t_tetris *tetris);
void init_game(t_tetris *tetris);

//can_move.c
int can_move_field(t_tetris *tetris, t_tetrimino *tetrimino);

//finish.c
void finish_game(t_tetris *tetris);
//void finish_game(t_tetris *tetris,t_tetrimino current);
void finish_ncurses();
void print_resulting_to_standard_output(t_tetris *tetris);

//key_command.c
t_tetrimino *select_type_tetrimino(t_tetrimino *src);
void move_by_key_case(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *for_judg_move, bool update, int key);
void move_tetrimino_with_key(t_tetris *tetris, t_tetrimino *tetrimino, bool update);
void roteta_tetrimino(t_tetrimino *tetrimino);
void move_tetrimino_with_key(t_tetris *tetris, t_tetrimino *tetrimino, bool update);
void move_case_key_d(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg);
void move_case_key_a(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg);
void move_case_key_w(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg);
	//case s
void fix_tetrimino_on_the_field(t_tetris *tetris);
void make_next_tetrimino(t_tetris *tetris, t_tetrimino *tetlimino);
bool check_overlap_other_pieces(t_tetrimino *tetrimino, int i, int j);
int count_blocks_of_line(t_tetris *tetris, int y);
void lower_the_upper_block(t_tetris *tetris, int y);
void clear_line(t_tetris *tetris, int y);
void drop_placed_block_one_rank(t_tetris *tetris, int y);
int count_completed_lines_and_erase(t_tetris *tetris);
void move_case_key_s(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judg, bool update);

//make and destroy
t_tetrimino *copy_tetrimino_type(t_tetrimino *type_tetrimino);
t_tetrimino *create_new_tetrimino(t_tetrimino *type_tetrimino);
void destroy_tetrimino(t_tetrimino *tetrimino);

//refresh
void refresh_game_screen(t_tetris *tetris, t_tetrimino *current);
void get_current_position(t_tetris *tetris, char next_playing_field[FIELD_ROW][FIELD_COL]);
void print_game_screen(t_tetris *tetris, char next_playing_field[FIELD_ROW][FIELD_COL]);

//time.c
suseconds_t get_millisecond(struct timeval timevalue);
bool need_update(t_tetris *tetris);




#endif 