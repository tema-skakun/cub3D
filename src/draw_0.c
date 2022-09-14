#include "cub3D.h"

void	my_pixel_put(t_game *game, int x, int y, int color, float ray_x, int ray_y, float length)
{
	char	*dst;
	unsigned int	*pixels;
	(void)	ray_x;
	(void)	ray_y;
	(void)	length;
	// int		pos;
	// if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)// Колина проверка, она от чего то защищает
	// 	return ;
	dst = game->img.addr + (y * game->img.size_line + x * (game->img.bits_per_pixel / 8));
	// printf ("HERE\n");
	if (color != 0)// костыль для работы set_textures
	{
		pixels = (unsigned int *) game->info->no.addr;
	// (int) (int) pixels[(ray_y * game->info->no.size_line / 4 + ray_x)]
	// printf ("num = %u\n", (unsigned int)pixels[(int)(length * game->info->no.size_line / 4 + ray_x)]);
		*(unsigned int *)dst = (unsigned int) pixels[(int)((int)length * game->info->no.size_line / 4 + ray_x)];
	}
}

int argb_to_int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

static void	set_pixel_minimap(t_game *game, int j, int i, int color, int *multiplier)
{
	int	a;//строки
	int	b;//столбцы

	a = 0;
	while (a <= scale_mini_map)
	{
		b = 0;
		while (b <= scale_mini_map)
		{
			my_pixel_put(game, j + multiplier[1] + b, i + a + multiplier[0], color, 0, 0, 0);
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
			set_pixel_minimap(game, j + 20, i + 20, color, multiplier);
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
	int				color;
	unsigned int	*tmp;

	tmp = (unsigned int *)game->img.addr;
	color = argb_to_int(0, game->c[0], game->c[1], game->c[2]);//потолок - ceilling
	i = HEIGHT / 8 * game->img.size_line + 1;
	while (--i)
		*tmp++ = color;
	color = argb_to_int(0, game->f[0], game->f[1], game->f[2]);//пол - floor
	i = HEIGHT / 8 * game->img.size_line + 1;
	while (--i)
		*tmp++ = color;
	raycasting(game);//raycasting - отрисовка стен происходит в той же img, где нарисован пол и потолок
}
