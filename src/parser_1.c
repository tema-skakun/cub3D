/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:45:36 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/16 23:39:14 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_config_file(t_game *game)
{
	int	key;
	int	i;

	key = 0;
	i = 0;
	while (game->file[i])
	{
		if (!ft_strncmp(game->file[i], "NO", 2))
			add_path_texture(&game->no, game->file[i], "NO \n", &key);
		if (!ft_strncmp(game->file[i], "SO", 2))
			add_path_texture(&game->so, game->file[i], "SO \n", &key);
		if (!ft_strncmp(game->file[i], "WE", 2))
			add_path_texture(&game->we, game->file[i], "WE \n", &key);
		if (!ft_strncmp(game->file[i], "EA", 2))
			add_path_texture(&game->ea, game->file[i], "EA \n", &key);
		if (!ft_strncmp(game->file[i], "F", 1))
			add_color(game->f, game->file[i], &key);
		if (!ft_strncmp(game->file[i], "C", 1))
			add_color(game->c, game->file[i], &key);
		i++;
	}
	if (key != 6 || check_textures(game))
		ft_error("Error: invalid configuration file");
}

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

void	validation_check_map(t_game *game)
{
	int	i;
	int	j;
	int	hero;

	check_config_file(game);//проверить цвет на минус
	hero = 0;
	i = 0;
	while (game->map[i])
	{
		if (ft_strchr("\n", game->map[i][0]))//карта не может быть разорвана, может состоять только из " 01NSWE"
			ft_error("Error: the map contains an invalid character(s)");
		j = 0;
		while (game->map[i][j])
		{
			if (ft_strchr("NSWE", game->map[i][j]))
				hero++;
			if (!ft_strchr("NSWE10 \n", game->map[i][j]))
				ft_error("Error: the map contains an invalid character(s)");
			j++;
		}
		i++;
	}
	if (hero != 1)
		ft_error("Error: too many heroes");
	// squaring_map(game);
}

void	get_map(t_game *game, char *base)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	game->map = (char **)ft_calloc(game->x + 1, sizeof(char *));
	while (game->file[j])
	{
		if (!ft_strchr(base, game->file[j][0]))
		{
			game->map[i] = return_word_and_plus_i(game->file[j], &i);
			while (game->file[j])
			{
				game->map[i] = return_word_and_plus_i(game->file[j], &i);
				j++;
			}
		}
		j++;
	}
	game->map[++i] = NULL;
}
