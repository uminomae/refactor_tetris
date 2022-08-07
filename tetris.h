#ifndef MAIN_TETRIS
# define MAIN_TETRIS

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
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
	t_tetrimino *tetrimino;
	//char **playing_field;
	char playing_field[FIELD_ROW][FIELD_COL];
} t_tetris;

void end_ncurses();
void set_timeout_millisecond(int time);
void print_string_to_window(char *str,...);


void copy_figure(t_tetrimino *new_tetrimino, char **type_tetrimino_figure);
t_tetrimino create_tetrimino(const t_tetrimino type_tetrimino);
void destroy_tetrimino(t_tetrimino *tetrimino);

//void refresh_game_screen(t_tetris *tetris);
void get_current_position(t_tetris *tetris, \
							char Buffer[FIELD_ROW][FIELD_COL]);
void print_game_screen(t_tetris *tetris, \
						char Buffer[FIELD_ROW][FIELD_COL]);
void print_footer(t_tetris *tetris);
void print_game_field(t_tetris *tetris, \
						char Buffer[FIELD_ROW][FIELD_COL]);
void print_header();

bool check_left(t_tetrimino *tetrimino, int i, int j);
bool check_right(t_tetrimino *tetrimino, int i, int j);
bool check_bottom(t_tetrimino *tetrimino, int i, int j);

#endif 