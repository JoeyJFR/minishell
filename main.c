#include "mini_exec.h"

char	*set_prompt(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		exit (get_error_code());
	}
	cwd = ft_strjoin_cwd(cwd, " > ");
	if (!cwd)
	{
		perror("malloc when strjoin cwd");
		exit (get_error_code());
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

	(void)argv;
	(void)argc;
	while (1)
	{
		cwd = set_prompt();
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
		if (check_cd_exp_un_ex(parse_result))
		{
			cd_exp_un_ex(parse_result);
			free(cwd);
			continue ;
		}
		if (check_env(env))
		{
			printf("error in environment.\n");
			continue ;
		}
		data.env = env;
		pid = fork();
		if (pid == -1)
		{
			perror("fork in main loop");
			exit (get_error_code());
		}
		if (pid == 0)
		{
			free(cwd);
			exit(exec(parse_result, &data));
		}
		else
			waitpid(pid, NULL, 0);
		free(cwd);
		free_parse(parse_result);
	}
	rl_clear_history();
	//free t_parse struct;
	return (0);
}

//need to compile with -lreadline flag for readline header file
//need to check to free return from readline() and getcwd
