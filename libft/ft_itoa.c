/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:24:55 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/22 15:33:47 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
#1. целое число для преобразования.

Возвращаемое значение
Строка, представляющая целое число. Значение NULL, если
выделение завершится неудачно.

Описание
Выделяет (с помощью malloc(3)) и возвращает строку,
представляющую целое число, полученное в качестве аргумента.
Отрицательные числа должны быть обработаны.
*/

#include "libft.h"

char	*fill_array(char *str, unsigned int n, int len)
{
	while (n > 0)
	{
		str[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

size_t	numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*res;
	unsigned int	number;

	len = numlen(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len--] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		number = -n;
		res[0] = '-';
	}
	else
		number = n;
	res = fill_array(res, number, len);
	return (res);
}
/*
#include <stdio.h>

int	main(void)
{
	int	n;

	n = -2147483648;
	printf("numlen	: %lu\n", numlen(n));
	printf("ft_itoa	: %s\n", ft_itoa(n));
	return (0);
}
*/