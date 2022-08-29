/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:23:57 by mmeredit          #+#    #+#             */
/*   Updated: 2022/08/29 19:15:20 by mmeredit         ###   ########.fr       */
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

double	ft_abs(double number)
{
	if (number < 0)
		return (-number);
	return (number);
}

double	from_big_degree_to_small(double degree)
{
	if (degree > PI)
		return (2 * PI - degree);
	// if (degree > PI)
	// 	return (3 * PI / 2 - degree);
	return (degree);
}

void	draw_country(t_game *game, double x, double y, double length, int color, int c, double degree)
{
	double	k;
	double	main_pi;
	int		d;

	(void)	y;
	(void)	x;
	(void)	degree;

	if (game->info->view < PI) 
		main_pi = PI / 2;
	else
		main_pi = PI;
	if (game->info->view == 0 || game->info->view == PI || game->info->view == 2 * PI) // крайние значения
	{
		k = length * sin(degree);
		if (degree > PI)
			k = length * sin(PI - degree);
		if (game->info->view == 0 || game->info->view == 2 * PI)
			k = length * sin(PI / 2 - from_big_degree_to_small(degree));
	}
	if (game->info->view <= PI / 2) // 1 часть
	{
		k = length * sin(ft_abs(from_zero_to_pi(PI - degree - ft_abs(main_pi - game->info->view))));
		if (game->info->view > degree)
			k = length * sin(ft_abs(from_zero_to_pi(degree + ft_abs(main_pi - game->info->view))));
	}
	else if (game->info->view >=3 * PI / 2) // 4 часть
	{
		k = length * sin(ft_abs(from_zero_to_pi(PI - (degree - (game->info->view - PI + PI / 2)))));
		if (game->info->view > degree)
			k = length * sin(ft_abs(from_zero_to_pi(2 * PI - degree + (game->info->view - 3 * PI / 2))));
	}
	else if (game->info->view > PI) // 3 часть
	{
		k = length * sin(ft_abs(from_zero_to_pi(PI - (degree - (game->info->view - PI + PI / 2)))));
		if (game->info->view > degree)
			k = length * sin(ft_abs(from_zero_to_pi(degree - (game->info->view - PI + PI / 2))));
	}
	else if (game->info->view > PI / 2) // 2 часть
	{
		k = length * sin(ft_abs(from_zero_to_pi(PI - (degree - ft_abs(main_pi - game->info->view)))));
		if (game->info->view > degree)
			k = length * sin(ft_abs(from_zero_to_pi(degree - ft_abs(main_pi - game->info->view))));
	}
	k = (int) game->x * 32 / k + 1;
	d = (int) game->x * 16 - k / 2;
	if (d > 0)
	{
		while (d <= game->x * 16 + k / 2)
		{
			mlx_pixel_put(game->vars->mlx, game->vars->win, c, d, color);
			d++;
			// x++;
		}
	}
	else
	{
		d = 0;
		while (d <= game->x * 32)
			mlx_pixel_put(game->vars->mlx, game->vars->win, c, d++, color);
	}
	// while()
}

int	define_side(char **map, double i, double j)
{
	if (i == (int) i)
	{
		i = i - 1;
		j = trunc(j);
	}
	else if (j == (int) j)
	{
		j = j - 1;
		i = trunc(i);
	}
	if (map[(int)i][(int)j] && map[(int)i][(int)j] == '1')
		return (0);
	return (1);
}

void	some_raycasting(t_game *game)//сега когда смотришь за пределы карты
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
	map = game->square_map;
	pixel = 0;
	while (fov2 <= fov1)
	{
		while (map[(int)i][(int)j] && (map[(int)i][(int)j] != '1'))
		{
			mlx_pixel_put(game->vars->mlx, game->vars->win, j * 32, (i + game->x) * 32, color);
			full_raycasting(game, &i, &j, from_zero_to_pi(fov1));
			if (!define_side(map, i, j)) // доп проверка для попадание в стену
				break;
		}
		mlx_pixel_put(game->vars->mlx, game->vars->win, j * 32, (i + game->x) * 32, color);
		pixel = sqrt(pow(i - game->info->player_pos_y, 2) + pow(j - game->info->player_pos_x, 2));
		draw_country(game, i, j, pixel, color, k++, from_zero_to_pi(fov1));
		// printf("k = %d\n", k);
		pixel = 0;
		i = game->info->player_pos_y;
		j = game->info->player_pos_x;
		fov1 -= PI / 3 / ((game->y - 1) * 32);
	}
}

void	execute(t_game *game)
{
	init_info(game); // Инициализация данных
	set_map(game); // Исполнения
	mlx_hook(game->vars->win, 2, 0, &move, game);
    mlx_loop(game->vars->mlx);
}
