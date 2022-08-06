/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/06 14:37:14 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_game(t_game *game)//del
{
	int	i = 0;
	printf("no -%s\n", game->no);
	printf("so -%s\n", game->so);
	printf("we -%s\n", game->we);
	printf("ea -%s\n", game->ea);
	printf("f - r=%d,\tg=%d,\tb=%d\n", game->f[0], game->f[1], game->f[2]);
	printf("c - r=%d,\tg=%d,\tb=%d\n", game->c[0], game->c[1], game->c[2]);
	printf("x - %d\n", game->x);
	printf("y - %d\n", game->y);
	if (game->map)
	{
		while (game->map[i])
		{
			printf("%s", game->map[i]);
			i++;
		}
	}
	printf("\nparser is OK\n");
}

void	get_map(int fd, t_game *game)//x = кол-во строк; y = кол-во столбцов
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
				if (ft_strchr("\n", line[1][0]))// && check_line(line[1])))//карта не может быть разорвана, может состоять только из " 01NSWE"
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
	fd = open(av, O_RDONLY);//положить все в массив строк и работать с ним
	if (fd == -1)
		return (ft_error("Error: wrong path or file not exist"));
	check_config_file(fd, game);
	close(fd);
	fd = open(av, O_RDONLY);
	get_size_map(fd, game);
	close(fd);
	fd = open(av, O_RDONLY);
	get_map(fd, game);//положил карту в массив строк game->map
	close(fd);
	print_game(game);
	return (0);
}
