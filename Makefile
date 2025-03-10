CC=cc

SRC=src/main.c src/mini_lst.c src/env_lst.c src/exit_utils.c \
	src/parsing/parsing.c src/parsing/parsing_utils.c src/parsing/convert_var.c src/parsing/convert_var_2.c \
	src/parsing/parsing_env.c src/parsing/fill_node_utils.c src/parsing/check_syntax.c \
	src/built_in/mini_cd.c src/built_in/mini_export.c src/built_in/mini_exit.c src/built_in/mini_env.c src/built_in/mini_echo.c\
	src/built_in/mini_pwd.c src/built_in/mini_unset.c src/built_in/mini_export_2.c src/built_in/mini_export_3.c\
	src/execution/command.c src/execution/command_utils1.c src/execution/command_utils2.c src/execution/command_utils3.c\
	src/execution/exec.c src/execution/exec_utils1.c src/execution/exec_utils2.c\
	src/execution/open_heredoc.c src/execution/open_file.c src/execution/pipe.c src/execution/pipe_utils.c src/execution/redirect.c src/execution/handle_heredoc.c\
	src/execution/check_builtin.c\
	src/execution/signal.c \
	src/parsing/quote_utils.c

LIBFT=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c\
	ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf_utils.c ft_printf_writechars.c ft_printf_writenbrs.c ft_printf.c ft_strcpy.c get_next_line.c libft.h Makefile

LIBFT_FILES=$(addprefix $(PATH_LIB), $(LIBFT))

SRCDIR=src

OBJDIR=.obj

OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS= -Wextra -Wall -Werror -g3

INC=minishell.h

PATH_LIB=./libft/

LIB=libft.a

NAME=minishell


all : $(NAME)

debug : $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=ignore_rl.txt --trace-children=yes --track-fds=yes --track-origins=yes -s  --show-mismatched-frees=yes ./$(NAME)

$(NAME) : $(OBJ) $(PATH_LIB)$(LIB)
	@$(MAKE) --no-print-directory -C $(PATH_LIB)
	@$(CC)  $(OBJ) -o $(NAME) $(PATH_LIB)$(LIB) -lreadline
	@echo "$@ Compiled !"

$(PATH_LIB)$(LIB) : $(LIBFT_FILES)
	@$(MAKE) --no-print-directory -C $(PATH_LIB)

$(OBJDIR)/%.o : src/%.c $(INC) Makefile $(PATH_LIB)$(LIB) | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "Compiling $<"

$(OBJDIR) :
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/parsing
	@mkdir -p $(OBJDIR)/execution
	@mkdir -p $(OBJDIR)/built_in

clean :
	@rm -rf $(OBJDIR)
	@echo "Objects cleaned"

lclean :
	@$(MAKE) --no-print-directory fclean -C $(PATH_LIB)

fclean : lclean clean
	@rm -f $(NAME)
	@echo "Exec cleaned"

flclean : fclean lclean

re : fclean all

.PHONY : fclean clean re all lclean flclean	
