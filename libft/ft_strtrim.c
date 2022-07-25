/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:17:47 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/25 18:20:41 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
#1. Строка, которую нужно обрезать.
#2. Эталонный набор символов для обрезки.

Возвращаемое значение
Обрезанная строка. Значение NULL, если выделение завершится неудачно.

Описание
Выделяет (с помощью malloc(3)) и возвращает копию ’s1’ с удаленными
из начала и конца строки символами, указанными в ’set’.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	ptr = ft_substr(s1, 0, len + 1);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*a;
	char	*b;

	a = "ovlolvo";
	b = "ov";
	printf("%s\n", ft_strtrim(a, b));
	return (0);
}
*/