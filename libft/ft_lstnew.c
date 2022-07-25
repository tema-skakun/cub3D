/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:47:15 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/27 13:47:15 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
№ 1. content, с помощью которого будет создан новый элемент.

Возвращаемое значение
Новый элемент.

Внешние функции.
маллок

Описание
Выделяет (с помощью malloc(3)) и возвращает новый
элемент. Переменная "content" инициализируется
значением параметра "content".
Переменная "next" инициализируется значением NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*a;
	char	*b = "123";
	char	*c = "456";

	a = ft_lstnew(b);
	a->next = ft_lstnew(c);
	while (a != NULL)
	{
		printf("%s\n", a->content);
		a = a->next;
	}
	return (0);
}
*/