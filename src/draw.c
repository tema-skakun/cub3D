#include "cub3D.h"

int argb_to_int(int a, int r, int g, int b){
	return (a << 24 | r << 16 | g << 8 | b);
}

static void	set_pixel_minimap(int color, t_game *game, int i, int j)
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
	mlx_destroy_image(game->vars->mlx, img.ptr);
}

static void	set_minimap(t_game *game)
{
	char	**map;
	int		color;
	int		j;
	int		i;

	i = 0;
	map = game->square_map;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			color = argb_to_int(0, 199, 199, 199);
			if (map[i][j] == '0' || map[i][j] != '1')
				color = argb_to_int(0, 100, 0, 230);
			else if (map[i][j] == ' ' || map[i][j] == '8')//в квадратной карте "8"
				color = argb_to_int(0, 210, 100, 50);
			set_pixel_minimap(color, game, (i + game->x) * 32, j * 32);
			j++;
		}
		i++;
	}
}

static void	draw_all(t_game *game)
{
	t_img			img;
	int				i;
	int				color;
	unsigned int	*tmp;

	img.ptr = mlx_new_image(game->vars->mlx, game->y * 32, game->x * 32);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	mlx_clear_window(game->vars->mlx, game->vars->win);//или вызывать тут, а можно вообще не вызывать - ликов не будет
	tmp = (unsigned int *)img.addr;
	color = argb_to_int(0, game->c[0], game->c[1], game->c[2]);//потолок - ceilling
	i = game->x * 32 / 8 * img.size_line;
	while (--i)
		*tmp++ = color;
	color = argb_to_int(0, game->f[0], game->f[1], game->f[2]);//пол - floor
	i = game->x * 32 / 8 * img.size_line;
	while (--i)
		*tmp++ = color;
	some_raycasting(game, game->info->player_pos_y, game->info->player_pos_x, img);//raycasting - отрисовка стен происходит в той же img, где нарисован пол и потолок
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, img.ptr, 0, 0);//помещаю итоговое img в окно
	mlx_destroy_image(game->vars->mlx, img.ptr);//разрушаю img, что бы не кушать много физической памяти
}

int	set_map(t_game *game)
{
	if (game->i == 65)
	{
		// mlx_clear_window(game->vars->mlx, game->vars->win);//можно вызывать тут
		draw_all(game);//заполнение пола, неба и стен
		set_minimap(game);//заполнение миникарты (временное решение. Создано для удобной отладки)
		game->i = 0;
	}
	game->i++;
	return (0);
}
