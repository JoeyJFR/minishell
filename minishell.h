#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

//ARG_MAX = 2097152 bytes
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef enum s_type
{
	ARG,
	ABS,
	CD,
	EXPORT,
	EXIT,
	PWD,
	ENV,
	ECHO,
	UNSET,
	SL,
	SR,
	DL,
	DR,
	PI,
}	t_type;

typedef struct s_token
{
	char			*str;
	t_type			type;	
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_alloc
{
	t_env	*env_head;
	t_token	*token_head;
	char	*str;
}	t_alloc;

typedef struct s_data
{
	char	*env[BUFFER_SIZE];
	t_token	*cmd_pos;
	pid_t	*pid;
	int		pid_nb;
	int		open_in_fail;
	int		open_out_fail;
	int		infile;
	int		outfile;
}	t_data;

//main
t_env	*parse_env(char **env);
t_token	*parsing(char *buffer, t_env *env);
void	free_env(t_env *env);
int		check_path(t_env *env_head);
int		exec(t_token *parse_result, t_data *data);
int		built_in(t_token *token, t_env *env);

//list functions
t_env	*env_lstnew(char *str);
int		env_lstadd_back(t_env **lst, t_env *new);
t_token	*mini_lstnew(char *str);
void	mini_lstadd_back(t_token **lst, t_token *new);
/*						PARSING							*/
int		check_quotes(char *s);
//convert env variables
char	*convert_var(char *buf, t_alloc *data);
char	*add_env_var(char *str, t_alloc *data, int var_i, int buf_len);

int		is_in_squote(char *str);
//	
int		len_word(char *s);
void	free_token(t_token *token);
int		is_ope(char c, char *current);
char	*fill_ope(char **str, char *result);
char	*fill_word(char **str, char *result);
void	define_ope(t_token *node);
void	define_type(t_token *node);
void	exit_parsing(char *str, t_alloc *data, int status);
void	print_error(char *str);

//built_in directory
//cd
void	mini_cd(t_token *pr, t_env *env);
//env
void	mini_env(t_env *env);
//export
void	mini_export(t_env *env, t_token *token);
int		check_in_env(t_env *env, char *str);
int		check_name(char *str);
int		check_def(char *str);
void	change_var(t_env *env, char *str, int i);
void	ascii_env(t_env *env);
//exit
void	mini_exit(void);
//pwd
void	mini_pwd(t_token *token);
//echo
void	mini_echo(t_token *token);

// 
//builtin
void	check_b_cd(t_token *parse_result);
void	check_b_exit(t_token *parse_result, t_env *env_head);
void	check_b_export(t_token *parse_result, t_env *env_head);
int		cal_env_nb(t_env *env_head);
void	mini_unset(t_env *env, t_token *token);

//exec
int		count_pid(t_token *parse_result);
int		ft_ope(t_token **parse_result, t_data *data, char *av[], int cmd_index);
int		handle_heredoc(t_token *parse_result);
char	*get_next_line(int fd);
int		handle_pipe(char *av[], t_data *data);
int		exec(t_token *parse_result, t_data *data);
void	reform_env(t_env *env, char *environ[]);
void	handle_execve_fail(t_data *data, char *path);
char	**ft_split(char const *s, char c);
void	exec_cmd(char *av[], t_data *data);
void	ft_built(char *av[], t_data *data);
void	ft_echo(char *av[], t_data *data);
void	check_b_pwd(char *av[]);
void	check_b_env(char *av[], t_data *data);
int		get_error_code(void);
void	print_equal(char *s, char *pos);
void	print_space(char *s);
int		wait_dup_free(t_data *data, t_token *parse_result);

#endif
