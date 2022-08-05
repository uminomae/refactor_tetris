NAME		:= tetris
CC			:= gcc
RM			:= rm -f
#CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		:= 
SRCS		:= 	$(wildcard *.c)
OBJS	= $(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -lncurses -o $(NAME)

clean:
	$(RM) $(OBJS) 

fclean:	clean
	$(RM) $(NAME)

re: fclean all

#debug: CFLAGS +=  -g -fsanitize=address -fsanitize=undefined
#debug: re

.PHONY: all clean fclean re debug
