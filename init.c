#include "tetris.h"
#include "tetrimino.h"

//void init_type_tetrimino(){
void init_type_tetrimino(t_tetrimino *type){

	//type[] = {
	t_tetrimino type_tetlimino[] = {
		{
			S_FIGURE
		},
		{
			Z_FIGURE
		},
		{
			T_FIGURE
		},
		{
			L_FIGURE
		},
		{
			J_FIGURE
		},
		{
			O_FIGURE
		},
		{
			I_FIGURE
		}
	};
	type = type_tetlimino;
}


//--------------------------------------------------------
//init_game
//--------------------------------------------------------

static void init_struct_tetris(t_tetris **tetris){
	const size_t type_size = sizeof(char) * ONE_SIDE_SQUARE_MAX * ONE_SIDE_SQUARE_MAX + sizeof(int) * 3;
	const size_t field_size = sizeof(char) * FIELD_ROW * FIELD_COL;
	
	//*tetris = (t_tetris *)malloc(sizeof(t_tetris) * 1);
	//if (tetris == NULL)
	//	return ;
	(*tetris)->score = 0;
	(*tetris)->game_status = GAME_PLAY;
	(*tetris)->time_to_update = FALL_VELOCITY_INTERVAL;
	(*tetris)->decrease = INTERVAL_DECREASE;
	init_type_tetrimino((*tetris)->type);
	memset(&(*tetris)->type, 0, type_size);
	//memset(&(*tetris)->type, 0, type_size);
	memset((*tetris)->playing_field, 0, field_size);
	(*tetris)->input_from_keyboard = 0;
}

static void set_timeout_millisecond(int time) {
	timeout(time);
}

void init_game(t_tetris *tetris)
{
	t_time timer;
	
	srand(time(NULL));
	init_struct_tetris(&tetris);
	//gettimeofday(&tetris->time->before_now, NULL);
	gettimeofday(&timer.before_now, NULL);
	tetris->timer = &timer;
	//printf("debug-5---");
	set_timeout_millisecond(1);
}

//--------------------------------------------------------
//end of init_game
//--------------------------------------------------------

void init_ncurses_window(){
	initscr();
}

//ssize_t	init_param(t_param **prm)
//{
//	*prm = (t_param *)malloc(sizeof(t_param) * 1);
//	if (*prm == NULL)
//		return (ERR_ALC);
//	init_stack(&(*prm)->st_a);
//	init_stack(&(*prm)->st_b);
//	init_ope_lst(&(*prm)->opr, NULL, NULL);
//	init_distance(&(*prm)->distance, 0, 0);
//	if ((*prm)->st_a == NULL || (*prm)->st_a == NULL || \
//	    (*prm)->opr == NULL || (*prm)->distance == NULL)
//		return (ERR_ALC);
//	(*prm)->len_arg = 0;
//	(*prm)->divide_size = 0;
//	(*prm)->largest_partition = 0;
//	(*prm)->central_partition = 0;
//	(*prm)->partitioning_loop = 0;
//	(*prm)->jewel = 0;
//	(*prm)->st_a->now = NULL;
//	(*prm)->st_b->now = NULL;
//	(*prm)->is_error = false;
//	(*prm)->is_alc_error = false;
//	return (1);
//}
