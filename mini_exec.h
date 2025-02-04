
#ifndef MINI_EXEC_H
# define MINI_EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
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
	DL,
	SR,
	DR,
	PIPE,
	ABS_PATH,
	BUILT_IN
}	t_type;

typedef struct s_parse
{
	char			*str;
	t_type			type;	
	struct s_parse	*prev;
	struct s_parse	*next;
}	t_parse;

typedef enum e_error
{
	SUCCESS,
	ERR_PARAMETERS,
	ERR_ENV,
	ERR_PIPE,
	ERR_FORK,
	ERR_FD,
	ERR_DUP,
	ERR_EMPTY_CMD,
	ERR_MALLOC,
	ERR_FINDING_PATH,
	ERR_EXEC
}	t_error;

typedef struct s_data
{
	char	**env;
	char	*cmd;
	t_parse	*cmd_pos;
	pid_t	*pid;
	int		pid_nb;
	int		infile;
	int		outfile;
	int		stdin_backup;
	int		stdout_backup;
	int		open_in_fail;
	int		open_out_fail;
}	t_data;

char	*ft_strjoin_cwd(char *s1, char *s2);
t_parse	*parsing(char *str);
int		check_env(char *env[]);
int		exec(t_parse *parse_result, t_data *data);
int		ft_ope(t_parse **parse_result, t_data *data, \
				char *av[], int cmd_index);
int		handle_pipe(char *av[], t_data *data);
void	exec_cmd(char *av[], t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
int		handle_heredoc(t_parse *parse_result);
t_parse	*mini_lstnew(char *str);
void	mini_lstadd_back(t_parse **lst, t_parse *new);
void	mini_error(char *str, int status);
size_t	ft_strlen(const char *str);
int		count_pid(t_parse *parse_result);
int		wait_dup_free(t_data *data, t_parse *parse_result);
int		get_error_code(void);
void	handle_execve_fail(t_data *data, char *path);
void	ft_built(char *av[], t_data *data);
void	ft_echo(char *av[], t_data *data);
void	free_parse(t_parse *p);
void	cd_exp_un_ex(t_parse *parse_result);
void	check_b_cd(t_parse *parse_result);
int		check_cd_exp_un_ex(t_parse *parse_result);
void	check_b_pwd(char *av[]);
void	check_b_env(char *av[], t_data *data);




int		check_arg(char *arg, t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *str, char c);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);




#endif
