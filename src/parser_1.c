/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:45:36 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/15 21:07:06 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_textures(t_game *game)//проверка на существование файла текстур
{
	int	file[4];
	int	ret[4];

	file[0] = open(game->no, O_RDONLY);//файл есть?
	ret[0] = read(file[0], NULL, 0);//это не папка?
	if (file[0] == -1 || ret[0] == -1)
		return (1);
	close(file[0]);
	file[1] = open(game->so, O_RDONLY);
	ret[1] = read(file[1], NULL, 0);
	if (file[1] == -1 || ret[1] == -1)
		return (1);
	close(file[1]);
	file[2] = open(game->ea, O_RDONLY);
	ret[2] = read(file[2], NULL, 0);
	if (file[2] == -1 || ret[2] == -1)
		return (1);
	close(file[2]);
	file[3] = open(game->we, O_RDONLY);
	ret[3] = read(file[3], NULL, 0);
	if (file[3] == -1 || ret[3] == -1)
		return (1);
	close(file[3]);
	return (0);
}

void	add_path_texture(char **path, char *line, char *str, int *key)
{
	*path = ft_strtrim(line, str);
	if (NULL == (*path))
		ft_error("Error: memory was not allocated properly");
	*key += 1;
}

void	add_color(int *rgb, char *line, int *key)
{
	char	**digit;

	digit = ft_split(line, ' ');
	if (NULL == digit)
		ft_error("Error: memory was not allocated properly");
	convert_digit(rgb, digit);
	free_point_str(digit);
	*key += 1;
}

void	validation_check_map(char **map)
{
	int	i;
	int	j;
	int	hero;

	hero = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
				hero++;
			if (!ft_strchr("NSWE10 \n", map[i][j]))
				ft_error("Error: the map contains an invalid character(s)");
			j++;
		}
		i++;
	}
	if (hero != 1)
		ft_error("Error: too many heroes");
	// squaring_map(game);
}

void	get_map(int fd, t_game *game)
{
	char	*base;
	char	*line[2];
	int		i;

	base = "NSWEFC\n";
	i = 0;
	game->map = (char **)ft_calloc(game->x + 1, sizeof(char *));
	while (1)
	{
		line[0] = get_next_line(fd);
		if (NULL == line[0])
			break ;
		if (!ft_strchr(base, line[0][0]))
		{
			game->map[i] = ft_substr(line[0], 0, ft_strlen(line[0]));
			i++;
			while (1)
			{
				line[1] = get_next_line(fd);
				if (NULL == line[1])
					break ;
				game->map[i] = ft_substr(line[1], 0, ft_strlen(line[1]));
				free(line[1]);
				i++;
			}
		}
		free(line[0]);
	}
}
