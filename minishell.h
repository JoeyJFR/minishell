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
	int		open_out_fail;
	int		open_in_fail;
	int		pid_nb;
	pid_t	*pid;
	int		cmd_i;
	char	*env[BUFFER_SIZE];
}	t_data;

//main
t_env	*parse_env(char **env);
t_token	*parsing(char *buffer, t_env *env, int exit_code);
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
int		check_quotes(char *s);
//convert env variables
char	*convert_var(char *buf, t_env *env, int exit_code);
char	*add_env_var(char *str, t_env *env, int var_i, int buf_len);

int		is_in_squote(char *str);
//	
int		check_syntax(t_token *token);
int		len_word(char *s);
void	free_token(t_token *token);
int		count_cmd(t_token *token);
int		is_ope(char c, char *current);
char	*fill_ope(char **str, char *result);
char	*fill_word(char **str, char *result);
void	define_ope(t_token *node);
void	define_type(t_token *node);

//built_in directory
//cd
int		mini_cd(char *av[], t_data *data);
//env
int		mini_env(t_alloc *alloc);
//export
int		mini_export(char *av[], t_alloc *alloc);
int		check_in_env(t_env *env, char *str);
int		check_name(char *str);
int		check_def(char *str);
void	change_var(t_env *env, char *str, int i, t_alloc *alloc);
void	ascii_env(t_env *env, t_alloc *alloc);
//exit
void	mini_exit(char *av[], t_alloc *alloc, t_data *data);
//pwd
int		mini_pwd(char *av[]);
//echo
int		mini_echo(char *av[]);

// 
//builtin
void	check_b_cd(t_token *parse_result);
void	check_b_exit(t_token *parse_result, t_env *env_head);
void	check_b_export(t_token *parse_result, t_env *env_head);
int		cal_env_nb(t_env *env_head);
int		mini_unset(t_env *env, char *av[]);

//exec
int		count_pid(t_token *parse_result);
int		ft_ope(t_token **parse_result, t_data *data, char *av[], int cmd_index);
int		handle_heredoc(t_token *parse_result);
char	*get_next_line(int fd);
int		handle_pipe(t_token *token, char *av[], t_data *data, t_alloc *alloc);
void	reform_env(t_env *env, char *environ[]);
void	handle_execve_fail(t_data *data, char *path);
char	**ft_split(char const *s, char c);
void	exec_cmd(char *av[], t_data *data, t_alloc *alloc);
void	ft_built(char *av[], t_data *data);
void	ft_echo(char *av[], t_data *data);
void	check_b_pwd(char *av[]);
void	check_b_env(char *av[], t_data *data);
int		get_error_code(void);
void	print_equal(char *s, char *pos);
void	print_space(char *s);
void	wait_free(t_data *data, t_alloc *alloc);
void	open_file(t_data *data, t_token **token);
int		redirect_file(t_data *data, t_token **parse_result);
void	open_heredoc(t_token *parse_result);
int		check_ope(t_token *token);
int		check_inter_ope(t_token *token);
void 	free_close(t_data *data);
void	close_all_fd(t_data *data);
int		built_in(char *av[], t_data *data, t_alloc *alloc);
int		check_built(char *s);
int		check_only_builtin(char *av[], t_alloc *alloc);

#endif
