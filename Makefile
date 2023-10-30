NAME = philosophers

CFLAGS = -Wall -Wextra -Werror -pthread 

RM = rm -f

SRCS := src/main.c src/thread_handler.c src/state_handler.c src/utils.c
OBJS := $(SRCS:.c=.o)

$(NAME): $(OBJS)
	    gcc $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

fclean: clean
	    $(RM) $(NAME)

clean:
	    $(RM) $(OBJS)

re: fclean all
