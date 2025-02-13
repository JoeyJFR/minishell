/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgarcia <vgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:07:10 by vgarcia           #+#    #+#             */
/*   Updated: 2024/11/13 09:49:06 by vgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	negative_check(char nptr)
{
	if (nptr == '-')
		return (-1);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long int				result;
	int									i;
	int									t;

	result = 0;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	t = negative_check(nptr[i]);
	if (nptr[i] == '-' || nptr[i] == '+')
		++i;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i++] - 48;
		if ((result * 10 / 10) != result)
		{
			if (t < 0)
				return (0);
			return (-1);
		}
	}
	return (result * t);
}
