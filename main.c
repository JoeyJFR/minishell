#include "mini_exec.h"

char	*set_prompt(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		exit (1);
	}
	cwd = ft_strjoin_cwd(cwd, " > ");
	if (!cwd)
	{
		perror("malloc when strjoin");
		exit (1);
	}
	return (cwd);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*rl;
	char	*cwd;
	t_data	data;
	t_parse	*parse_result;
	pid_t	pid;

	cwd = set_prompt();
	while (1)
	{
		//check signal, if signal control C , just print path, or D, I free space, exit, control \ do nothing
		rl = readline(cwd);
		// if (rl == NULL)
		// {
		// 	printf("Input error or EOF detected.\n");
		// 	free(cwd);
		// 	rl_clear_history();
		// 	return (1);
		// }
		add_history(rl);
		// /wait from Vincent's work
		parse_result = parsing(rl);
		// t_parse	*temp = parse_result;
		// while (temp)
		// {
		// 	printf("%s\n", temp->str);
		// 	temp = temp->next;
		// }
		free(rl);
		if (!parse_result)
		{
			printf("fail to parse.\n");
			free(cwd);
			return (1);
		}
		if (check_env(env))
		{
			printf("error in environment.\n");
			return (1);
		}
		data.env = env;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
		{
			//exec in child process
			if (exec(parse_result, &data) == -1)
			{
				printf("error in exec.\n");
				//free t_parse struct
				exit (-1);
			}
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	free(cwd);
	rl_clear_history();
	//free t_parse struct;
	return (0);
}

//need to compile with -lreadline flag for readline header file
//need to check to free return from readline() and getcwd
