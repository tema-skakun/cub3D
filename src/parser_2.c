/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:00:37 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/18 01:29:44 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_close_map(t_game game)
{
	(void)game;
}

void	squaring_map(t_game *game)//x = кол-во строк; y = кол-во столбцов
{
	//идея: создать массив интов, оквадратить его и проверять карту на замкнутость
	(void)game;
	// check_close_map(game);
}

void	convert_digit(int *rgb, char **digit)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (digit[i])
	{
		if (ft_atoi(digit[i]))
		{
			rgb[j] = ft_atoi(digit[i]);
			printf("rgb = %d\n", rgb[j]);
			if (rgb[j] > 255 || rgb[j] < 0)
				ft_error("Error: invalid configuration file\n");
			j++;
		}
		i++;
	}
}

char	*return_word_and_plus_i(char *line, int *i)
{
	char	*str;

	str = ft_substr(line, 0, ft_strlen(line));
	*i += 1;
	return (str);
}
