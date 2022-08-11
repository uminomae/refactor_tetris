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


////main.c
//void init_ncurses_window();
//void begin_game(t_tetris *tetris);
//void run_game(t_tetris *tetris);
//void finish_game(t_tetris *tetris);

////begin.c
//void init_game(t_tetris *tetris);

////field.c
//int count_completed_lines_and_erase(t_tetris *tetris);

////finish.c
//void finish_ncurses();
//void print_resulting_to_standard_output(t_tetris *tetris);

////judge.c
//void judge_the_end_of_game(t_tetris *tetris);
//int can_move_field(t_tetris *tetris, t_tetrimino *tetrimino);


////key.c
//void get_char_input_from_keyboad(t_tetris *tetris);
//void move_tetrimino_with_key(t_tetris *tetris, t_tetrimino *tetrimino, bool update);
//void move_by_key_case(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *for_judge_move, bool update, int key);
//void move_case_key_d(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge);
//void move_case_key_a(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge);
//void move_case_key_w(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge);
//void move_case_key_s(t_tetris *tetris, t_tetrimino *tetrimino, t_tetrimino *temp_for_judge, bool update);

////tetrimino.c
//void switch_to_next_tetrimino(t_tetris *tetris, t_tetrimino *tetlimino);
//void rotate_tetrimino(t_tetrimino *tetrimino);
//void fix_tetrimino_on_the_field(t_tetris *tetris);
//void destroy_tetrimino(t_tetrimino *tetrimino);
//t_tetrimino *copy_tetrimino_type(t_tetrimino *type_tetrimino);
//t_tetrimino *create_new_tetrimino(t_tetrimino *type_tetrimino);

////screen.c
//void refresh_game_screen(t_tetris *tetris, t_tetrimino *current);

////time.c
//suseconds_t get_millisecond(struct timeval timevalue);
//bool need_update(t_tetris *tetris);




#endif 