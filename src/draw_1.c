#include "cub3D.h"

t_img	wall_facing(float dy, float dx, t_game *game)
{
	if (dy >= 0 && game->info->wall == 1)//северная
		return (game->info->tex[0]);
	else if (dy <= 0 && game->info->wall == 1)//южная
		return (game->info->tex[1]);
	else if (dx >= 0 && game->info->wall == 2)//западная
		return (game->info->tex[2]);
	return (game->info->tex[3]); //восточн
}


void	draw_country(t_game *game, int col, t_img *img)
{
	int	k;
	float	h;//проецируемая высота среза
	int	top;//верхняя граница столбца стены
	int	down;//нижняя граница столбца стены

	h = img->length;
	k = 0;
	if (h > HEIGHT)
		k = (h - HEIGHT) * (64 / h);
	
	top = (int)ceil((float)(HEIGHT / 2.0f) - (h / 2.0f));
	down = (int)((float)(HEIGHT / 2.0f) + (h / 2.0f));
	if (top < 0)
	{
		top = 0;
		down = HEIGHT;
		// h = h - (h - HEIGHT);
	}
	img->ray_x = 64 * (img->ray_x - (int) img->ray_x);
	if (game->info->wall == 2)
		img->ray_x = 64 * (img->ray_y - (int) img->ray_y);
	while (top < down)
	{
		img->length = k * (64 / h);
		my_pixel_put(game, col, top++, img);
		k++;
	}
}

float	ray(t_game *game, float degree, int counter)
{
	float	length;
	float	x;
	float	y;
	t_img	img;

	x = game->info->player_pos_x;
	y = game->info->player_pos_y;
	while (game->square_map[(int)y][(int)x] != '1')//пока символ не стена
	{
		find_coordinate_grid(&y, &x, degree, game);//поиск стены
		if (!check_hit_wall(game->square_map, y, x)) // доп проверка для попадание в стену
			break ;
	}
	length = pythagor(game->info->player_pos_x, game->info->player_pos_y, x, y);
	if (counter != -1)
	{
		img = wall_facing(y - game->info->player_pos_y, x - game->info->player_pos_x, game);//выбор цвета стены (dy, dx, h/v)
		img.length = length * (float)cos(degree - game->info->view);
		img.length = (1.0f / img.length) * (((float)WIDTH - 1.0f) / 2.0f) / (float)tan(30.0f * (float)RADIAN);
		img.ray_x = x;
		img.ray_y = y;
		draw_country(game, counter, &img);
	}
	return (length);
}

void	raycasting(t_game *game)//, float ppy, float ppx)//сега когда смотришь за пределы карты
{
	int		counter;// счётчик столбцов
	float	step;
	float	angle_beam;// угол каждого луч
	float	tmp_angle;
	float	tmp_angle2;
	float	tmp_current;

	step = (2 * tan((float)FOV / 2.0f * RADIAN)) / (WIDTH - 1);
	
	tmp_angle = tan((float)FOV / 2.0f * RADIAN);
	tmp_angle2 = -tmp_angle;
	tmp_current = tmp_angle;
	angle_beam = game->info->view;
	counter = 0;//по экрану идём слевой стороны
	// printf ("tmp_current = %f tmp_angle = %f\n", tmp_current, tmp_angle2);
	while (tmp_current >= tmp_angle2)//пока экран не заполнен
	{	
		angle_beam = atan(tmp_current);
		ray(game, from_zero_to_2_pi(angle_beam + game->info->view), counter);//цвет есть в game->info
		counter++;
		tmp_current -= step;
	}
	set_minimap(game);//отрисовка миникарты и поля зрения должны выполняться после отрисовки стен
}
