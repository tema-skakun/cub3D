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

// void	pixels_init(t_game *game, t_vars *vars){
// 	void    *floor;
//     void    *wall;
//     void    *start;
// 	char	**map;
// 	int		i;
// 	int		j;
// 	int	width;
// 	int hight;

// 	width = 32;
// 	hight = 32;
// 	i = 0;
// 	j = 0;
// 	map = game->map;
// 	floor = mlx_xpm_file_to_image(vars->mlx, "/Users/mmeredit/Desktop/cubas/Textures/floor.xpm", &width, &hight);
// 	wall = mlx_xpm_file_to_image(vars->mlx, "/Users/mmeredit/Desktop/cubas/Textures/wall.xpm", &width, &hight);
// 	start = mlx_xpm_file_to_image(vars->mlx, "/Users/mmeredit/Desktop/cubas/Textures/dot.xpm", &width, &hight); 

// 	while (map[i])
// 	{
// 		while (map[i][j] && map[i][j] != '\n')
// 		{
// 			if (map[i][j] == '1')
// 			{
// 				mlx_put_image_to_window(vars->mlx, vars->win, wall, j * 64, i * 64);
// 			}
// 			else if (map[i][j] == '0')
// 			{
// 				mlx_put_image_to_window(vars->mlx, vars->win, floor, j * 64, i * 64);
// 			}
// 			else if (map[i][j] == 'N')
// 			{
// 				mlx_put_image_to_window(vars->mlx, vars->win, floor, j * 64, i * 64);
// 				// mlx_put_image_to_window(vars->mlx, vars->win, start, j * 64, i * 64);
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// }

int	move_all(t_game *game, double x, double y)
{
	game->info->player_pos_x += x * 32;
	game->info->player_pos_y += y * 32;
	set_map(game);
	return (1);
}

int move(int keycode, t_game *game){
	// printf("I AM MOVE! keycode = %d\n", keycode);
	close_esc(keycode, game);
	if (keycode == 13)
		move_all(game, 0, -0.5);
	else if (keycode == 0)
		move_all(game, -0.5, 0);
	else if (keycode == 1)
		move_all(game, 0, 0.5);
	else if (keycode == 2)
		move_all(game, 0.5, 0);
	// if (!game->game_over)
	// {
	// 	mlx_clear_window(game->libx->mlx, game->libx->win);
	// 	last_img(game, 0, 0);
	// }
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
	info->player_pos_x *= 32;
	info->player_pos_y *= 32;
}

int argb_to_int(int a, int r, int g, int b){
	return (a << 24 | r << 16 | g << 8 | b);
}

// void set_map(t_game *game){
// 	int i = 0;
// 	int j = 0;
// 	char	**map = game->map;
// 	while (map[i])
// 	{
// 		while (map[i][j])
// 		{
// 			mlx_pixel_put(game->vars->mlx, game->vars->win, j * 64, i * 64, 0x808080);
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// }

void	draw_floor_ceilling(t_game *game)
{
	t_img			img;
	int				i;
	int				color;
	unsigned int	*tmp;

	printf ("x = %d y = %d\n", game->x, game->y);
	img.ptr = mlx_new_image(game->vars->mlx, game->y * 64, game->x * 64);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	tmp = (unsigned int *)img.addr;
	color = argb_to_int(0, game->f[0], game->f[1], game->f[2]);

	i = game->x * 64 / 8 * img.size_line;
	while (--i)
		*tmp++ = color;

	color = argb_to_int(0, game->c[0], game->c[1], game->c[2]);

	i = game->x * 64 / 8 * img.size_line;
	while (--i)
		*tmp++ = color;
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, img.ptr, 0, 0);
}

void	draw_country(t_game *game, int x, int y)
{
	t_img			img;
	int				i;
	int				color;
	unsigned int	*tmp;

	img.ptr = mlx_new_image(game->vars->mlx, 1, game->y * 32);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	tmp = (unsigned int *)img.addr;
	color = argb_to_int(0, 199, 199, 199);

	i = game->y * 32;
	while (--i)
		*tmp++ = color;
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, img.ptr, x * 64, (game->x - y) * 64);
}

void	set_country(t_game *game)
{
	int		i;
	int		j;
	char	**map;

	map = game->map;
	i = game->info->player_pos_x;
	j = game->info->player_pos_y;

	while(map[j][i] != '1')
	{
		i--;
	}
	draw_country(game, i, j);
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
			set_pixel_minimap(color, game, i * 32, j * 32);
			j++;
		}
		i++;
	}
	color = argb_to_int(0, 255, 1, 1);
	set_pixel_minimap(color, game, game->info->player_pos_y, game->info->player_pos_x);
}

void	some_raycasting(t_game *game)
{
	double i = game->info->player_pos_y / 32;
	double j = game->info->player_pos_x / 32;
	int color = argb_to_int(0, 20, 255, 20);
	char	**map;
	double	pixel;

	map = game->map;
	t_img			img;
	unsigned int	*tmp;
	int				k;

	k = 0;
	img.ptr = mlx_new_image(game->vars->mlx, 4, 4);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	tmp = (unsigned int *)img.addr;
	while (k++ < img.size_line)
		*tmp++ = color;
	printf ("x = %f  y = %f\n", i, j);

	printf ("map = %c\n", map[(int)i][(int)j]);
	pixel = 0;
	int counter = -120;
	while (counter != -59)
	{
		while (map[(int)i][(int)j] != '1' && i != 0)
		{
			mlx_pixel_put(game->vars->mlx, game->vars->win, j * 32, i * 32, color);
			// mlx_put_image_to_window(game->vars->mlx, game->vars->win, img.ptr, j * 32, i * 32);
			i = game->info->player_pos_y / 32 + pixel * sin(RADIAN * counter);
			j = game->info->player_pos_x / 32 + pixel * cos(RADIAN * counter);
			pixel += 0.05;
			printf ("x = %f  y = %f\n", i, j);
		}
		printf ("pixel = %f\n", pixel);
		pixel = 0;
		i = game->info->player_pos_y / 32;
		j = game->info->player_pos_x / 32;
		counter += 1;
	}
	// pixel = ++i;
	// while (pixel * 32 < game->info->player_pos_y)
	// {
	// 	// printf ("i = %d  pos = %f\n", i, game->info->player_pos_y);
	// 	mlx_pixel_put(game->vars->mlx, game->vars->win, game->info->player_pos_x + pixel * cos(60), pixel * 32, color);
	// 	pixel += 0.05;
	// }
}

void 	set_map(t_game *game)
{
	// draw_floor_ceilling(game);
	// set_country(game);
	set_minimap(game);
	some_raycasting(game);
}

void execute(t_game *game)
{
    game->vars = malloc(sizeof(t_vars));
	game->info = malloc(sizeof(t_info));
	find_pos_hero(game->map, game->info);

	game->vars->mlx = mlx_init();
	game->vars->win = mlx_new_window(game->vars->mlx, (game->y - 1) * 32, game->x * 32, "cub3D_minimap");
	
	// pixels_init(game, game->vars);
	find_pos_hero(game->map, game->info);
	set_map(game);
	mlx_hook(game->vars->win, 2, 0, &move, game);
    mlx_loop(game->vars->mlx);

	// int 	i = 0;
	// char	**map = game->map;
    // printf("MYMAP\n");
    // while (map[i]){
    //     printf ("%s", map[i]);
    //     i++;
    // }
    // i = 0;

}