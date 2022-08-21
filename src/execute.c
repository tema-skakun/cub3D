/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulagrezina <ulagrezina@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:23:57 by mmeredit          #+#    #+#             */
/*   Updated: 2022/08/21 22:02:57 by ulagrezina       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void 	set_map(t_game *game);
void	set_minimap(t_game *game);
int	close_esc(int keycode, t_game *game)
{
	(void) game;
	if (keycode == 53)
	{
		mlx_destroy_window(game->vars->mlx, game->vars->win);
		free(game->vars);
		cleaner(game);
		exit(0);
	}
	return (0);
}

int	move_all(t_game *game, double x, double y)
{
	if (x == y)
	{
		game->info->player_pos_x += y * cos(game->info->view + 30 * RADIAN);
		game->info->player_pos_y += x * sin(game->info->view + 30 * RADIAN);
	}
	else
	{
		game->info->player_pos_x += y * cos(game->info->view - 60 * RADIAN);
		game->info->player_pos_y += x * sin(game->info->view + 120 * RADIAN);
	}
	set_map(game);
	return (1);
}

int	look(t_game *game, double x)
{
	game->info->view += x*RADIAN;
	set_map(game);
	return(1);
}

int move(int keycode, t_game *game){
	close_esc(keycode, game);
	if (keycode == 13) // w
		move_all(game, 0.4, 0.4);
	else if (keycode == 0) // a
		move_all(game, -0.4, 0.4);
	else if (keycode == 1) // s
		move_all(game, -0.4, -0.4);
	else if (keycode == 2) // d
		move_all(game, 0.4, -0.4);
	else if (keycode == 123) // l
		look(game, -3);
	else if (keycode == 124) // r
		look(game, 3);
	return (0);
}

void find_pos_hero(char **map, t_info *info){
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				info->player_pos_x = j;
				info->player_pos_y = i;
				break;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int argb_to_int(int a, int r, int g, int b){
	return (a << 24 | r << 16 | g << 8 | b);
}

void	draw_floor_ceilling(t_game *game)
{
	t_img			img;
	int				i;
	int				color;
	unsigned int	*tmp;

	// printf ("x = %d y = %d\n", game->x, game->y);
	img.ptr = mlx_new_image(game->vars->mlx, game->y * 32, game->x * 32);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	tmp = (unsigned int *)img.addr;
	color = argb_to_int(0, game->f[0], game->f[1], game->f[2]);

	i = game->x * 32 / 8 * img.size_line;
	while (--i)
		*tmp++ = color;

	color = argb_to_int(0, game->c[0], game->c[1], game->c[2]);

	i = game->x * 32 / 8 * img.size_line;
	while (--i)
		*tmp++ = color;
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, img.ptr, 0, 0);
}

void	draw_country(t_game *game, double x, double y, double length, int color, int c)
{
	// char	**map;
	double		k;
	double		up;
	// double		down;
	// int		d;
	
	// map = game->map;
	// printf ("x1 = %f  y1 = %f\n", x, y);
	k = length * 32; // длина до стены
	up = game->y * 16 + k * 32;
	// down = game->x * 16;
	x += game->y * 16; // координата центра карты + координата точки по (y) или (x) для массива
	y += game->x * 16; // координата центра карты + координата точки по (x) или (y) для массива
	printf ("x = %f  y = %f k = %f\n", x, y, k);
	up = game->x * 32 - k;
	while (k < up )
	{
		
		mlx_pixel_put(game->vars->mlx, game->vars->win, c, k, color);
		k++;
		
		// x++;
	}
	// while()
}

void	set_pixel_minimap(int color, t_game *game, int i, int j)
{
	t_img			img;
	unsigned int	*tmp;
	int				k;

	k = 0;
	img.ptr = mlx_new_image(game->vars->mlx, 32, 32);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	tmp = (unsigned int *)img.addr;
	while (k++ < 32 / 4 * img.size_line)
		*tmp++ = color;	
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, img.ptr, j, i);
	mlx_destroy_image(game->vars->mlx, img.ptr);
}

void	set_minimap(t_game *game)
{
	char	**map;
	int			color;

	map = game->map;
	int i = 0;
	int j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			color = argb_to_int(0, 199, 199, 199);
			if (map[i][j] == '0' || map[i][j] != '1')
				color = argb_to_int(0, 100, 0, 230);
			else if (map[i][j] == ' ')
				color = argb_to_int(0, 210, 100, 50);
			set_pixel_minimap(color, game, (i + game->x) * 32, j * 32);
			j++;
		}
		i++;
	}
	color = argb_to_int(0, 255, 1, 1);
}

void	some_raycasting(t_game *game)
{
	double i = game->info->player_pos_y;
	double j = game->info->player_pos_x;
	int color = argb_to_int(0, 20, 255, 20);
	char	**map;
	double	pixel;
	int 	k;

	k = 0;
	map = game->map;

	// (game->y - 1) * 32 / 60 - количество лучей которые нужно отбросить. // 
	// printf ("map = %c\n", map[(int)i][(int)j]);
	pixel = 0;
	double counter = game->info->view / RADIAN;
	while (counter < game->info->view / RADIAN + 60)
	{
		while (map[(int)i][(int)j] && map[(int)i][(int)j] != '1' && i != 0)
		{
			mlx_pixel_put(game->vars->mlx, game->vars->win, j * 32, (i + game->x) * 32, color);
			i = game->info->player_pos_y + pixel * sin(RADIAN * counter);
			j = game->info->player_pos_x + pixel * cos(RADIAN * counter);
			pixel += 0.05;
		}
		draw_country(game, i, j, pixel - 0.05, color, k++);
		pixel = 0;
		i = game->info->player_pos_y;
		j = game->info->player_pos_x;
		counter += (double) 60 / ((game->y - 1) * 32);
	}
}

void 	set_map(t_game *game)
{
	draw_floor_ceilling(game);
	set_minimap(game);
	some_raycasting(game);
}

void execute(t_game *game)
{
    game->vars = malloc(sizeof(t_vars));
	game->info = malloc(sizeof(t_info));
	find_pos_hero(game->map, game->info);

	game->vars->mlx = mlx_init();
	game->vars->win = mlx_new_window(game->vars->mlx, (game->y - 1) * 32, game->x * 64, "cub3D_minimap");
	
	// pixels_init(game, game->vars);
	find_pos_hero(game->map, game->info);
	game->info->view = -120 * RADIAN;
	set_map(game);
	mlx_hook(game->vars->win, 2, 0, &move, game);
    mlx_loop(game->vars->mlx);

}