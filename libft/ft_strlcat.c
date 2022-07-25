/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:43:56 by fdarkhaw          #+#    #+#             */
/*   Updated: 2021/10/19 15:23:31 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Функция strlcpy копирует из строки src в буфер dst не более чем dstsize - 1
символов и гарантированно устанавливает в конец строки нулевой символ.
strlcat делает то же самое, однако копирование ведётся не в начало dst,
а таким образом, чтобы продолжить строку, на которую указывает dst. В случае,
когда dst указывает на нуль-символ, поведение функций эквивалентно. 

strlcat возвращает суммарную длину строк по адресам src и dst. Возвращаемое
значение не зависит от того, удалось скопировать строку полностью или нет;
это позволяет легко определить что буфер назначения слишком мал для
копируемой строки.
Переполнение буфера можно проверить следующим образом:
	if (strlcat(dst, src, dstsize) >= dstsize)
		return (-1);
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	res;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	res = 0;
	i = 0;
	if (dstsize > len_dst)
		res = len_src + len_dst;
	else
		res = len_src + dstsize;
	while (src[i] && (len_dst + 1) < dstsize)
		dst[len_dst++] = src[i++];
	dst[len_dst] = '\0';
	return (res);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str1[11] = "Start";
	char	str2[] = "Stop";
	char	str3[11] = "Start";
	char	str4[] = "Stop";

	printf("ft	: %ld\n", ft_strlcat(str1, str2, 11));
	printf("str1	: %s\n", str1);
	printf("str2	: %s\n", str2);
	printf("\n");
	printf("c	: %ld\n", strlcat(str3, str4, 11));
	printf("str3	: %s\n", str3);
	printf("str4	: %s\n", str4);
	return (0);
}
*/