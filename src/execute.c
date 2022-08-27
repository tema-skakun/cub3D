/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:23:57 by mmeredit          #+#    #+#             */
/*   Updated: 2022/08/27 16:59:37 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	full_raycasting(t_game *game, double *i, double *j, double degree)
{
	double	dx;
	double	dy;
	double	cx;
	double	cy;
	double	delta;
	(void)	game;

	// horizontal line
	if (degree > 0 && degree < PI)
	{
		dy = ceil(*i - 1);
		dx = *j + (*i - dy) * 1/tan(degree);
	}
	else if (degree > PI)
	{
		dy = trunc(*i + 1);
		dx = *j - (dy - *i) * 1/tan(degree);
	}
	else
	{
		dy = *i;
		dx = ceil(*j + cos(degree));
		if	(cos(degree) > 0)
			dx = trunc(*j + cos(degree));
	}
	

	cx = dx;
	cy = dy;

	// vertical line
	if (degree < PI / 2 || degree > 3 * PI / 2)
	{
		dx = trunc(*j + 1);
		dy = *i - (dx - *j) * tan(degree);
	}
	else if (degree > PI / 2 || degree < 3 * PI / 2)
	{
		dx = ceil(*j - 1);
		dy = *i + (*j - dx) * tan(degree);
	}
	else
	{
		dx = *j;
		dy = trunc(*i - sin(degree));
		if (sin(degree) > 0)
			dy = ceil(*i - sin(degree));
	}
	// сравнение гипотенуз
	delta = sqrt(pow(dx - *j, 2) + pow(dy - *i, 2));
	if (delta < sqrt(pow(cx - *j, 2) + pow(cy - *i, 2)))
	{
		*i = dy;
		*j = dx;
	}
	else
	{
		*i = cy;
		*j = cx;
	}
}

void	draw_country(t_game *game, double x, double y, double length, int color, int c)
{
	double		k;
	double		up;
	(void)	y;
	(void)	x;

	k = length * 32; // длина до стены
	// up = game->y * 16 + k * 32;
	up = game->x * 32 - k;
	while (k < up)
	{
		mlx_pixel_put(game->vars->mlx, game->vars->win, c, k, color);
		k++;
		// x++;
	}
	// while()
}

// double	abs(double number)
// {
// 	if (number < 0)
// 		return (-number);
// 	return (number);
// }

void	some_raycasting(t_game *game)
{
	double i = game->info->player_pos_y;
	double j = game->info->player_pos_x;
	int color = argb_to_int(0, 20, 255, 20);
	char	**map;
	double	pixel;
	int 	k;
	double	fov1;
	double	fov2;

	fov1 = game->info->view + PI / 6;
	fov2 = game->info->view - PI / 6;
	k = 0;
	map = game->map;
	pixel = 0;
	while (fov2 <= fov1)
	{
		while (map[(int)i][(int)j] && map[(int)i][(int)j] != '1')
		{
			mlx_pixel_put(game->vars->mlx, game->vars->win, j * 32, (i + game->x) * 32, color);
			full_raycasting(game, &i, &j, from_zero_to_pi(fov1));
		}
		pixel = sqrt(pow(i - game->info->player_pos_y, 2) + pow(j - game->info->player_pos_x, 2));
		draw_country(game, i, j, pixel, color, k++);
		printf("k = %d\n", k);
		pixel = 0;
		i = game->info->player_pos_y;
		j = game->info->player_pos_x;
		fov1 -= PI / 3 / ((game->y - 1) * 32);
	}
}

void execute(t_game *game)
{
	init_info(game); // Инициализация данных
	set_map(game); // Исполнения
	mlx_hook(game->vars->win, 2, 0, &move, game);
    mlx_loop(game->vars->mlx);
}
