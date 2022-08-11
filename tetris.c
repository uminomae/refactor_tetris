#include "main.h"
#include "type.h"

int main() {

	t_tetris tetris;
	t_tetrimino current;
	t_tetrimino type[7];
	t_time timer;
	
	init_game(&tetris, &timer);
	memcpy(type, type_tetrimino, sizeof(type) * 1);
	begin_game(&tetris, &current, type);
	run_game(&tetris, &current, type, &timer);
	finish_game(&tetris, &current);
	return 0;
}


//	     42 Tetris (header)
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	.  t_tetrimino.current  . . .
//  . . . . . . . . . (type[7]) .
//	. . . . . . # # . . . . . . .
//	. . . . . . . # # . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	.  t_tetris.pleaying_field  .
//	. . . . . [20][15]. . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	. . . . . . . . . . . . . . .
//	# . # # # # . . . . . . . . .
//	# # # # # # # . # # # # . . .
//
//	Score: 0 (footer)