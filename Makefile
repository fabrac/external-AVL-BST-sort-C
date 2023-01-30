NAME	=	external_sort

CC	=	gcc

RM	=	rm -f

SRCS	=	 $(wildcard src/*.c)

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -g -I include/

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
