/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:55:39 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/25 17:43:50 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция strnstr ();
находит первое вхождение строки, заканчивающейся нулем,
Fa needle в строке Fa haystack, где выполняется поиск не более чем
Fa len символов. Символы, которые появляются после символа "\0",
не ищутся. Поскольку функция strnstr();
является API, специфичным для Fx, ее следует использовать
только тогда, когда переносимость не вызывает беспокойства.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Если Fa needle является пустой строкой, возвращается Fa haystack;
если Fa needle нигде не встречается в Fa haystack, возвращается NULL;
в противном случае возвращается указатель на первый символ
первого вхождения Fa needle.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	b;
	size_t	l;

	b = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[b] != '\0')
	{
		l = 0;
		while (haystack[b + l] == needle[l] && (b + l) < len)
		{
			if (haystack[b + l] == '\0' && needle[l] == '\0')
				return ((char *)haystack + b);
			l++;
		}
		if (needle[l] == '\0')
			return ((char *)haystack + b);
		b++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	haystack[30] = "aaabcabcdaa";
	char	needle[10] = "ab";
	int		n = 4;

	printf("ft	: %s\n", ft_strnstr(haystack, needle, n));
	printf("c	: %s\n", strnstr(haystack, needle, n));
	return (0);
}
*/