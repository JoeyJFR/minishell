# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjiang <zjiang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 13:27:04 by zjiang            #+#    #+#              #
#    Updated: 2025/02/03 14:54:55 by zjiang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = check.c command.c exec.c ft_split.c get_next_line_utils.c get_next_line.c \
heredoc.c main.c mini_lst.c mini_utils.c ope.c parsing.c pipe.c utils1.c utils2.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME = shell

MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) Makefile mini_exec.h libft.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline
	
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re