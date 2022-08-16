/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/16 23:34:25 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	return_fd(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_error("Error: wrong path or file not exist"));
	return (fd);
}

void	get_size_map(t_game *game, char *base)
{
	int		i;

	i = 0;
	while (game->file[i])
	{
		if (!ft_strchr(base, game->file[i][0]))//пролистал файл конфигурации
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

	fd = return_fd(av);
	i = -1;
	game->file = (char **)ft_calloc(3000, sizeof(char *));
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		game->file[i] = return_word_and_plus_i(line, &i);
		free(line);
	}
	if (line)
		free(line);
	game->file[++i] = NULL;
	close(fd);
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
	char	*base;

	base = "NSWEFC\n";
	if (argc != 2)
		return (ft_error("Error: invalid number of arguments"));
	if (check_extension(av))
		return (ft_error("Error: file must be in .cub extension"));
	// get_size_file(av, game);
	get_file(av, game);
	get_size_map(game, base);
	get_map(game, base);
	validation_check_map(game);
	print_game(game);
	return (0);
}
