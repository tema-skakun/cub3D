/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:44:53 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/21 18:41:13 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция strlen() вычисляет длину строки s. Завершающий символ '\0'
не учитывается.

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функция strlen() возвращает количество символов в строке s.
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s;

	s = "Hi guys";
	printf("ft	: %ld\n", ft_strlen(s));
	printf("c	: %lu\n", strlen(s));
	return (0);
}
*/