/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:38:29 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/11/06 10:51:04 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Параметры
#1. Строка, по которой нужно выполнить итерацию.
#2. Функция, применяемая к каждому символу.

Возвращаемое значение
Строка, созданная из последовательных применений
’f’. Возвращает значение NULL, если выделение завершается неудачно.

Описание
Применяет функцию "f" к каждому символу
строки "s" и передает ее индекс в качестве первого
аргумента для создания новой строки (с помощью malloc(3))
в результате последовательного применения "f".
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

char	f(unsigned int i, char c)
{
	char	str;

	str = c + i;
	return (str);
}

int	main(void)
{
	char	*str1;
	char	*str2;

	str1 = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
	str2 = ft_strmapi(str1, *f);
	printf("%s\n", str2);
	return (0);
}
*/