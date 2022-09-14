#include "cub3D.h"

float	from_zero_to_2_pi(float degree)
{
	if (degree < 0.0f)
		degree += 2.0f * (float)PI;
	else if (degree >= 2.0f * (float)PI)
		degree = degree - 2.0f * (float)PI;
	return (degree);
}

static void	find_pos_hero(char **map, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))// == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				info->player_pos_x = j + 0.5f;//если не делать +0,5 при инициализации игрока в углу карты при повороте на 360 - сега
				info->player_pos_y = i + 0.5f;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	set_vision(t_game *game, char start)
{
	game->info->view = 0.0f;
	if (start == 'N')
		game->info->view = (float)PI / 2.0f;
	else if (start == 'W')
		game->info->view = (float)PI;
	else if (start == 'S')
		game->info->view = 3.0f * (float)PI / 2.0f;
}

void	init_info(t_game *game)
{
	game->vars = malloc(sizeof(t_vars)); // mlx данные
	if (game->vars == NULL)
	    ft_error("Error: Memmory was not allocate properly"); 
	game->info = malloc(sizeof(t_info)); // данные игрока
	if (game->info == NULL)
		ft_error("Error: Memmory was not allocate properly"); 
	find_pos_hero(game->square_map, game->info); // нахождение позиции игрока
	game->vars->mlx = mlx_init();
	game->vars->win = mlx_new_window(game->vars->mlx, WIDTH, HEIGHT, "cub3D");
	game->info->no.ptr = mlx_xpm_file_to_image(game->vars->mlx, game->no, &game->info->no.width, &game->info->no.hight);
	game->info->no.addr = mlx_get_data_addr(game->info->no.ptr, &game->info->no.bits_per_pixel, &game->info->no.size_line, &game->info->no.endian);
	set_vision(game, game->square_map[(int)game->info->player_pos_y][(int)game->info->player_pos_x]);// установка направление взгляда
}
