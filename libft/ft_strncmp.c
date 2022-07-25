/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:45:24 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/15 17:45:44 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция strcmp() сравнивает две строки: s1 и s2.
Она возвращает целое число, которое меньше, больше нуля или равно ему,
если s1 соответственно меньше, больше или равно s2.
Функция strncmp() работает аналогичным образом,
но сравнивает только первые n символов строки s1.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функции strcmp() и strncmp() возвращают целое число, которое меньше,
больше нуля или равно ему, если строка s1 (или ее первые n байтов)
соответственно меньше, больше или равна (равны) s2.
Сравнение выполняется с использованием unsigned characters, так что "\200"
больше, чем "\0".
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n-- && (*c1 || *c2))
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		n = 3;

	char	*str1 = "ART\0";
	char	*str2 = "FDA\0";

	printf("ft\t:\t%d\n", ft_strncmp(str1, str2, n));
	printf("c\t:\t%d\n", strncmp(str1, str2, n));
	return (0);
}
*/