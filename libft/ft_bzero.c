/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:34:01 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:34:30 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция bzero() устанавливает первые n байтов области, начинающейся с s в нули
(пустые байты).

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Нет возвращаемых значений.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = '\0';
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int	arr1[] = {3, 4, 5};
	int	arr2[] = {1, 2, 3};

	ft_bzero(arr1, 1 * sizeof(int));
	bzero(arr2, 1 * sizeof(int));
	printf("ft	: %d %d %d\n", arr1[0], arr1[1], arr1[2]);
	printf("c	: %d %d %d\n", arr2[0], arr2[1], arr2[2]);
	return (0);
}
*/