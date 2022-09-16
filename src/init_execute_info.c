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

void	init_textures(t_game *game)
{
	game->info->tex[0].ptr = mlx_xpm_file_to_image(game->vars->mlx, game->no, \
		&game->info->tex[0].width, &game->info->tex[0].hight);
	game->info->tex[1].ptr = mlx_xpm_file_to_image(game->vars->mlx, game->so, \
		&game->info->tex[1].width, &game->info->tex[1].hight);
	game->info->tex[2].ptr = mlx_xpm_file_to_image(game->vars->mlx, game->ea, \
		&game->info->tex[2].width, &game->info->tex[2].hight);
	game->info->tex[3].ptr = mlx_xpm_file_to_image(game->vars->mlx, game->we, \
		&game->info->tex[3].width, &game->info->tex[3].hight);
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
	init_textures(game);
	set_vision(game, game->square_map[(int)game->info->player_pos_y][(int)game->info->player_pos_x]);// установка направление взгляда
}
