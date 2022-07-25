/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:28:41 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/11/06 10:51:42 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
#1. Строка, из которой создается подстрока.
#2. Начальный индекс подстроки в строке "s".
#3. Максимальная длина подстроки.

Описание
Выделяет (с помощью malloc(3)) и возвращает подстроку
из строки "s". Подстрока начинается с индекса "start" и имеет
максимальный размер 'len'.

Возвращаемое значение
Подстрока. Значение NULL, если выделение завершится неудачно.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	n;

	if (s == NULL)
		return (NULL);
	n = ft_strlen(s);
	if (len > n)
		str = (char *)malloc(sizeof(char) * (n + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start < n && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*c;
	char	*d;

	c = "tripouille";
	d = ft_substr(c, 0, 42000);
	printf("%s\n", d);
	free(d);
	return (0);
}
*/