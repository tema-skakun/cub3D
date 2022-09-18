/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:00:37 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/18 10:59:10 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_bzero_8(void *s, size_t n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)s;
	while (n--)
		ptr[i++] = '8';
	ptr[--i] = '\0';
}

void	*ft_calloc_8(size_t count, size_t size)
{
	void	*mem;

	mem = (void *)malloc(count * size);
	if (mem == NULL)
		ft_error("Error: memory was not allocated properly");
	ft_bzero_8(mem, size * count);
	return (mem);
}

void	from_file_to_map(char **map, char **file, int *i, int *j)
{
	*map = ft_substr(*file, 0, ft_strlen(*file));
	if (NULL == map)
		ft_error("Error: memory was not allocated properly");
	*j += 1;
	*i += 1;
}

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
