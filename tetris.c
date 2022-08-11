#include "main.h"
#include "type.h"

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
	const suseconds_t now_ms = get_millisecond(timer->now);
	const suseconds_t before_now_ms = get_millisecond(timer->before_now);
	return (now_ms - before_now_ms > tetris->time_to_update);
}


//void move_tetrimino_with_key(t_tetris *tetris, \
//								t_tetrimino *tetrimino, \
//								bool update){
//	int key = tetris->input_from_keyboard;
//	t_tetrimino temp_for_judge = *copy_tetrimino_type(tetrimino);
	
//	move_by_key_case(tetris, tetrimino, &temp_for_judge, update, key);
//	destroy_tetrimino(&temp_for_judge);
//	refresh_game_screen(tetris, tetrimino);
//}

void run_game(t_tetris *tetris, t_tetrimino *current, t_time *timer, const t_tetrimino *type){
	while(tetris->game_status == IN_GAME){
		get_char_input_from_keyboad(tetris);
		if (tetris->input_from_keyboard != ERR) {
			t_tetrimino temp = copy_tetrimino(*current);
			move_by_key_case(tetris, current, &temp, type);
			destroy_tetrimino(temp);
			refresh_game_screen(tetris, current);
		}
		gettimeofday(&timer->now, NULL);
		if (need_update(tetris, timer)) {
			tetris->input_from_keyboard = 's';
			t_tetrimino temp = copy_tetrimino(*current);
			move_by_key_case(tetris, current, &temp, type);
			destroy_tetrimino(temp);
			refresh_game_screen(tetris, current);
			gettimeofday(&timer->before_now, NULL);
		}
	}
}

int main() {

	t_tetris tetris;
	t_tetrimino current;
	t_tetrimino type[7];
	t_time timer;
	
	init_game(&tetris, &timer);
	memcpy(type, type_tetrimino, sizeof(type) * 1);
	begin_game(&tetris, &current, type);
	run_game(&tetris, &current, &timer, type);
	//while(tetris.game_status == IN_GAME){
	//	get_char_input_from_keyboad(&tetris);
	//	if (tetris.input_from_keyboard != ERR) {
	//		t_tetrimino temp = copy_tetrimino(current);
	//		move_by_key_case(&tetris, &current, &temp, type);
	//		destroy_tetrimino(temp);
	//		refresh_game_screen(&tetris, &current);
	//	}
	//	gettimeofday(&timer.now, NULL);
	//	if (need_update(&tetris, &timer)) {
	//		tetris.input_from_keyboard = 's';
	//		t_tetrimino temp = copy_tetrimino(current);
	//		move_by_key_case(&tetris, &current, &temp, type);
	//		destroy_tetrimino(temp);
	//		refresh_game_screen(&tetris, &current);
	//		gettimeofday(&timer.before_now, NULL);
	//	}
	//}
	finish_game(&tetris, &current);
	return 0;
}

//--------------------------------------------------------
// sub
//--------------------------------------------------------

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