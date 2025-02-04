/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjiang <zjiang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:50:54 by zjiang            #+#    #+#             */
/*   Updated: 2025/02/04 15:03:44 by zjiang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		write(STDOUT_FILENO, data->env[i], ft_strlen(data->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	check_b_env(char *av[], t_data *data)
{
	if (!av[1])
		ft_env(data);
	else
		write(STDOUT_FILENO, "wrong input, use: export with no options.\n", 43);
}