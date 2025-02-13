/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentgarcia <vincentgarcia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:49:36 by vincentgarc       #+#    #+#             */
/*   Updated: 2024/11/12 22:33:04 by vincentgarc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!new)
	{
		new = ft_lstnew(NULL);
		if (!new)
			return ;
	}
	if (!*lst)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}
/*
void	*ft_lsttoupper(void *content)
{
	*(char *)content -= 32;
	printf("passe\n");
	return (content);
}
void	lsttoupper(void *content)
{
	*(char *)content += 2;
	printf("passe lstiter\n");
}
int	main(void)
{
	t_list *test;
	t_list *test2;
	t_list *dl;
	t_list *el;
	char c = 'c';
	char d = 'd';
	char e = 'e';

	test = ft_lstnew(&c);
	dl = ft_lstnew(&d);
	el = ft_lstnew(&e);
	ft_lstadd_back(&test, dl);
	printf("initial test : %c\n", *(char *)test->content);
	ft_lstadd_front(&test, el);
	printf("size test : %d\n", ft_lstsize(test));
	printf("addfront test : %c\n", *(char *)test->content);
	ft_lstiter(test, &lsttoupper);
	test2 = ft_lstmap(test, &ft_lsttoupper, NULL);
	printf("lstmap test : %c\n", *(char *)test2->content);
	test = ft_lstlast(test);
	printf("lstlast : %c\n", *(char *)test->content);
}*/
