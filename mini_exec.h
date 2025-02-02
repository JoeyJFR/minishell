#ifndef MINI_EXEC_H
# define MINI_EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

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
	int		infile;
	int		outfile;
}	t_data;

char	*ft_strjoin_cwd(char *s1, char *s2);
t_parse	*parsing(char *str);
int		check_env(char *env[]);
int		exec(t_parse *parse_result, t_data *data);
int		ft_ope(t_parse **parse_result, t_data *data, char *av[], int *cmd_index);
void	handle_pipe(char *av[], t_data *data, int fd[]);
int		exec_cmd(char *av[], t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
void	handle_heredoc(t_parse *parse_result, t_data *data);
t_parse	*mini_lstnew(char *str);
void	mini_lstadd_back(t_parse **lst, t_parse *new);
void 	mini_error(char *str, int status);
size_t	ft_strlen(const char *str);

int		check_arg(char *arg, t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *str, char c);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);

#endif
