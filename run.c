#include "tetris.h"

static suseconds_t	get_millisecond(struct timeval timevalue){
	return (timevalue.tv_sec * MILLION + timevalue.tv_usec);
}

static bool	need_update(t_tetris *tetris, t_time *timer){
	const suseconds_t	now_ms = get_millisecond(timer->now);
	const suseconds_t	before_now_ms = get_millisecond(timer->before_now);
	return (now_ms - before_now_ms > tetris->time_to_update);
}

static void	get_char_input_from_keyboad(t_tetris *tetris){
	tetris->input_from_keyboard = getch();
}

static void	move_each_key_command(t_tetris *tetris, \
						t_tetrimino *current, \
						t_tetrimino *temp_for_judge, \
						const t_tetrimino *type){
	int	key = tetris->input_from_keyboard;
	if (key == DROP_KEY){
		move_drop(tetris, current, temp_for_judge, type);
	}else if (key == RIGHT_KEY){
		move_right(tetris, current, temp_for_judge);
	}else if (key == LEFT_KEY){
		move_left(tetris, current, temp_for_judge);
	}else if (key == ROTATE_KEY){
		move_rotate(tetris, current, temp_for_judge);
	}
}

static void	move_tetrimino_with_key(t_tetris *tetris, \
								t_tetrimino *current, \
								const t_tetrimino *type, \
								bool update){
	t_tetrimino	temp = copy_tetrimino(*current);

	if (temp.figure == NULL)
		return ;
	if (update == true)
		tetris->input_from_keyboard = DROP_KEY;
	move_each_key_command(tetris, current, &temp, type);
	if (current->figure == NULL)
		return ;
	destroy_tetrimino_fiure(temp);
	refresh_game_screen(tetris, current);
}

void	run_game(t_tetris *tetris, \
				t_tetrimino *current, \
				const t_tetrimino *type, \
				t_time *timer){
	while (tetris->game_status == IN_GAME){
		get_char_input_from_keyboad(tetris);
		if (tetris->input_from_keyboard != ERR) 
			move_tetrimino_with_key(tetris, current, type,false);
		if (current->figure == NULL)
			return ;
		gettimeofday(&timer->now, NULL);
		if (need_update(tetris, timer)){
			move_tetrimino_with_key(tetris, current, type, true);
			if (current->figure == NULL)
				return ;
			gettimeofday(&timer->before_now, NULL);
		}
	}
}
