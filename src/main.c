#include "../minishell.h"

int main(int ac, char **av, char **env)
{
	char	*str;
	t_parse	*parse_result;
	t_env	*env_head;
	t_data	data;
	pid_t	pid;


	(void)ac;
	(void)av;
	env_head = parse_env(env);
	if (env_head == NULL)
		return (1);
	while (1)
	{
		str = readline("minishell > ");
		if (!str)
			break ;
		if (*str == '\0')
		{
			free(str);
			continue ;
		}
		add_history(str);
		parse_result = parsing(str, env_head);
		free(str);
		if (parse_result == NULL)
			return (free(str), printf("fail to parse.\n"), free_env(env_head), 1);
		if (check_cd_exp_un_ex(parse_result))
		{
			cd_exp_un_ex(parse_result, env_head);
			continue ;
		}
		if (check_env(env_head))
		{
			printf("error in environment: no PATH for execution.\n");
			continue ;
		}
		reform_env(env_head, data.env);
		pid = fork();
		if (pid == -1)
		{
			perror("fork in main loop");
			free_parse(parse_result);
			free_env(env_head);
			exit (get_error_code());
		}
		if (pid == 0)
			exit(exec(parse_result, &data, env_head));
		else
			waitpid(pid, NULL, 0);
		free_parse(parse_result);
	}
	free_env(env_head);
	rl_clear_history();
	return (0);
}
