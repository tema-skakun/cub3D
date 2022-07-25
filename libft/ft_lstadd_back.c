/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:24:45 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/27 13:44:56 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
№ 1. Адрес указателя на первую ссылку списка.
# 2. Адрес указателя на элемент, который будет
добавлен в список.

Возвращаемое значение
Отсутствует

Внешние функции.
Никто

Описание
Добавляет элемент "new" в конце списка.
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lstlast(*(lst));
			tmp->next = new;
		}
	}
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
	t_list	*a1;
	t_list	*a2;
	char	*b = "123";
	char	*c = "456";
	char	*d = "789";

	a1 = ft_lstnew(b);
	a1->next = ft_lstnew(c);
	print_content(a1);
	printf("\n");
	a2 = ft_lstnew(d);
	print_content(a2);
	printf("\n");
	ft_lstadd_back(&a1, a2);
	print_content(a1);
	return (0);
}
*/