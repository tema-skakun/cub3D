/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:23:57 by mmeredit          #+#    #+#             */
/*   Updated: 2022/08/30 19:11:04 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	draw_country(t_game *game, double length, int c, double degree)
{
	double	k;
	double	camera_degree;
	int		d;
	int		sign;

	sign = -1;
	camera_degree = set_camera_degree(game->info->view, &sign);
	k = length * ft_abs(sin(from_zero_to_pi(degree + sign * ft_abs(camera_degree - game->info->view))));
	k = (int) ceil(game->x * 32 / k);
	d = (int) ceil(game->x * 16 - k / 2);
	sign = game->x * 16 + k / 2;
	if (d < 0)
		d = 0;
	if (sign >= game->x * 32)
		sign = game->x * 32 - 1;
	while (d <= sign)
		mlx_pixel_put(game->vars->mlx, game->vars->win, c, d++, argb_to_int(0, 20, 255, 20));
}

void	some_raycasting(t_game *game, double i, double j)//сега когда смотришь за пределы карты
{
	char	**map;
	double	pixel;
	int		counter;
	double	fov1;

	fov1 = game->info->view + PI / 6;
	counter = 0;
	map = game->square_map;
	while (fov1 >= game->info->view - PI / 6)
	{
		i = game->info->player_pos_y;
		j = game->info->player_pos_x;
		pixel = 0;
		while (map[(int)i][(int)j] && (map[(int)i][(int)j] != '1'))
		{
			mlx_pixel_put(game->vars->mlx, game->vars->win, j * 32, (i + game->x) * 32, argb_to_int(0, 20, 255, 20));
			full_raycasting(&i, &j, from_zero_to_pi(fov1));
			if (!check_hit_wall(map, i, j)) // доп проверка для попадание в стену
				break ;
		}
		mlx_pixel_put(game->vars->mlx, game->vars->win, j * 32, (i + game->x) * 32, argb_to_int(0, 20, 255, 20));
		pixel = sqrt(pow(i - game->info->player_pos_y, 2) + pow(j - game->info->player_pos_x, 2));
		draw_country(game, pixel, counter++, from_zero_to_pi(fov1));
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
