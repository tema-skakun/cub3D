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

void	draw_country(t_game *game, double length, int c, double angle)
{
	float	k;
	double	camera_degree;
	int		d;
	int		sign;

	// (void)angle;
	sign = -1;
	camera_degree = set_camera_degree(game->info->view, &sign);
	
	// k = length * ft_abs(sin(degree + sign * ft_abs(camera_degree - game->info->view)));
	k = (float) length * fabs(cos(angle - game->info->view));
	k = fabs(1.0f / (k) * (((float)HEIGHT / (float)tan(30 * RADIAN))));// изменил HEIGHT на WIDTH / 2
	// k = (float) ceil((float) / k);
	// printf ("k = %f\n", k);
	d = ceil((float)HEIGHT / 2.0f - k / 2.0f) - 1;// что это?
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

void	some_raycasting(t_game *game, double ppy, double ppx)//сега когда смотришь за пределы карты
{
	char	**map;
	double	length;// расстояние до стены
	int		counter;// счётчик столбцов
	float	angle;// угол каждого луча

	angle = (float)game->info->view + (float) PI / 6;//по углу мы идем справой стороны
	counter = 0;//по экрану идём слевой стороны
	map = game->square_map;
	while (counter < WIDTH)//
	{
		ppy = game->info->player_pos_y;//задали координаты камере
		ppx = game->info->player_pos_x;
		// length = 0;
		while (map[(int)ppy][(int)ppx] && (map[(int)ppy][(int)ppx] != '1'))
		{
			my_pixel_put(game->img, (int)ppx + 20, (int)(ppy + game->x) + 20, argb_to_int(0, 20, 255, 20));//рисует поле зрения героя на миникарте
			full_raycasting(&ppy, &ppx, from_zero_to_2pi(angle), game);
			if (!check_hit_wall(map, ppy, ppx)) // доп проверка для попадание в стену
				break ;
		}
		my_pixel_put(game->img, (int)ppx + 20, (int)(ppy + game->x) + 20, argb_to_int(0, 20, 255, 20));//рисует поле зрения героя на миникарте
		length = (float)sqrt(pow((float)ppy - (float)game->info->player_pos_y, 2) + pow((float)ppx - (float)game->info->player_pos_x, 2));//
		// printf("dy = %f, dx = %f\n", i - game->info->player_pos_y, j - game->info->player_pos_x);
		wall_facing(ppy - game->info->player_pos_y, ppx - game->info->player_pos_x, game);//выбор цвета стены (dy, dx, h/v)
		draw_country(game, length, counter++, angle);//цвет есть в game->info
		angle -= PI / 3 / (WIDTH);
	}
	set_minimap(game);//отрисовка миникарты и поля зрения должны выполняться после отрисовки стен
}
