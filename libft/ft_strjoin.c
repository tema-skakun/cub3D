/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:49:46 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/11/06 10:49:04 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
#1. Строка префикса.
#2. Строка суффикса.

Возвращаемое значение
Новая строка. Значение NULL, если выделение завершится неудачно.

Описание
Выделяет (с помощью malloc(3)) и возвращает новую
строку, которая является результатом объединения
"s1" и "s2".
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[] = "Start";
	char	str2[] = "Stop";

	printf("ft	: %s\n", ft_strjoin(str1, str2));
	return (0);
}
*/