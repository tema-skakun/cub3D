#include "cub3D.h"

void	my_pixel_put(t_img texture, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)// Колина проверка, она от чего то защищает
		return ;
	dst = texture.addr + (y * texture.size_line + x * (texture.bits_per_pixel / 8));
	if (color != 0)// костыль для работы set_textures
		*(unsigned int *)dst = color;
}

int argb_to_int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

static void	set_pixel_minimap(t_img img, int j, int i, int color, int *multiplier)
{
	int	a;//строки
	int	b;//столбцы

	a = 0;
	while (a <= scale_mini_map)
	{
		b = 0;
		while (b <= scale_mini_map)
		{
			my_pixel_put(img, j + multiplier[1] + b, i + a + multiplier[0], color);
			b++;
		}
		a++;
	}
}

// static void	set_pixel_minimap(int color, t_game *game, int i, int j)
// {
// 	t_img			img;
// 	unsigned int	*tmp;
// 	int				k;

// 	k = 0;
// 	img.ptr = mlx_new_image(game->vars->mlx, 32, 32);
// 	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
// 	tmp = (unsigned int *)img.addr;
// 	while (k++ < 32 / 4 * img.size_line)
// 		*tmp++ = color;	
// 	mlx_put_image_to_window(game->vars->mlx, game->vars->win, img.ptr, j, i);
// 	mlx_destroy_image(game->vars->mlx, img.ptr);
// }

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
			else if (map[i][j] == '8')
				color = argb_to_int(0, 0, 200, 0);//цвет пустоты
			set_pixel_minimap(game->img, j + 20, i + 20, color, multiplier);
			multiplier[1] += scale_mini_map;
			j++;
		}
		multiplier[0] += scale_mini_map;
		i++;
	}
}

void	draw_all(t_game *game)
{
	int				i;
	// int				j;
	int				color;
	unsigned int	*tmp;

	tmp = (unsigned int *)game->img.addr;
	color = argb_to_int(0, game->c[0], game->c[1], game->c[2]);//потолок - ceilling
	i = game->x * 32 / 8 * game->img.size_line;
	while (--i)
		*tmp++ = color;
		// my_pixel_put(game->img, j, i, color);
	color = argb_to_int(0, game->f[0], game->f[1], game->f[2]);//пол - floor
	i = game->x * 32 / 8 * game->img.size_line;
	while (--i)
		*tmp++ = color;
	some_raycasting(game, game->info->player_pos_y, game->info->player_pos_x);//raycasting - отрисовка стен происходит в той же img, где нарисован пол и потолок
}