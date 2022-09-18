/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:00:37 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/18 10:54:14 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_colors(char **digits)
{
	int		i;
	int		j;
	int		comma;

	i = 1;
	comma = 0;
	while (digits[i])
	{
		if (ft_strlen(digits[i]) < 2)//проверка отсутствия цифры цвета - "F 220, , 0"
			ft_error("Error: invalid configuration file");
		j = 0;
		while (digits[i][j])
		{
			if (ft_strchr(",", digits[i][j]))
				comma++;
			if (!ft_strchr("0123456789,\n", digits[i][j]))//они разделены недопустимым символом (не запятой) или отрицательные
				ft_error("Error: invalid configuration file");
			j++;
		}
		i++;
	}
	if (i != 4 || comma != 2)//У RGB нет трех чисел или нет двух запятых
		ft_error("Error: invalid configuration file");
}

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
	int	str;
	int	col;

	str = -1;
	while (game->square_map[++str])
	{
		col = -1;
		while (game->square_map[str][++col])
		{
			if (ft_strchr("0NSWE", game->square_map[str][col]))//когда встретил нуль или героя - действуй
				check_neigbour_char(game, str, col);
		}
	}
}

void	squaring_map(t_game *game)
{//x = кол-во строк; y = максимальное кол-во столбцов
	int	i;
	int	j;

	i = 0;
	game->square_map = (char **)ft_calloc(game->x, sizeof(char *));
	if (NULL == game->square_map)
		ft_error("Error: memory was not allocated properly");
	while (game->map[i])
	{
		game->square_map[i] = (char *)ft_calloc_8(game->y, sizeof(char));
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
			if (rgb[j] > 255 || rgb[j] < 0)//значения > 255 и < 0 - нам не подходят
				ft_error("Error: invalid configuration file");
			j++;
		}
		i++;
	}
}
