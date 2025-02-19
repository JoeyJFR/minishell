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
# include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

extern int	g_sigint;

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
	int		exit_status;
	t_env	*env_head;
	t_token	*token_head;
	char	*str;
}	t_alloc;

typedef struct s_data
{
	int		infile;
	int		outfile;
	int		stdout_backup;
	int		stdin_backup;
	int		pid_nb;
	pid_t	*pid;
	int		cmd_i;
	int		no_permission;
	char	*env[BUFFER_SIZE];
	char	*av[BUFFER_SIZE];
}	t_data;

void	printl(t_token *list);
//main
t_env	*parse_env(char **env);
t_token	*parsing(char *buffer, t_env *env, int *exit_code);
void	free_env(t_env *env);
int		check_path(t_env *env_head);
int		exec(t_alloc *alloc, t_env *env, t_token *token);

//list functions
t_env	*env_lstnew(char *str);
int		env_lstadd_back(t_env **lst, t_env *new);
t_token	*mini_lstnew(char *str);
void	mini_lstadd_back(t_token **lst, t_token *new);
//error utils
void	exit_parsing(char *str, t_alloc *data, int status);
void	print_error(char *str);
void	exit_with_msg(char *str, int status);
/*						PARSING							*/
//convert env variables
char	*convert_var(char *buf, t_env *env, int exit_code);
char	*add_env_var(char *str, t_env *env, int var_i, int buf_len);

int		check_quotes(char *s);
int		is_in_squote(char *str);
int		update_quote_var(int *in_quote, char **c);
//	
int		check_syntax(t_token *token);
int		len_word(char *s);
void	free_token(t_token *token);
int		count_cmd(t_token *token);
int		is_ope(char c, char *current);
char	*fill_str(char **buf, char *result, int x);
void	define_ope(t_token *node);
void	define_type(t_token *node);
void	print_token(t_token *token);

//built_in directory
//cd
int		mini_cd(char *av[], t_data *data, t_alloc *alloc);
//env
int		mini_env(t_alloc *alloc);
//export
int		mini_export(char *av[], t_alloc *alloc, t_data *data);
int		check_in_env(t_env *env, char *str);
int		check_name(char *str);
int		check_def(char *str);
int		change_var(t_env *env, char *str, int i);
void	ascii_env(t_env *env, t_alloc *alloc, t_data *data);
//exit
int		mini_exit(char *av[], t_alloc *alloc, t_data *data);
//pwd
int		mini_pwd(char *av[]);
//echo
int		mini_echo(char *av[], t_alloc *alloc, t_data *data);
//unset
int		mini_unset(t_env *env, char *av[]);

//exec
int		count_pid(t_token *parse_result);
int		handle_heredoc(t_token *parse_result, t_data *data);
char	*get_next_line(int fd);
int		handle_pipe(t_token *token, char *av[], t_data *data, t_alloc *alloc);
void	reform_env(t_env *env, char *environ[]);
void	exec_cmd(char *av[], t_data *data, t_alloc *alloc);
int		get_error_code(void);
void	wait_free(t_data *data, t_alloc *alloc);
void	open_file(t_data *data, t_token **token);
int		redirect_file(t_data *data, t_token **parse_result);
void	open_heredoc(t_token *parse_result, t_data *data);
int		check_ope(t_token *token);
int		check_inter_ope(t_token *token);
void	close_all_fd(t_data *data);
int		built_in(char *av[], t_data *data, t_alloc *alloc);
int		check_built(char *s);
int		check_only_builtin(char *av[], t_alloc *alloc);
char	*ft_strjoin1(char const *s1, char const *s2);
int		check_built(char *s);
int		close_2_get_error_code(int fd1, int fd2);
void	waitfree_get_error_code(t_data *data, t_alloc *alloc);
void	handle_execve_fail(t_data *data, char *path, char *s, t_alloc *alloc);
void	free_alloc_pid(t_alloc *alloc, t_data *data);
void	handle_directory_fail(t_data *data, char *path, char *s, t_alloc *alloc);
void	handle_rel_sfail(t_data *data, char *s, t_alloc *alloc);
void	handle_rel_fail(t_data *data, char *path, char *s, t_alloc *alloc);
void	pipe_pid_fail(int fd[], t_data *data, t_alloc *alloc);
int		handle_open_fail(int fd[], t_data *data);
int		check_special(t_token *token);
char	*find_path(char *cmd, char *env[], t_data *data, t_alloc *alloc);

//signal
void	init_signal(void);
void	sigint_handler(int sig);
void	sigterm_handler(int sig);
void	sigquit_handler(int sig);
void	child_int(int sig);

#endif
