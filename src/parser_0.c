/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulagrezina <ulagrezina@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/22 21:39:48 by ulagrezina       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_map(t_game *game)
{
	int	i;//счётчик по map
	int	j;//счётчик по file

	i = 0;
	j = 0;
	game->map = (char **)ft_calloc(game->x + 1, sizeof(char *));
	if (NULL == game->map)
		ft_error("Error: memory was not allocated properly");
	while (game->file[j])
	{
		if (!ft_strchr("NSWEFC\n", game->file[j][0]))
		{
			while (game->file[j])
			{
				game->map[i] =  ft_substr(game->file[j], 0, ft_strlen(game->file[j]));
				if (NULL == game->map[i])
					ft_error("Error: memory was not allocated properly");
				j++;
				i++;
			}
		}
		j++;
	}
	game->map[++i] = NULL;
}

void	get_size_map(t_game *game)
{
	int		i;

	i = 0;
	while (game->file[i])
	{
		if (!ft_strchr("NSWEFC\n", game->file[i][0]))//пролистал файл конфигурации
		{
			game->x++;
			while (game->file[i])
			{
				game->len = ft_strlen(game->file[i]);
				if (game->y < game->len)
					game->y = game->len;
				game->x++;
				i++;
			}
		}
		i++;
	}
}

// void	get_size_file(char *av, t_game *game)
// {
// 	char	*line;
// 	int		fd;

// 	fd = return_fd(av);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (NULL == line)
// 			break ;
// 		game->num_str++;
// 		free(line);
// 	}
// 	close(fd);
// }

void	get_file(char *av, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	// printf("1 = %d\n", fd);
	// close(fd);//почему здесь нельзя закрыть fd?
	// printf("2 = %d\n", fd);
	if (fd == -1)
		ft_error("Error: wrong path or file not exist");
	i = -1;
	game->file = (char **)ft_calloc(3000, sizeof(char *));
	if (NULL == game->file)
		ft_error("Error: memory was not allocated properly");
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		game->file[i] = return_word_and_plus_i(line, &i);
		free(line);
	}
	close(fd);
	game->file[++i] = NULL;
	if (line)
		free(line);
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
	if (argc != 2)
		return (ft_error("Error: invalid number of arguments"));
	if (check_extension(av))
		return (ft_error("Error: file must be in .cub extension"));
	// get_size_file(av, game);
	get_file(av, game);
	get_size_map(game);
	get_map(game);
	validation_check_map(game);
	print_game(game);
	return (0);
}
