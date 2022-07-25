/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:46:06 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:46:11 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция strrchr() возвращает указатель на местонахождение последнего
совпадения с символом c в строке s.
Здесь, "символ" означает "байт" - эта функция не работает с широкими и
многобайтными символами.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функции strrchr() возвращают указатель на совпадения с
соответствующим символом, а если символ не найден, то возвращают NULL.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*buf;

	buf = NULL;
	while (*s)
	{
		if (*s == (char)c)
			buf = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (buf);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		n = '4';
	char	*str = "jhgfdnbvc    40Qg2UVZs8 8Uiju7V6T0hqP";

	printf("ft	: %s\n", ft_strrchr(str, n));
	printf("c	: %s\n", strrchr(str, n));
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	char		sym;

	sym = (char) c;
	i = ft_strlen(s);
	s += i;
	while (*s != s[0] && *s != sym) //ошибка в условии
		s--;
	if (*s == sym)
		return ((char *)s);
	return (NULL);
}
*/