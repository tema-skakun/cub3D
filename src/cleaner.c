/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:03:08 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/30 18:41:19 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_point_str(char **p_str)
{
	int	i;

	i = 0;
	if (p_str != NULL)
	{
		while (p_str[i])
			free(p_str[i++]);
		free(p_str);
	}
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
	// if (game->f)
	// 	free(game->f);
	// if (game->f)
	// 	free(game->c);
}
