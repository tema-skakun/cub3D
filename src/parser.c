/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/30 23:01:07 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	get_next_line(char **line)
// {
// 	int rd = 0;
// 	int i = 0;
// 	char ch;

// 	char *buffer = malloc(100000);
// 	*line = buffer;
// 	while ((rd = read(0, &ch, 1)) > 0 && ch != '\n')
// 	buffer[i++] = ch;
// 	buffer[i] = '\0';
// 	return (rd);
// }

void	get_size_map(int fd, t_game *game)//карта не может быть разорвана переносами каретки, добавить эту проверку
{
	char	*base;
	char	*line;
	int		y;
	int		x;

	base = "NSWEFC";
	x = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		if (!ft_strchr(base, line[0]))
		{
			y = ft_strlen(line);
			if (game->y < y)
				game->y = y;
			x++;
		}
		free(line);
	}
	game->x = x;
	printf("x - %d\n", game->x);
	printf("y - %d\n", game->y);
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
			j++;
		}
		i++;
	}
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

void	check_config_file(int fd, t_game *game)
{
	char	*line;
	int		key;//в конце д.б. равен 6 - все ключи переданы корректно

	key = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		if (!ft_strncmp(line, "NO", 2))
			add_path_texture(&game->no, line, "NO ", &key);
		if (!ft_strncmp(line, "SO", 2))
			add_path_texture(&game->so, line, "SO ", &key);
		if (!ft_strncmp(line, "WE", 2))
			add_path_texture(&game->we, line, "WE ", &key);
		if (!ft_strncmp(line, "EA", 2))
			add_path_texture(&game->ea, line, "EA ", &key);
		if (!ft_strncmp(line, "F", 1))
			add_color(game->f, line, &key);
		if (!ft_strncmp(line, "C", 1))
			add_color(game->c, line, &key);
		free(line);
	}
	if (key != 6 || check_textures(game))
		ft_error("Error: invalid configuration file");
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
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error: wrong path or file not exist"));
	check_config_file(fd, game);
	close(fd);
	fd = open(av, O_RDONLY);
	get_size_map(fd, game);//нужно положить карту в связный список(?) 
	close(fd);
	printf("parser is OK\n");//
	return (0);
}


/*
	printf("no -%s\n", game->no);//
	printf("so -%s\n", game->so);//
	printf("we -%s\n", game->we);//
	printf("ea -%s\n", game->ea);//
	printf("f -%d, %d, %d\n", game->f[0], game->f[1], game->f[2]);//
	printf("c -%d, %d, %d\n", game->c[0], game->c[1], game->c[2]);//
*/