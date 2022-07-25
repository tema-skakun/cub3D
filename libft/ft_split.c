/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:52:36 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/27 14:26:27 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
#1. Строка, которую нужно разделить.
#2. Символ-разделитель.

Возвращаемое значение
Массив новых строк, полученных в результате разделения.
Значение NULL, если выделение завершится неудачно.

Внешние факторы.
malloc, free

Описание
Выделяет (с помощью malloc(3)) и возвращает массив
строк, полученных путем разделения "s" с использованием
символа "c" в качестве разделителя. Массив должен
заканчиваться НУЛЕВЫМ указателем.
*/

#include "libft.h"

size_t	word_counter(char const *s, char c)
{
	size_t	count;
	int		i;

	count = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**sub_split(char **arr, char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len;
	char const		*tmp;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		tmp = &s[j];
		len = 0;
		while (s[j] != '\0' && s[j] != c)
		{
			len++;
			j++;
		}
		if (s[j - 1] != c)
			arr[i++] = ft_substr(tmp, 0, len);
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	num;

	if (s == NULL)
		return (NULL);
	num = word_counter(s, c);
	arr = (char **)malloc(sizeof(char *) * num);
	if (arr == NULL)
		return (NULL);
	return (sub_split(arr, s, c));
}
/*
#include <stdio.h>

int	main(void)
{
	char	*a;
	char	b;
	char	**c;
	int		i;

	a = "oooovlolov";
	b = 'o';
	c = ft_split(a, b);
	i = 0;
	while (i < 3)
		printf("%s\n", c[i++]);
	i = 0;
	while (i < 3)
		free(c[i++]);
	free(c);
	return (0);
}
*/