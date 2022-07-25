/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:40:38 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:40:50 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция memmove() копирует len байтов из области памяти src в облать памяти dst.
Области памяти могут перекрываться.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функция memmove() возвращает указатель на dst.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	if (s > d)
		while (len--)
			*d++ = *s++;
	else
	{
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "Start stop";
	char	str2[] = "Start stop";
	
	printf("%s\n", str1);

	ft_memmove(str1 + 2, str1 + 1, 5 * sizeof(char));
	memmove(str2 + 2, str2 + 1, 5 * sizeof(char));

	printf("ft	: %s\n", str1);
	printf("c	: %s\n", str2);
	return (0);
}
*/