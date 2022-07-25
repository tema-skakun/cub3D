/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:38:50 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:39:10 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция memchr() ищет символ c в первых n байтах той области памяти,
на которую указывает s. Совпадение первого байта с c
(представленным как беззнаковый символ) останавливает выполнение операции.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функциb memchr() возвращают указатель на совпадающий
байт или NULL, если символ не найден в данной области памяти.  
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	sym;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	sym = (unsigned char) c;
	while (n--)
	{
		if (*ptr == sym)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*mas = "aaabcd";
	int	k = 98;
	int	i = 6;

	printf("ft	: %p\n", ft_memchr(mas, k, i));
	printf("c	: %p\n", memchr(mas, k, i));
	return (0);
}
*/