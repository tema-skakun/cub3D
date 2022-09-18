/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:33:42 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/18 14:19:33 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		k;
	float	h;//проецируемая высота среза
	int		top;//верхняя граница столбца стены
	int		down;//нижняя граница столбца стены

	h = img->length;
	k = 0;
	top = (int)ceil((float)(HEIGHT / 2.0f) - (h / 2.0f));
	down = (int)((float)(HEIGHT / 2.0f) + (h / 2.0f));
	if (top < 0)
	{
		top = 0;
		down = HEIGHT;
		k = (h - HEIGHT) / 2;
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

// void	prepar_for_draw(t_img *img, float y, float x, t_game *game)
// {
// 	float	length;

// 	length = pythagor(game->info->player_pos_x, game->info->player_pos_y, x, y);
// 	*img = wall_facing(y - game->info->player_pos_y, \
// 											x - game->info->player_pos_x, game);//выбор текстуры
// 	(*img).length = length * (float)cos(game->angle - game->info->view);
// 	(*img).length = (1.0f / (*img).length) * (((float)WIDTH - 1.0f) \
// 									/ 2.0f) / (float)tan(30.0f * (float)RADIAN);
// 	(*img).ray_x = x;
// 	(*img).ray_y = y;
// }

float	ray(t_game *game, int counter, float ang)
{
	float	length;
	float	x;
	float	y;
	t_img	img;

	x = game->info->player_pos_x;
	y = game->info->player_pos_y;
	while (game->square_map[(int)y][(int)x] != '1')//пока символ не стена
	{
		find_coordinate_grid(&y, &x, ang, game);//поиск стены
		if (!check_hit_wall(game->square_map, y, x))// доп проверка для попадание в стену
			break ;
	}
	length = pythagor(game->info->player_pos_x, game->info->player_pos_y, x, y);
	if (counter != -1) // вынести в функцию
	{
		// prepar_for_draw(&img, y, x, game);//вынес, но похоже не то что надо было)))

		img = wall_facing(y - game->info->player_pos_y, \
												x - game->info->player_pos_x, game);//выбор текстуры
		img.length = length * (float)cos(ang - game->info->view);
		img.length = (1.0f / img.length * (((float)WIDTH - 1.0f) / 2.0f) / (float)tan(30.0f * (float)RADIAN));
		img.ray_x = x;
		img.ray_y = y;
		draw_country(game, counter, &img);
	}
	return (length);
}

void	raycasting(t_game *game)//больше не зависает при повороте направо до 0
{
	int		count_col;
	float	step;
	float	angle_beam;
	float	tmp_angle[2];
	float	tmp_current;

	step = (2 * tan((float)FOV / 2.0f * RADIAN)) / (WIDTH);
	tmp_angle[0] = tan((float)FOV / 2.0f * RADIAN);
	tmp_angle[1] = -tmp_angle[0];
	tmp_current = tmp_angle[0];
	// angle_beam = game->info->view;//кажется лишнее присвоение
	count_col = 0;//по экрану идём слевой стороны
	while (tmp_current >= tmp_angle[1])//пока экран не заполнен
	{	
		angle_beam = atan(tmp_current);
		// game->angle = from_zero_to_2_pi(angle_beam + game->info->view);
		ray(game, count_col, from_zero_to_2_pi(angle_beam + game->info->view));
		count_col++;
		tmp_current -= step;
	}
}
