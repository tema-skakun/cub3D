/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleane.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 21:03:08 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/29 21:10:56 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	cleane(t_game *game)
{
	if (game->NO)
		free(game->NO);
	if (game->SO)
		free(game->SO);
	if (game->WE)
		free(game->WE);
	if (game->EA)
		free(game->EA);
}
