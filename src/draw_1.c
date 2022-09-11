#include "cub3D.h"

void	wall_facing(float dy, float dx, t_game *game)
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

float	ray(t_game *game, float degree)
{
	float	length;
	float	x;
	float	y;

	x = game->info->player_pos_x;
	y = game->info->player_pos_y;
	while (game->square_map[(int)y][(int)x] != '1')//пока символ не стена
	{
		// my_pixel_put(game->img, (int)ppx + 20, (int)(ppy + game->x) + 20, argb_to_int(0, 20, 255, 20));//рисует поле зрения героя на миникарте
		find_coordinate_grid(&y, &x, from_zero_to_2_pi(degree), game);//поиск стены
		if (!check_hit_wall(game->square_map, y, x)) // доп проверка для попадание в стену
			break ;
	}
	wall_facing(y - game->info->player_pos_y, x - game->info->player_pos_x, game);//выбор цвета стены (dy, dx, h/v)
	length = pythagor(game->info->player_pos_x, game->info->player_pos_y, x, y);
	return (length);
}

//ceil - возвращает наименьшее целое, которое не меньше arg. (float)ceil(2.7) = 3; (float)ceil(-2.7) = -2
//trunk - Вычисляет ближайшее целое число, не большее по величине arg. trunk(2.7) = 2.0; trunk(-2.7) = -2.0

void	draw_country(t_game *game, float length, int col, float angle_beam)
{
	float	k;
	float	h;//проецируемая высота среза
	float	top;//верхняя граница столбца стены
	float	down;//нижняя граница столбца стены

	k = (length * (float)cos(angle_beam - game->info->view));
	// printf("angle_beam[%d] = %f\n", col, angle_beam);
	h = (1.0f / k) * ((float)WIDTH / 2.0f) / (float)tan(30.0f * (float)RADIAN);
	top = (float)ceil((float)(HEIGHT / 2.0f) - (h / 2.0f));
	down = (float)((float)(HEIGHT / 2.0f) + (h / 2.0f));
	if (top < 0.0f)
		top = 0.0f;
	if (down > (float)HEIGHT)
		down = (float)HEIGHT;
	while (top < down)
	{
		my_pixel_put(game->img, col, top, game->info->color_wall);
		top++;
	}
}

// void	draw_country(t_game *game, float length, int c, float angle_beam)
// {
// 	float	k;
// 	float	d;// что это?
// 	int		sign;

// 	k = (float) length * fabs(cos(angle_beam - game->info->view));
// 	k = fabs(1.0f / (k) * (((float)HEIGHT / (float)tan(30 * RADIAN))));
// 	d = (float)ceil((float)HEIGHT / 2.0f - k / 2.0f) - 1;
// 	sign = HEIGHT / 2.0f + k / 2.0f;
// 	if (d < 0)
// 		d = -1;
// 	if (sign >= HEIGHT)
// 		sign = HEIGHT - 1;
// 	while (++d < sign)
// 		my_pixel_put(game->img, c, d , game->info->color_wall);
// }

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

void	raycasting(t_game *game)//, float ppy, float ppx)//сега когда смотришь за пределы карты
{
	// float	length;// расстояние до стены
	int		counter;// счётчик столбцов
	float	angle_beam;// угол каждого луч
	// float	beam_coor_y;
	// float	beam_coor_x;

	angle_beam = game->info->view + (float)PI / 6.0f;//по углу мы идем справой стороны
	counter = 0;//по экрану идём слевой стороны
	while (counter < WIDTH)//пока экран не заполнен
	{
		
		// beam_coor_y = game->info->player_pos_y;//начальная координата каждого луч
		// beam_coor_x = game->info->player_pos_x;//начальная координата каждого луч
		// while (game->square_map[(int)beam_coor_y][(int)beam_coor_x] != '1')//пока символ не стена
		// {
		// 	// my_pixel_put(game->img, (int)ppx + 20, (int)(ppy + game->x) + 20, argb_to_int(0, 20, 255, 20));//рисует поле зрения героя на миникарте
		// 	find_coordinate_grid(&beam_coor_y, &beam_coor_x, from_zero_to_2_pi(angle_beam), game);//поиск стены
		// 	if (!check_hit_wall(game->square_map, beam_coor_y, beam_coor_x)) // доп проверка для попадание в стену
		// 		break ;
		// }
		// my_pixel_put(game->img, (int)ppx + 20, (int)(ppy + game->x) + 20, argb_to_int(0, 20, 255, 20));//рисует поле зрения героя на миникарте		
		draw_country(game, ray(game, from_zero_to_2_pi(angle_beam)) , counter, angle_beam);//цвет есть в game->info
		counter++;
		angle_beam -= (PI / 3.0f) / ((float)WIDTH - 1);
	}
	set_minimap(game);//отрисовка миникарты и поля зрения должны выполняться после отрисовки стен
}
