#include "main.h"
#include "type.h"

//#define R 20
//#define C 15



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

suseconds_t get_millisecond(struct timeval timevalue){
	return (timevalue.tv_sec * MILLION + timevalue.tv_usec);
}

bool need_update(t_tetris *tetris, t_time *timer){
//bool need_update(t_tetris *tetris){
	const suseconds_t now_ms = get_millisecond(timer->now);
	const suseconds_t before_now_ms = get_millisecond(timer->before_now);
	return (now_ms - before_now_ms > tetris->time_to_update);
}

int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

static void set_timeout_millisecond(int time_ms) {
	timeout(time_ms);
}

//void set_timeout(int time) {
//	time = 1;
//	timeout(1);
//}


int main() {

	t_tetris tetris;
	t_tetrimino current;
	t_tetrimino type[7];
	t_time timer;
	
	init_game(&tetris);

	gettimeofday(&timer.before_now, NULL);
	set_timeout_millisecond(1);

	//gettimeofday(&before_now, NULL);
	//timeout(1);
	//set_timeout(1);
	
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

		gettimeofday(&timer.now, NULL);
		if (need_update(&tetris, &timer)) {
		
		//gettimeofday(&now, NULL);
		//if (hasToUpdate()) {
		
			t_tetrimino temp = copy_tetrimino(current);
			tetris.input_from_keyboard = 's';
			move_by_key_case(&tetris, &current, &temp, type);
			destroy_tetrimino(temp);
			refresh_game_screen(&tetris, &current);

			gettimeofday(&timer.before_now, NULL);
			//gettimeofday(&before_now, NULL);
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

void finish_game(t_tetris *tetris, t_tetrimino *current)
{
	destroy_tetrimino_dubble_pointer(&current);
	finish_ncurses();
	print_resulting_to_standard_output(tetris);
}