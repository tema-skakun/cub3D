/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulagrezina <ulagrezina@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:00:37 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/22 22:45:05 by ulagrezina       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_neigbour_char(t_game *game, int str, int col)
{
	if (str == 0 || col == 0 || str == (game->x - 2) || col == (game->y - 2))
			ft_error("Error: Map is not close");//границы карты не должны содержать 0
	else if (ft_strchr("8", game->square_map[str - 1][col]))//check up
		ft_error("Error: Map is not close");
	else if (ft_strchr("8", game->square_map[str][col - 1]))//check left
		ft_error("Error: Map is not close");
	else if (ft_strchr("8", game->square_map[str + 1][col]))//check down
		ft_error("Error: Map is not close");
	else if (ft_strchr("8", game->square_map[str][col + 1]))//check right
		ft_error("Error: Map is not close");
}

void	check_close_map(t_game *game)
{
	int	str = -1;
	int	col;
	(void)game;
	while (game->square_map[++str])
	{
		col = -1;
		while (game->square_map[str][++col])
		{
			if (ft_strchr("0NSWE", game->square_map[str][col]))//когда встретил ноль или героя - действуй
				check_neigbour_char(game, str, col);
		}
	}
}

void	ft_bzero_8(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
		*ptr++ = '8';
	*ptr = '\0';
}

// void	ft_bzero_8(void *s, size_t n)
// {
// 	char	*ptr;
// 	int		i = 0;

// 	ptr = (char *)s;
// 	while (n--)
// 		ptr[i++] = '8';
// 	ptr[i] = '\0';
// 	printf("ft_8 i = %d\n", i);
// }

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
