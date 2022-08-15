/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/15 21:09:50 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_size_map(int fd, t_game *game)
{
	char	*base;
	char	*line[2];
	int		y;

	base = "NSWEFC\n";
	while (1)
	{
		line[0] = get_next_line(fd);
		if (NULL == line[0])
			break ;
		if (!ft_strchr(base, line[0][0]))
		{
			game->x++;
			while (1)
			{
				line[1] = get_next_line(fd);
				if (NULL == line[1])
					break ;
				if (ft_strchr("\n", line[1][0]))//карта не может быть разорвана, может состоять только из " 01NSWE"
					ft_error("Error: the map contains an invalid character(s)");
				y = ft_strlen(line[1]);
				if (game->y < y)
					game->y = y;
				game->x++;
				free(line[1]);
			}
		}
		free(line[0]);
	}
}

void	check_config_file(int fd, t_game *game)
{
	char	*line;
	int		key;

	key = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		if (!ft_strncmp(line, "NO", 2))
			add_path_texture(&game->no, line, "NO \n", &key);
		if (!ft_strncmp(line, "SO", 2))
			add_path_texture(&game->so, line, "SO \n", &key);
		if (!ft_strncmp(line, "WE", 2))
			add_path_texture(&game->we, line, "WE \n", &key);
		if (!ft_strncmp(line, "EA", 2))
			add_path_texture(&game->ea, line, "EA \n", &key);
		if (!ft_strncmp(line, "F", 1))
			add_color(game->f, line, &key);
		if (!ft_strncmp(line, "C", 1))
			add_color(game->c, line, &key);
		free(line);
	}
	if (key != 6 || check_textures(game))
		ft_error("Error: invalid configuration file");
}

int	return_fd(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error: wrong path or file not exist"));
	return (fd);
}

int	check_extension(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 4)
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

int	parser(int argc, char *av, t_game *game)
{
	int	fd;

	if (argc != 2)
		return (ft_error("Error: invalid number of arguments"));
	if (check_extension(av))
		return (ft_error("Error: file must be in .cub extension"));
	fd = return_fd(av);
	check_config_file(fd, game);//проверить цвет на минус
	close(fd);
	fd = return_fd(av);
	get_size_map(fd, game);
	close(fd);
	fd = return_fd(av);
	get_map(fd, game);//положил карту в массив строк game->map
	close(fd);
	validation_check_map(game->map);
	print_game(game);
	return (0);
}
