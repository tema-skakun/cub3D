/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 12:01:03 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/18 12:12:46 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_pixel_put(t_game *game, int x, int y, t_img *img)
{
	char			*dst;
	unsigned int	*pixels;

	if (img != NULL)
	{
		dst = game->img.addr + (y * game->img.size_line + x * \
											(game->img.bits_per_pixel / 8));
		pixels = (unsigned int *) mlx_get_data_addr(img->ptr, \
						&img->bits_per_pixel, &img->size_line, &img->endian);
		*(unsigned int *)dst = (unsigned int) pixels[(int)((int)img->length \
									* img->size_line / 4 + (int)img->ray_x)];
	}
}

int	argb_to_int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	draw_all(t_game *game)
{
	int				i;
	int				color;
	unsigned int	*tmp;

	tmp = (unsigned int *)game->img.addr;
	color = argb_to_int(0, game->c[0], game->c[1], game->c[2]);//потолок - c
	i = HEIGHT / 8 * game->img.size_line + 1;
	while (--i)
		*tmp++ = color;
	color = argb_to_int(0, game->f[0], game->f[1], game->f[2]);//пол - f
	i = HEIGHT / 8 * game->img.size_line + 1;
	while (--i)
		*tmp++ = color;
	raycasting(game);//рисую стены там же, где нарисован пол и потолок
}

/* отрисовка миникарты - WIP
static void	set_pixel_minimap(t_game *game, int j, int i, int *multiplier)
{
	int	str;
	int	col;

	str = 0;
	while (str <= SCALE_MINI_MAP)
	{
		col = 0;
		while (col <= SCALE_MINI_MAP)
		{
			my_pixel_put(game, j + multiplier[1] + col, \
												i + str + multiplier[0], NULL);
			col++;
		}
		str++;
	}
}

void	set_minimap(t_game *game)
{
	char	**map;
	int		color;
	int		j;
	int		i;
	int		multiplier[2];

	i = 0;
	map = game->square_map;
	multiplier[0] = 0;
	while (map[i])
	{
		j = 0;
		multiplier[1] = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			color = argb_to_int(0, 0, 0, 250);//цвет пола 
			if (map[i][j] == '1')
				color = argb_to_int(0, 200, 0, 0);//цвет стен
			set_pixel_minimap(game, j + 20, i + 20, multiplier);
			multiplier[1] += SCALE_MINI_MAP;
			j++;
		}
		multiplier[0] += SCALE_MINI_MAP;
		i++;
	}
}
*/
