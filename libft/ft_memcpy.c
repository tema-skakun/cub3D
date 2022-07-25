/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:40:05 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:40:19 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция memcpy() копирует n байтов из области памяти src в область памяти dst.
Области памяти не могут пересекаться. Используйте memmove(3), если области
памяти перекрываются.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функция memcpy() возвращает указатель на dst.
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	while (n--)
		*d++ = *s++;
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
	ft_memcpy(str1, str1 + 2, 3 * sizeof(char));
	memcpy(str2, str2 + 2, 3 * sizeof(char));
	printf("ft	: %s\n", str1);
	printf("c	: %s\n", str2);
	return (0);
}
*/