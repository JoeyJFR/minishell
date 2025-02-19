/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:51:12 by vgarcia           #+#    #+#             */
/*   Updated: 2025/02/18 14:39:19 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*fill_empty_env(void)
{
	t_env	*list;
	char	*pwd;

	list = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (NULL);
	}
	if (env_lstadd_back(&list, env_lstnew(ft_strdup("OLD_PWD"))))
		return (NULL);
	if (env_lstadd_back(&list, env_lstnew(ft_strdup(ft_strjoin("PWD=", pwd)))))
		free_env(list);
	if (env_lstadd_back(&list, env_lstnew(ft_strdup("SHLVL=1"))))
		free_env(list);
	return (list);
}

/*
copy the env into a chained-list
*/
t_env	*parse_env(char **env)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		if (env_lstadd_back(&env_list, env_lstnew(ft_strdup(env[i]))))
		{
			free_env(env_list);
			print_error("Alloc");
			exit(1);
		}
		++i;
	}
	if (i == 0)
		env_list = fill_empty_env();
	return (env_list);
}
