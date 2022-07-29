/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/29 23:10:42 by fdarkhaw         ###   ########.fr       */
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

// void	get_size_map(int fd, t_game *game)
// {
// 	// char	*line;
	
// 	// while (1)
// 	// {
// 	// 	line = get_next_line(fd);
		
// 	// }
	
// 	(void)fd;
// 	(void)game;
// }

int	check_textures(t_game *game)//проверка на существование файла текстур
{
	int	file[4];
	int	ret[4];

	file[0] = open(game->NO, O_RDONLY);//файл есть
	ret[0] = read(file[0], NULL, 0);//это не папка
	if (file[0] == -1 || ret[0] == -1)
		return (1);
	close(file[0]);
	file[1] = open(game->SO, O_RDONLY);
	ret[1] = read(file[1], NULL, 0);
	if (file[1] == -1 || ret[1] == -1)
		return (1);
	close(file[1]);
	file[2] = open(game->EA, O_RDONLY);
	ret[2] = read(file[2], NULL, 0);
	if (file[2] == -1 || ret[2] == -1)
		return (1);
	close(file[2]);
	file[3] = open(game->WE, O_RDONLY);
	ret[3] = read(file[3], NULL, 0);
	if (file[3] == -1 || ret[3] == -1)
		return (1);
	close(file[3]);
	return(0);
}

void	check_config_file(int fd, t_game *game)
{
	char	*line;
	int		key = 0;//в конце д.б. равен 4
	
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		if (!ft_strncmp(line, "NO ", 3) && !game->NO)
		{
			game->NO = ft_strtrim(line, "NO ");
			key++;
		}
		if (!ft_strncmp(line, "SO ", 3) && !game->SO)
		{
			game->SO = ft_strtrim(line, "SO ");
			key++;
		}
		if (!ft_strncmp(line, "WE ", 3) && !game->WE)
		{
			game->WE = ft_strtrim(line, "WE ");
			key++;
		}
		if (!ft_strncmp(line, "EA ", 3) && !game->EA)
		{
			game->EA = ft_strtrim(line, "EA ");
			key++;
		}
		free(line);
	}
	close(fd);
	if (key != 4 || check_textures(game))
		ft_error("Error: invalid configuration file");
	printf("key = %d\n", key);//
	printf("%s\n", game->NO);//
	printf("%s\n", game->SO);//
	printf("%s\n", game->WE);//
	printf("%s\n", game->EA);//
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
	// get_size_map(fd, game);
	printf("parser is OK\n");
	close(fd);
	return (0);
}
