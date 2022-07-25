/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:46:55 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/27 13:46:55 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
№ 1. Начало списка.

Возвращаемое значение
Последнего элемента списка.

Внешние функции.
Никто

Описание
Возвращает последний элемент списка
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (lst)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}
/*
#include <stdio.h>

void	print_content(t_list *begin)
{
	while (begin)
	{
		printf("%s\n", begin->content);
		begin = begin->next;
	}
}

int	main(void)
{
	t_list	*a;
	char	*b = "123";
	char	*c = "456";
	char	*d = "789";

	a = ft_lstnew(b);
	a->next = ft_lstnew(c);
	a->next->next = ft_lstnew(d);
	print_content(a);
	printf("\n");
	a = ft_lstlast(a);
	print_content(a);
	return (0);
}
*/