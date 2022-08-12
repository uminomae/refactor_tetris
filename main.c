#include "tetris.h"

int	main(void){
	t_tetris	tetris;
	t_tetrimino	current;
	t_tetrimino	type[7];
	t_time		timer;

	init_game(&tetris, type, &timer);
	begin_game(&tetris, &current, type);
	if (current.figure == NULL)
		return (0);
	run_game(&tetris, &current, type, &timer);
	if (current.figure == NULL)
		return (0);
	finish_game(&tetris, &current);
	return (0);
}

//       42 Tetris (header)
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . t_tetrimino . . . . . . . .
//  . . current.figure  . . . . . 
//  . . . . . . . (type[7]) . . . 
//  . . . . # # . . . . . . . . .
//  . . . . . # # . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . t_tetrimino . . . . . . . .
//  .  tetris.playing_field . . .
//  . . . . . [20][15]. . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  . . . . . . . . . . . . . . .
//  # . # # # # . . . . . . . . .
//  # # # # # # # . # # # # . . .
//  
//  Score: 0 (footer)
