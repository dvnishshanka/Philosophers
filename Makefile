CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
RM = rm -f
INCLUDE = -I include

SRCS = main.c utils.c parsing.c init.c
OBJS = $(SRCS:.c=.o)

# Compile source files into into object files
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean