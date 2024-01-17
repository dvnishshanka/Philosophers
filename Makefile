CC = gcc
# -g -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
NAME = philo
RM = rm -f
INCLUDE = -I include

SRCS = main.c utils.c parsing.c init.c safe_functions.c dinner.c getters_setters.c write.c monitor.c utils2.c
OBJS = $(SRCS:.c=.o)

# Compile source files into into object files
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

# -ltsan
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean