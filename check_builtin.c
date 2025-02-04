#include "mini_exec.h"

// *******TO DO: change printf to ft_printf

// void	check_b_unset(char *av[], t_data *data)
// {
// 	if (!av[1])
// 		ft_unset();
// 	printf("wrong input, use: unset with no options.\n");
// 	free(data->pid);
// 	exit (0);
// }

// void	check_b_env(char *av[], t_data *data)
// {
// 	if (!av[1])
// 		ft_env();
// 	printf("wrong input, use: env with no options or arguments.\n");
// 	free(data->pid);
// 	exit (0);
// }

// void	check_b_exit(char *av[], t_data *data)
// {
// 	if (!av[1])
// 		ft_exit();
// 	printf("wrong input, use: exit with no options.\n");
// 	free(data->pid);
// 	exit (0);
// }

int	check_cd_exp_un_ex(t_parse *parse_result)
{
	if (!ft_strcmp(parse_result->str, "cd"))
		return (1);
	if (!ft_strcmp(parse_result->str, "export"))
		return (1);
	if (!ft_strcmp(parse_result->str, "unset"))
		return (1);
	if (!ft_strcmp(parse_result->str, "exit"))
		return (1);
	return (0);
}
