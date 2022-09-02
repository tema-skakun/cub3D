/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:23:57 by mmeredit          #+#    #+#             */
/*   Updated: 2022/09/02 16:58:15 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	my_mlx_pixel_put(t_img texture, int x, int y, int color)
{
	char	*dst = NULL;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)// Колина проверка, она от чего то защищает
		return ;
	dst = texture.addr + (y * texture.size_line + x * (texture.bits_per_pixel / 8));
	if (color != 0)// костыль для работы set_textures
		*(unsigned int *)dst = color;
}

void	draw_country(t_game *game, double length, int c, double degree, t_img img)
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
		d = -1;
	if (sign >= game->x * 32)
		sign = game->x * 32 - 1;
	while (d < sign)
		my_mlx_pixel_put(img, c, ++d, argb_to_int(0, 20, 255, 20));//есть мнение, что ++d работает быстрее чем d++
		// mlx_pixel_put(game->vars->mlx, game->vars->win, c, d++, argb_to_int(0, 20, 255, 20));
}

void	set_textures(t_game *game)
{
	t_img	texture;
	int		width;
	void	*no;
	int		height;
	int	i = 0;
	int	j;

	no = mlx_xpm_file_to_image(game->vars->mlx, game->no, &width, &height);
	texture.addr = mlx_get_data_addr(no, &texture.bits_per_pixel, &texture.size_line, &texture.endian);
	while (i < height)
	{
		j = -1;
		while (++j < width)
			my_mlx_pixel_put(texture, j, i, 0);
		i++;
	}
	// mlx_destroy_image(game->vars->mlx, no);
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, no, 150, 150);
}

void	some_raycasting(t_game *game, double i, double j, t_img img)//сега когда смотришь за пределы карты
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
			my_mlx_pixel_put(img, (int)j, (int)(i + game->x), argb_to_int(0, 20, 255, 20));
			// mlx_pixel_put(game->vars->mlx, game->vars->win, (int)j * 32, (int)(i + game->x) * 32, argb_to_int(0, 20, 255, 20));
			full_raycasting(&i, &j, from_zero_to_pi(fov1));
			if (!check_hit_wall(map, i, j)) // доп проверка для попадание в стену
				break ;
		}
		my_mlx_pixel_put(img, (int)j, (int)(i + game->x), argb_to_int(0, 20, 255, 20));
		// mlx_pixel_put(game->vars->mlx, game->vars->win, (int)j * 32, (int)(i + game->x) * 32, argb_to_int(0, 20, 255, 20));
		pixel = sqrt(pow(i - game->info->player_pos_y, 2) + pow(j - game->info->player_pos_x, 2));
		draw_country(game, pixel, counter++, from_zero_to_pi(fov1), img);
		fov1 -= PI / 3 / ((game->y - 1) * 32);
	}
}

void	execute(t_game *game)
{
	init_info(game); // Инициализация данных
	// set_textures(game);
	set_map(game); // Исполнения
	mlx_hook(game->vars->win, 2, 0, &move, game);
	mlx_loop_hook(game->vars->mlx, &set_map, game);
    mlx_loop(game->vars->mlx);
}
