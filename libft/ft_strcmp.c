/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:08:47 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/29 20:13:12 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if ((s1 && !s2) || (!s1 && s2))
		return (-1);
	if (!s1 && !s2)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		n = 3;

	char	*str1 = "TERM_";
	char	*str2 = "TERM_PROG";

	printf("ft\t:\t%d\n", ft_strcmp(str1, str2));
	printf("c\t:\t%d\n", strcmp(str1, str2));
	return (0);
}
*/