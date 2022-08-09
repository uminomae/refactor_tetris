# define S_FIGURE \
	.figure = { \
		{0,1,1}, \
		{1,1,0}, \
		{0,0,0} \
	},\
	.width_and_height = 3,
# define Z_FIGURE \
	.figure = {\
		{1,1,0},\
		{0,1,1},\
		{0,0,0}\
	}, \
	.width_and_height = 3,
# define T_FIGURE \
	.figure = {\
		{0,1,0},\
		{1,1,1},\
		{0,0,0}\
	}, \
	.width_and_height = 3,
# define L_FIGURE \
	.figure = {\
		{0,0,1},\
		{1,1,1},\
		{0,0,0}\
	}, \
	.width_and_height = 3,
# define J_FIGURE \
	.figure = {\
		{1,0,0},\
		{1,1,1},\
		{0,0,0}\
	}, \
	.width_and_height = 3,
# define O_FIGURE \
	.figure = {\
		{1,1},\
		{1,1}\
	}, \
	.width_and_height = 2,
# define I_FIGURE \
	.figure = {\
		{0,0,0,0},\
		{1,1,1,1},\
		{0,0,0,0},\
		{0,0,0,0}\
	}, \
	.width_and_height = 4,

//# define S_FIGURE \
//	(char *[3]){ \
//	(char []){0,1,1}, \
//	(char []){1,1,0}, \
//	(char []){0,0,0} \
//	} ,3 
//# define Z_FIGURE \
//	(char *[]){\
//	(char []){1,1,0},\
//	(char []){0,1,1}, \
//	(char []){0,0,0}\
//	}, 3
//# define T_FIGURE \
//	(char *[]){\
//	(char []){0,1,0},\
//	(char []){1,1,1},\
//	(char []){0,0,0}\
//	}, 3
//# define L_FIGURE \
//	(char *[]){\
//	(char []){0,0,1},\
//	(char []){1,1,1}, \
//	(char []){0,0,0}\
//	}, 3
//# define J_FIGURE \
//	(char *[]){\
//	(char []){1,0,0},\
//	(char []){1,1,1}, \
//	(char []){0,0,0}\
//	}, 3
//# define O_FIGURE \
//	(char *[]){\
//	(char []){1,1},\
//	(char []){1,1}\
//	}, 2
//# define I_FIGURE \
//	(char *[]){\
//	(char []){0,0,0,0}, \
//	(char []){1,1,1,1}, \
//	(char []){0,0,0,0}, \
//	(char []){0,0,0,0}\
//	}, 4
	
//t_tetrimino type_tetrimino[7]= {
//	{
//		S_FIGURE
//	},
//	{
//		Z_FIGURE
//	},
//	{
//		T_FIGURE
//	},
//	{
//		L_FIGURE
//	},
//	{
//		J_FIGURE
//	},
//	{
//		O_FIGURE
//	},
//	{
//		I_FIGURE
//	}
//};