/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:15:49 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/17 20:07:33 by mmeredit         ###   ########.fr       */
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
				from_file_to_map(&game->map[i], &game->file[j], &i, &j);
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

void	get_size_file(char *av, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		ft_error("Error: wrong path or file not exist");
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		game->num_str++;
		free(line);
	}
	game->num_str++;//место под NULL
	if (line)
		free(line);
	close(fd);
}

void	get_file(char *av, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		ft_error("Error: wrong path or file not exist");
	i = -1;
	game->file = (char **)ft_calloc(game->num_str + 1, sizeof(char *));
	if (NULL == game->file)
		ft_error("Error: memory was not allocated properly");
	while (1)
	{
		line = get_next_line(fd);
		if (NULL == line)
			break ;
		game->file[++i] = ft_substr(line, 0, ft_strlen(line));
		free(line);
		if (NULL == game->file[i])
			ft_error("Error: memory was not allocated properly");
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

void	parser(int argc, char *av, t_game *game)
{
	if (argc != 2)
		ft_error("Error: invalid number of arguments");
	if (check_extension(av))
		ft_error("Error: file must be in .cub extension");
	get_size_file(av, game);
	get_file(av, game);
	get_size_map(game);
	get_map(game);
	validation_check_map(game);
}
