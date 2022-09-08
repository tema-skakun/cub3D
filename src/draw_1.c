#include "cub3D.h"

void	wall_facing(double dy, double dx, t_game *game)
{
	// game->info->color_wall = 0;
	if (dy >= 0 && game->info->wall == 1)//северная
		game->info->color_wall = argb_to_int(0, 20, 20, 255);//синий
	else if (dy <= 0 && game->info->wall == 1)//южная
		game->info->color_wall = argb_to_int(0, 200, 100, 50);//оранжевый
	else if (dx >= 0 && game->info->wall == 2)//западная
		game->info->color_wall = argb_to_int(0, 20, 200, 25);//зелёный
	else if (dx <= 0 && game->info->wall == 2)//восточная
		game->info->color_wall = argb_to_int(0, 200, 200, 25);//желтый
}

void	draw_country(t_game *game, double length, int c, double degree)
{
	float	k;
	double	camera_degree;
	int		d;
	int		sign;

	(void)	degree;
	sign = -1;
	camera_degree = set_camera_degree(game->info->view, &sign);
	
	// k = length * ft_abs(sin(degree + sign * ft_abs(camera_degree - game->info->view)));
	k = (float) length * fabs(cos(degree - game->info->view));
	
	k = fabs(1.0f / (k) * (((float)HEIGHT / (float)tan(30 * RADIAN))));
	// k = (float) ceil((float)HEIGHT / k);
	// printf ("k = %f\n", k);
	d = ceil((float)HEIGHT / 2.0f - k / 2.0f) - 1;
	sign = HEIGHT / 2.0f + k / 2.0f;
	if (d < 0)
		d = -1;
	if (sign >= HEIGHT)
		sign = HEIGHT - 1;
	while (++d < sign)//есть мнение, что ++d работает быстрее чем d++
	{
		if (game->info->color_wall)//если цвет есть есть
			my_pixel_put(game->img, c, d , game->info->color_wall);
		else if (!game->info->color_wall)//дефолтный зелёный
			my_pixel_put(game->img, c, d, argb_to_int(0, 20, 200, 20));
	}
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
			my_pixel_put(texture, j, i, 0);
		i++;
	}
	// mlx_destroy_image(game->vars->mlx, no);
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, no, 150, 150);
}

void	some_raycasting(t_game *game, double i, double j)//сега когда смотришь за пределы карты
{
	char	**map;
	double	length;
	int		counter;
	float	fov;

	fov = (float)game->info->view + (float) PI / 6;
	counter = 0;
	map = game->square_map;
	while (counter < WIDTH)
	{
		i = game->info->player_pos_y;//задали координаты камере или что это
		j = game->info->player_pos_x;
		// length = 0;
		while (map[(int)i][(int)j] && (map[(int)i][(int)j] != '1'))
		{
			my_pixel_put(game->img, (int)j + 20, (int)(i + game->x) + 20, argb_to_int(0, 20, 255, 20));//рисует поле зрения героя
			full_raycasting(&i, &j, from_zero_to_pi(fov), game);
			if (!check_hit_wall(map, i, j)) // доп проверка для попадание в стену
				break ;
		}
		my_pixel_put(game->img, (int)j + 20, (int)(i + game->x) + 20, argb_to_int(0, 20, 255, 20));//рисует поле зрения героя
		length = sqrt(pow((float)i - (float)game->info->player_pos_y, 2) + pow((float)j - (float)game->info->player_pos_x, 2));
		// printf("dy = %f, dx = %f\n", i - game->info->player_pos_y, j - game->info->player_pos_x);
		wall_facing(i - game->info->player_pos_y, j - game->info->player_pos_x, game);//выбор цвета стены (dy, dx, h/v)
		draw_country(game, length, counter++, fov);//цвет есть в game->info
		fov -= PI / 3 / (WIDTH - 1);
	}
	set_minimap(game);//отрисовка миникарты и поля зрения должны выполняться после отрисовки стен
}
