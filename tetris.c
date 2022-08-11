
# include "main.h"
//# include "tetrimino.h"
# include "type.h"

#define R 20
#define C 15

void rotate_clodkwise(t_tetrimino shape);
void put_screen(t_tetris *tetris, t_tetrimino *current);
int hasToUpdate();
void set_timeout(int time);


suseconds_t timer = FALL_VELOCITY_INTERVAL;
int decrease = 1000;

int final = 0;

struct timeval before_now, now;


void begin_game(t_tetris *tetris, t_tetrimino *current, t_tetrimino *type){
	
	(void)tetris;
	*current = create_new_tetrimino(type);
	judge_the_end_of_game(tetris, *current);
    //refresh_game_screen(tetris, tetris->tetrimino);
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



    int c;
	//refresh_game_screen変える

    put_screen(&tetris, &current);
	while(tetris.game_status == IN_GAME){
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
						
						current = replace_next_tetrimino(&current, type);

						if(!can_move_tetrimino(&tetris, current)){
							tetris.game_status = GAME_OVER;
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

						current = replace_next_tetrimino(&current, type);

						if(!can_move_tetrimino(&tetris, current)){
							tetris.game_status = GAME_OVER;
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

	// finish_game()へ
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
	//
    
	return 0;
}



static void print_string_to_window(char *str,...){
	printw(str);
}

//--------------------------------------------------------
// refresh_game_screen
//--------------------------------------------------------
static void get_current_position(t_tetris *tetris, \
							t_tetrimino *current, \
							char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	const int n = current->width;

	for(int i = 0; i < n ;i++){
		for(int j = 0; j < n ; j++){
			if(current->array[i][j])
				next_playing_field[current->row+i][current->col+j] \
				 = current->array[i][j];
		}
	}
}

static void print_header(){
	for(int i = 0; i < FIELD_X_COL - 9; i++)
		print_string_to_window(" ");
	print_string_to_window("42 Tetris\n");
}

static void print_game_field(t_tetris *tetris, \
						char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	for(int i = 0; i < FIELD_Y_ROW ;i++){
		for(int j = 0; j < FIELD_X_COL ; j++){
			if (tetris->playing_field[i][j] + next_playing_field[i][j])
				print_string_to_window("%c ", '#');
			else
				print_string_to_window("%c ", '.');
		}
		print_string_to_window("\n");
	}
}

static void print_footer(t_tetris *tetris){
	printw("\nScore: %d\n", final);
	//print_string_to_window("\nScore: %d\n", tetris->score);
}

static void print_game_screen(t_tetris *tetris, \
						char next_playing_field[FIELD_Y_ROW][FIELD_X_COL]){
	print_header();
	print_game_field(tetris, next_playing_field);
	print_footer(tetris);
}

void put_screen(t_tetris *tetris, t_tetrimino *current){
//void refresh_game_screen(t_tetris *tetris, t_tetrimino *current){
	char next_playing_field[FIELD_Y_ROW][FIELD_X_COL] = {0};
	
	//tetris->tetrimino = current;
	get_current_position(tetris, current, next_playing_field);
	clear();
	print_game_screen(tetris, next_playing_field);
}
//--------------------------------------------------------
// refresh_game_screen
//--------------------------------------------------------


//void put_screen(t_tetris *tetris, t_tetrimino *current){
//	char Buffer[R][C] = {0};
//	int i, j;
//	for(i = 0; i < current->width ;i++){
//		for(j = 0; j < current->width ; j++){
//			if(current->array[i][j])
//				Buffer[current->row+i][current->col+j] = current->array[i][j];
//		}
//	}
//	clear();
//	for(i=0; i<C-9; i++)
//		printw(" ");
//	printw("42 Tetris\n");
//	for(i = 0; i < R ;i++){
//		for(j = 0; j < C ; j++){
//			printw("%c ", (tetris->playing_field[i][j] + Buffer[i][j])? '#': '.');
//		}
//		printw("\n");
//	}
//	printw("\nScore: %d\n", final);
//}


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

int hasToUpdate(){
	return ((suseconds_t)(now.tv_sec*1000000 + now.tv_usec) -((suseconds_t)before_now.tv_sec*1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	time = 1;
	timeout(1);
}