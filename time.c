#include "tetris.h"

////struct timeval {
////    time_t      tv_sec;     /* 秒 */
////    suseconds_t tv_usec;    /* マイクロ秒 */
////};
suseconds_t get_millisecond(struct timeval timevalue){
	return (timevalue.tv_sec * MILLION + timevalue.tv_usec);
}

bool need_update(t_tetris *tetris){
	const suseconds_t now_ms = get_millisecond(now);
	const suseconds_t before_now_ms = get_millisecond(before_now);
	return (now_ms - before_now_ms > tetris->time_to_update);
}
