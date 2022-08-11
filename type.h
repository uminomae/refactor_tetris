# include "main.h"

const t_tetrimino type_tetrimino[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};

//# define S_FIGURE \
//	.array = { \
//		{0,1,1}, \
//		{1,1,0}, \
//		{0,0,0} \
//	},\
//	.width = 3 
//# define Z_FIGURE \
//	.array = {\
//		{1,1,0},\
//		{0,1,1}, \
//		{0,0,0}\
//	},\
//	.width = 3
//# define T_FIGURE \
//	.array = {\
//		{0,1,0},\
//		{1,1,1},\
//		{0,0,0}\
//	},\
//	.width = 3
//# define L_FIGURE \
//	.array = {\
//		{0,0,1},\
//		{1,1,1}, \
//		{0,0,0}\
//	},\
//	.width = 3
//# define J_FIGURE \
//	.array = {\
//		{1,0,0},\
//		{1,1,1}, \
//		{0,0,0}\
//	},\
//	.width = 3
//# define O_FIGURE \
//	.array = {\
//		{1,1},\
//		{1,1}\
//	},\
//	.width = 2
//# define I_FIGURE \
//	.array = {\
//		{0,0,0,0}, \
//		{1,1,1,1}, \
//		{0,0,0,0}, \
//		{0,0,0,0}\
//	},\
//	.width = 4
	
////const t_tetrimino type_tetrimino[7]= {
////	{S_FIGURE},{Z_FIGURE},{T_FIGURE},{L_FIGURE},{J_FIGURE},{O_FIGURE},{I_FIGURE}
////};