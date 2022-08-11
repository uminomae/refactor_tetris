
# include "main.h"
# include "tetrimino.h"

#define R 20
#define C 15

# define FALL_VELOCITY_INTERVAL	100000
//# define FALL_VELOCITY_INTERVAL	400000

char GameOn = TRUE;
suseconds_t timer = FALL_VELOCITY_INTERVAL;
int decrease = 1000;

typedef struct s_time{
	struct timeval before_now;
	struct timeval now;
} t_time;

typedef struct {
	int 		score;
	char 		game_status;
	suseconds_t time_to_update;
	int 		decrease;
	char		playing_field[FIELD_Y_ROW][FIELD_X_COL];
	int 		input_from_keyboard;
	struct s_time	*time;
} t_tetris;

int final = 0;


t_tetrimino copy_tetrimino(t_tetrimino shape);
void destroy_tetrimino(t_tetrimino shape);

const t_tetrimino type_tetrimino[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};


int can_move_tetrimino(t_tetris *tetris, t_tetrimino shape){
//int can_move_tetrimino t_tetrimino shape){
	char **array = shape.array;

	int i, j;
	for(i = 0; i < shape.width;i++) {
		for(j = 0; j < shape.width ;j++){
			if((shape.col+j < 0 || shape.col+j >= C || shape.row+i >= R)){
				if(shape.array[i][j])
				if(array[i][j])
					return FALSE;
				
			}
			//else if(tetris->playing_field[shape.row+i][shape.col+j] && shape.array[i][j])
			else if(tetris->playing_field[shape.row+i][shape.col+j] && array[i][j])
				return FALSE;
		}
	}
	return TRUE;
}

void rotate_clodkwise(t_tetrimino shape){
	t_tetrimino temp = copy_tetrimino(shape);
	int i, j, k, width;
	width = shape.width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape.array[i][j] = temp.array[k][i];
		}
	}
	destroy_tetrimino(temp);
}

void rotate_clodkwise2(t_tetrimino *shape){
	t_tetrimino temp = copy_tetrimino(*shape);
	int i, j, k, width;
	width = shape->width;
	for(i = 0; i < width ; i++){
		for(j = 0, k = width-1; j < width ; j++, k--){
				shape->array[i][j] = temp.array[k][i];
		}
	}
	destroy_tetrimino(temp);
}

void put_screen(t_tetris *tetris, t_tetrimino *current){
	char Buffer[R][C] = {0};
	int i, j;
	for(i = 0; i < current->width ;i++){
		for(j = 0; j < current->width ; j++){
			if(current->array[i][j])
				Buffer[current->row+i][current->col+j] = current->array[i][j];
		}
	}
	clear();
	for(i=0; i<C-9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printw("%c ", (tetris->playing_field[i][j] + Buffer[i][j])? '#': '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}

struct timeval before_now, now;
//struct timeval now;
int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}

//suseconds_t get_millisecond(struct timeval timevalue){
//	return (timevalue.tv_sec * MILLION + timevalue.tv_usec);
//}

//bool need_update(t_tetris *tetris){
//	const suseconds_t now_ms = get_millisecond(tetris->time->now);
//	const suseconds_t before_now_ms = get_millisecond(tetris->time->before_now);
//	return (now_ms - before_now_ms > tetris->time_to_update);
//}

//--------------------------------------------------------
//init_game
//--------------------------------------------------------

static void init_ncurses_window(){
	initscr();
}

static void init_struct_tetris(t_tetris *tetris){
	tetris->score = 0;
	tetris->game_status = IN_GAME;
	tetris->time_to_update = FALL_VELOCITY_INTERVAL;
	tetris->decrease = INTERVAL_DECREASE;
	//tetris->type = type_tetrimino;
	memset(tetris->playing_field, 0, sizeof(char) * FIELD_Y_ROW * FIELD_X_COL);
	tetris->input_from_keyboard = 0;
}

static void set_timeout_millisecond(int time) {
	timeout(time);
}

void init_game(t_tetris *tetris)
{
	
	srand(time(0));
	init_struct_tetris(tetris);
	//gettimeofday(&tetris->time->before_now, NULL);
	//set_timeout_millisecond(1);
	init_ncurses_window();
}

//--------------------------------------------------------
//end of init_game
//--------------------------------------------------------



//void begin_game(t_tetris *tetris, t_tetrimino *tetrimino){
//	tetrimino = create_new_tetrimino(tetris->type);
//	judge_the_end_of_game(tetris);
//	printf("b2--begin----\n");
//    refresh_game_screen(tetris, tetris->tetrimino);
//}

int main() {

	t_tetris tetris;
	t_tetrimino current;

	init_game(&tetris);
	//char playing_field[R][C] = {0};
	//memcpy(tetris.playing_field, playing_field, sizeof(char) * 20*15);

    //srand(time(0));
    //final = 0;
    int c;
    //initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	t_tetrimino new_shape = copy_tetrimino(type_tetrimino[rand()%7]);
    new_shape.col = rand()%(C-new_shape.width+1);
    new_shape.row = 0;
    //destroy_tetrimino(current);
	current = new_shape;
	if(!can_move_tetrimino(&tetris, current)){
		GameOn = FALSE;
	}
    put_screen(&tetris, &current);
	while(GameOn){
		if ((c = getch()) != ERR) {
			t_tetrimino temp = copy_tetrimino(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(can_move_tetrimino(&tetris, temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									tetris.playing_field[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<R;n++){
							sum = 0;
							for(m=0;m< C;m++) {
								sum+=tetris.playing_field[n][m];
							}
							if(sum==C){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<C;l++)
										tetris.playing_field[k][l]=tetris.playing_field[k-1][l];
								for(l=0;l<C;l++)
									tetris.playing_field[k][l]=0;
								timer-=decrease--;
							}
						}
						final += 100*count;
						t_tetrimino new_shape = copy_tetrimino(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						destroy_tetrimino(current);
						current = new_shape;
						if(!can_move_tetrimino(&tetris, current)){
							GameOn = FALSE;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(can_move_tetrimino(&tetris, temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(can_move_tetrimino(&tetris, temp))
						current.col--;
					break;
				case 'w':
					rotate_clodkwise(temp);
					if(can_move_tetrimino(&tetris, temp))
						rotate_clodkwise(current);
					break;
			}
			destroy_tetrimino(temp);
			put_screen(&tetris, &current);
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			t_tetrimino temp = copy_tetrimino(current);
			switch('s'){
				case 's':
					temp.row++;
					if(can_move_tetrimino(&tetris, temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									tetris.playing_field[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<R;n++){
							sum = 0;
							for(m=0;m< C;m++) {
								sum+=tetris.playing_field[n][m];
							}
							if(sum==C){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<C;l++)
										tetris.playing_field[k][l]=tetris.playing_field[k-1][l];
								for(l=0;l<C;l++)
									tetris.playing_field[k][l]=0;
								timer-=decrease--;
							}
						}
						t_tetrimino new_shape = copy_tetrimino(type_tetrimino[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						destroy_tetrimino(current);
						current = new_shape;
						if(!can_move_tetrimino(&tetris, current)){
							GameOn = FALSE;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(can_move_tetrimino(&tetris, temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(can_move_tetrimino(&tetris, temp))
						current.col--;
					break;
				case 'w':
					rotate_clodkwise(temp);
					if(can_move_tetrimino(&tetris, temp))
						rotate_clodkwise(current);
					break;
			}
			destroy_tetrimino(temp);
			put_screen(&tetris, &current);
			gettimeofday(&before_now, NULL);
		}
	}
	destroy_tetrimino(current);
	endwin();
	int i, j;
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printf("%c ", tetris.playing_field[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
    return 0;
}
