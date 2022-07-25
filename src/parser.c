/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/25 21:47:39 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_extension(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i <= 4)
		return (1);
	while (i - 4)
	{
		str++;
		i--;
	}
	if (ft_strncmp(str, ".cub", 4))
		return (1);
	return (0);
}

int	parser(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (check_extension(argv[1]))
		return (1);
	return (0);
}
