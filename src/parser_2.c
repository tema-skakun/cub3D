/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulagrezina <ulagrezina@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:00:37 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/21 22:47:34 by ulagrezina       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_close_map(t_game *game)
{
	(void)game;
}

void	ft_bzero_8(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
		*ptr++ = '8';
	*ptr++ = '\0';
}

void	*ft_calloc_8(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	ft_bzero_8(mem, size * count);
	return (mem);
}

void	squaring_map(t_game *game)//x = кол-во строк; y = максимальное кол-во столбцов
{
	int	i;
	int	j;

	i = 0;
	game->square_map = (char **)ft_calloc(game->x, sizeof(char *));
	if (NULL == game->square_map)
		ft_error("Error: memory was not allocated properly");
	while (game->map[i])
	{
		game->square_map[i] = (char *)ft_calloc_8(game->y - 1, sizeof(char));
		if (NULL == game->square_map[i])
			ft_error("Error: memory was not allocated properly");
		j = 0;
		while (game->map[i][j])
		{
			if (ft_strchr("01NSWE", game->map[i][j]))
				game->square_map[i][j] = game->map[i][j];
			j++;
		}
		i++;
	}
	game->square_map[i] = NULL;
	check_close_map(game);
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
			if (rgb[j] > 255 || rgb[j] < 0)
				ft_error("Error: invalid configuration file");
			j++;
		}
		i++;
	}
}

char	*return_word_and_plus_i(char *line, int *i)
{
	char	*str;

	str = ft_substr(line, 0, ft_strlen(line));
	if (NULL == str)
		ft_error("Error: memory was not allocated properly");
	*i += 1;
	return (str);
}
