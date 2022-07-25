/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:44:30 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:44:35 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Описание
Функция strlcpy копирует из строки src в буфер dst не более чем dstsize -1
символов и гарантированно устанавливает в конец строки нулевой символ.

Возвращаемое значение
strlcpy возвращает размер строки по адресу src.
*/
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	i = 0;
	srcsize = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "Start";
	char	str2[] = "Stop";
	char	str3[] = "Start";
	char	str4[] = "Stop";

	printf("ft	: %ld\n", ft_strlcpy(str1, str2, 5));
	printf("str1	: %s\n", str1);
	printf("str2	: %s\n", str2);
	
	printf("c	: %ld\n", strlcpy(str3, str4, 5));
	printf("str3	: %s\n", str3);
	printf("str4	: %s\n", str4);
	return (0);
}
*/