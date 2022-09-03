#include "cub3D.h"

int argb_to_int(int a, int r, int g, int b){
	return (a << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put_2(t_img texture, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)// Колина проверка, она от чего то защищает
		return ;
	dst = texture.addr + (y * texture.size_line + x * (texture.bits_per_pixel / 8));
	if (color != 0)// костыль для работы set_textures
		*(unsigned int *)dst = color;
}

static void	set_pixel_minimap(t_img img, int j, int i, int color, int *mnogitel)
{
	int	a;//строки
	int	b;//столбцы
	// unsigned int	*dst;

	a = 0;
	while (a < 4)
	{
		b = 0;
		while (b < 4)
		{
			my_mlx_pixel_put(img, j + mnogitel[1] + b, i + a + mnogitel[0], color);
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

static void	set_minimap(t_game *game)
{
	char	**map;
	int		color;
	int		j;
	int		i;
	int		mnogitel[2];

	i = 0;
	map = game->square_map;
	mnogitel[0] = 0;
	while (map[i])
	{
		j = 0;
		mnogitel[1] = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			color = argb_to_int(0, 0, 0, 100);//цвет пола 
			if (map[i][j] == '1')
				color = argb_to_int(0, 200, 0, 0);//цвет стен
			else if (map[i][j] == '8')
				color = argb_to_int(0, 0, 100, 0);//цвет пустоты
			set_pixel_minimap(game->img, j + 20, i + 20, color, mnogitel);
			mnogitel[1] += 2;
			j++;
		}
		mnogitel[0] += 2;
		i++;
	}
}

static void	draw_all(t_game *game)
{
	// t_img			img;
	int				i;
	int				color;
	unsigned int	*tmp;

	// img.ptr = mlx_new_image(game->vars->mlx, game->y * 32, game->x * 32);
	// img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	mlx_clear_window(game->vars->mlx, game->vars->win);//или вызывать тут, а можно вообще не вызывать - ликов не будет
	tmp = (unsigned int *)game->img.addr;
	color = argb_to_int(0, game->c[0], game->c[1], game->c[2]);//потолок - ceilling
	i = game->x * 32 / 8 * game->img.size_line;
	while (--i)
		*tmp++ = color;
	color = argb_to_int(0, game->f[0], game->f[1], game->f[2]);//пол - floor
	i = game->x * 32 / 8 * game->img.size_line;
	while (--i)
		*tmp++ = color;
	some_raycasting(game, game->info->player_pos_y, game->info->player_pos_x);//raycasting - отрисовка стен происходит в той же img, где нарисован пол и потолок
}

int	set_map(t_game *game)
{
	// if (game->i == 65)//зачем это замедление?
	// {
	game->img.ptr = mlx_new_image(game->vars->mlx, game->y * 32, game->x * 32);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bits_per_pixel, \
										&game->img.size_line, &game->img.endian);
	// mlx_clear_window(game->vars->mlx, game->vars->win);//можно вызывать тут
	draw_all(game);//заполнение пола, неба и стен
	set_minimap(game);//заполнение миникарты (временное решение. Создано для удобной отладки)
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, game->img.ptr, 0, 0);//помещаю итоговое img в окно
	mlx_destroy_image(game->vars->mlx, game->img.ptr);//разрушаю img, что бы не кушать много физической памяти
	// game->i = 0;
	// }
	// game->i++;
	return (0);
}
