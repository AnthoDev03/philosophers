NAME = philosophers

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS 		:= src/main.c src/thread_handler.c src/state_handler.c src/utils.c

$(NAME) :
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all
