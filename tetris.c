
# include "main.h"
//# include "tetrimino.h"
# include "type.h"

#define R 20
#define C 15



int hasToUpdate();
void set_timeout(int time);

suseconds_t timer = FALL_VELOCITY_INTERVAL;
int decrease = 1000;

struct timeval before_now, now;


//void move_tetrimino_with_key(t_tetris *tetris, \
//								t_tetrimino *tetrimino, \
//								bool update){
//	int key = tetris->input_from_keyboard;
//	t_tetrimino temp_for_judge = *copy_tetrimino_type(tetrimino);
	
//	move_by_key_case(tetris, tetrimino, &temp_for_judge, update, key);
//	destroy_tetrimino(&temp_for_judge);
//	refresh_game_screen(tetris, tetrimino);
//}


static void finish_ncurses(){
	endwin();
}

//--------------------------------------------------------
//print_resulting_to_standard_output
//--------------------------------------------------------

static void print_field_result(t_tetris *tetris){
	for(int y = 0; y < FIELD_Y_ROW ;y++){
		for(int x = 0; x < FIELD_X_COL ; x++){
			if (tetris->playing_field[y][x])
				printf("%c ", '#');
			else
				printf("%c ", '.');
		}
		printf("\n");
	}
}

static void print_result_footer(t_tetris *tetris){
	printf("\nGame over!\n");
	printf("\nScore: %d\n", tetris->score);
}

void print_resulting_to_standard_output(t_tetris *tetris){
	print_field_result(tetris);
	print_result_footer(tetris);
}

//--------------------------------------------------------
//end of print_resulting_to_standard_output
//--------------------------------------------------------



void finish_game(t_tetris *tetris, t_tetrimino *current)
{
	destroy_tetrimino_dubble_pointer(&current);
	finish_ncurses();
	print_resulting_to_standard_output(tetris);
}

int main() {

	t_tetris tetris;
	t_tetrimino current;
	t_tetrimino type[7];
	
	init_game(&tetris);
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	memcpy(type, type_tetrimino, sizeof(type) * 1);
	begin_game(&tetris, &current, type);

//temp++を定数とか引数で設定する
	while(tetris.game_status == IN_GAME){
		get_char_input_from_keyboad(&tetris);
		if (tetris.input_from_keyboard != ERR) {
			t_tetrimino temp = copy_tetrimino(current);
			move_by_key_case(&tetris, &current, &temp, type);
			destroy_tetrimino(temp);
			refresh_game_screen(&tetris, &current);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			t_tetrimino temp = copy_tetrimino(current);
			tetris.input_from_keyboard = 's';
			move_by_key_case(&tetris, &current, &temp, type);
			destroy_tetrimino(temp);
			refresh_game_screen(&tetris, &current);
			gettimeofday(&before_now, NULL);
		}
	}
	finish_game(&tetris, &current);
	return 0;
}

void begin_game(t_tetris *tetris, t_tetrimino *current, t_tetrimino *type){
	
	(void)tetris;
	*current = create_new_tetrimino(type);
	judge_the_end_of_game(tetris, *current);
	refresh_game_screen(tetris, current);
}

int hasToUpdate(){
	//tetris.c:260:90: runtime error: signed integer overflow: 1660208859 * 1000000 cannot be represented in type 'int'
	//SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior tetris.c:260:90 in 

	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}