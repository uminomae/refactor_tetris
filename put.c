#include "tetris.h"
//#include <ncurses.h>

void print_string_to_screen(char *str,...){
	printw(str);
}

void print_game_title(){
	for(int i = 0; i < FIELD_COL - 9; i++)
		print_string_to_screen(" ");
	print_string_to_screen("42 Tetris\n");
}