CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
SRCDIRS = src src/execution src/parsing
SRC = $(wildcard $(addsuffix /*.c, $(SRCDIRS))) # Find all .c files
OBJ = $(SRC:.c=.o) # Convert .c filenames to .o
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
