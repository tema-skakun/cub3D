/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:46:07 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/27 13:46:07 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры 

№ 1. Адрес указателя на первую ссылку
списка.
#2. Адрес указателя на элемент, который будет
добавлен в список.

Возвращаемое значение
Отсутствует

Внешние функции.
Никто

Описание
Добавляет элемент "new" в начало списка.
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != (void *)0 && new != (void *)0)
	{
		new->next = *lst;
		*lst = new;
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
	t_list	*a;
	char	*b = "123";
	char	*c = "456";
	char	*d = "789";
	t_list	*e;

	a = ft_lstnew(b);
	a->next = ft_lstnew(c);
	print_content(a);
	printf("\n");
	e = ft_lstnew(d);
	ft_lstadd_front(&a, e);
	print_content(a);
	return (0);
}
*/