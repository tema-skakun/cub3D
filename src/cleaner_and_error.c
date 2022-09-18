/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_and_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:03:08 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/18 14:41:29 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	free_point_str(char **p_str)
{
	int	i;

	i = 0;
	while (p_str[i])
		free(p_str[i++]);
	free(p_str);
}

void	cleaner(t_game *game)
{
	if (game->no)
		free(game->no);
	if (game->so)
		free(game->so);
	if (game->we)
		free(game->we);
	if (game->ea)
		free(game->ea);
	if (game->info)
		free(game->info);
	if (game->vars)
		free(game->vars);
	if (game->map)
		free_point_str(game->map);
	if (game->file)
		free_point_str(game->file);
	if (game->square_map)
		free_point_str(game->square_map);
}
