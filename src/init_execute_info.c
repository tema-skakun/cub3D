#include "cub3D.h"

float	from_zero_to_pi(float degree)
{
	if (degree < 0)
		degree += 2 * PI;
	else if (degree >= 2 * PI)
		degree = degree - 2 * PI;
	return (degree);
}

static void find_pos_hero(char **map, t_info *info){
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				info->player_pos_x = j;
				info->player_pos_y = i;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static void	set_vision(t_game *game, char start)
{
	game->info->view = 0;
	if (start == 'N')
		game->info->view = PI / 2;
	else if (start == 'W')
		game->info->view = PI;
	else if (start == 'S')
		game->info->view = 3 * PI / 2;
}

void	init_info(t_game *game)
{
	game->vars = malloc(sizeof(t_vars)); // mlx данные
	if (game->vars == NULL)
	    ft_error("Error: Memmory are not allocated"); 
	game->info = malloc(sizeof(t_info)); // данные игрока
	if (game->info == NULL)
		ft_error("Error: Memmory are not allocated"); 
	find_pos_hero(game->square_map, game->info); // нахождение позиции игрока
	game->i = 0;
	game->vars->mlx = mlx_init();
	game->vars->win = mlx_new_window(game->vars->mlx, WIDTH, HEIGHT, "cub3D_minimap");
	set_vision(game, game->square_map[(int) game->info->player_pos_y][(int) game->info->player_pos_x]); // установка направление взгляда
}
