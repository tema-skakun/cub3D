/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:43:15 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/11/06 10:50:00 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ОПИСАНИЕ
Функция strdup() возвращает указатель на новую строку, являющуюся дубликатом
строки s1. Память под новую строку выделятся с помощью malloc(3) и может быть
высвобождены с помощью free(3).

ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЯ
Функция strdup() возвращает указатель на строку-дубль или NULL, если
недостаточно памяти.
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (dup == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*str1;

	str1 = "Helkjhgoiuytlkjhgiuytlkjho";
	printf("ft	: %s\n", ft_strdup(str1));
	printf("c	: %s\n", strdup(str1));
	return (0);
}
*/