/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:41:12 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:42:19 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция memset() заполняет первые len байтов той области памяти, на которую
указывает b, постоянным байтом c.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функция memset() возвращает указатель на область памяти b.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (len > i)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int	arr1[] = {3, 4, 5};
	int	arr2[] = {1, 2, 3};
	
	ft_memset(arr1, 0, 2 * sizeof(int));
	memset(arr2, 0, 2 * sizeof(int));
	printf("ft	: %d %d %d\n", arr1[0], arr1[1], arr1[2]);
	printf("c	: %d %d %d\n", arr2[0], arr2[1], arr2[2]);
	return (0);
}
*/