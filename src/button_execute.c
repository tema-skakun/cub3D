/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 11:55:33 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/18 14:42:32 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	from_zero_to_2_pi(float degree)
{
	if (degree < 0.0f)
		degree += 2.0f * (float)PI;
	else if (degree >= 2.0f * (float)PI)
		degree = degree - 2.0f * (float)PI;
	return (degree);
}

void	move_all(t_game *game, float x, float y, float degree)
{
	float	move_x;
	float	move_y;

	if (x == y)// движение вперёд-назад (поправил рассчёт)
	{
		move_x = x * (float)cos(from_zero_to_2_pi(game->info->view));
		move_y = y * (float)-sin(from_zero_to_2_pi(game->info->view));
	}
	else// движение влево-вправо (поправил рассчёт)
	{
		move_x = x * (float)-cos(from_zero_to_2_pi(game->info->view \
													+ (float)PI / 2.0f));
		move_y = y * (float)sin(from_zero_to_2_pi(game->info->view \
													- (float)PI / 2.0f));
	}
	if (ray(game, -1, from_zero_to_2_pi(degree)) >= 0.2f)
	{
		game->info->player_pos_x += move_x;
		game->info->player_pos_y += move_y;
	}
}

void	look(t_game *game, float rotation)
{
	game->info->view = from_zero_to_2_pi(game->info->view + \
										rotation * (float)RADIAN);
}

int	red_cross(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	exit(0);
	return (0);
}

int	move(int keycode, t_game *game)
{
	if (keycode == 13) // w
		move_all(game, 0.2f, 0.2f, game->info->view);
	else if (keycode == 0) // a
		move_all(game, -0.2f, 0.2f, game->info->view + (float) PI / 2);
	else if (keycode == 1) // s
		move_all(game, -0.2f, -0.2f, game->info->view + (float) PI);
	else if (keycode == 2) // d
		move_all(game, 0.2f, -0.2f, game->info->view - (float) PI / 2);
	else if (keycode == 123) // l
		look(game, 2.0f);
	else if (keycode == 124) // r
		look(game, -2.0f);
	else if (keycode == 53) // esc
	{
		mlx_destroy_window(game->vars->mlx, game->vars->win);
		cleaner(game);
		exit(0);
	}
	return (0);
}
