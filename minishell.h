#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
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
	SL,
	SR,
	DL,
	DR,
	PI,
	ABS,
	BUILT_IN,
}	t_type;

typedef struct s_parse
{
	char			*str;
	t_type			type;	
	struct s_parse	*prev;
	struct s_parse	*next;
}	t_parse;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char	*env[BUFFER_SIZE];
	t_parse	*cmd_pos;
	pid_t	*pid;
	int		pid_nb;
	int		open_in_fail;
	int		open_out_fail;
	int		infile;
	int		outfile;
}	t_data;

//main
t_env	*parse_env(char **env);
t_parse	*parsing(char *buffer, t_env *env);
void	free_env(t_env *env);
int		check_cd_exp_un_ex(t_parse *parse_result);
void	cd_exp_un_ex(t_parse *parse_result, t_env *env_head);
int		check_env(t_env *env_head);
int		exec(t_parse *parse_result, t_data *data);

//parse_env
t_env	*env_lstnew(char *str);
int		env_lstadd_back(t_env **lst, t_env *new);

//parsing
int		check_quotes(char *s);
char	*convert_var(char *buf, t_env *env);
int		is_in_squote(char *str);
int		len_word(char *s, char c);
char	*fill_str(char **str, char c, char *result);
t_parse	*mini_lstnew(char *str);
void	mini_lstadd_back(t_parse **lst, t_parse *new);
void	free_parse(t_parse *parse);

//builtin
void	check_b_cd(t_parse *parse_result);
void	check_b_exit(t_parse *parse_result, t_env *env_head);
void	check_b_export(t_parse *parse_result, t_env *env_head);
int		cal_env_nb(t_env *env_head);

//exec
int		count_pid(t_parse *parse_result);
int		ft_ope(t_parse **parse_result, t_data *data, char *av[], int cmd_index);
int		handle_heredoc(t_parse *parse_result);
char	*get_next_line(int fd);
void	ft_putstr_fd(char *s, int fd);
int		handle_pipe(char *av[], t_data *data);
int		exec(t_parse *parse_result, t_data *data);
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
int		wait_dup_free(t_data *data, t_parse *parse_result);


char	*ft_strjoin_gnl(char **head, char **end);
int		check_end(char *temp);
void	new_start(char start[], char *lines);


//libft
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_isalnum(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);


#endif
