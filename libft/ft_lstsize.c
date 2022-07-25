/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:47:27 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/27 13:47:27 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
№ 1. Начало списка.

Возвращаемое значение
Длина списка.

Внешние функции.
Никто

Описание
Подсчитывает количество элементов в списке.
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*a;
	char	*b = "123";
	char	*c = "456";
	char	*d = "789";
	
	a = ft_lstnew(b);
	a->next = ft_lstnew(c);
	a->next->next = ft_lstnew(d);
	printf("%d\n", ft_lstsize(a));
}
*/