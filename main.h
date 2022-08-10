#ifndef MAIN_TETRIS
# define MAIN_TETRIS

typedef struct {
    char **array;
	//char array[WIDTH_AND_HEIGHT_MAX][WIDTH_AND_HEIGHT_MAX];
    int width;
	int row;
	int col;
} t_tetrimino;

const t_tetrimino type_tetrimino[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};


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