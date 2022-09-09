#include "cub3D.h"

void	move_all(t_game *game, float x, float y)
{
	float	move_x;
	float	move_y;
	float	tmp_x;
	float	tmp_y;

	tmp_x = game->info->player_pos_x;
	tmp_y = game->info->player_pos_y;
	if (x == y)// движение вперёд-назад (поправил рассчёт)
	{
		while (game->square_map[(int)tmp_y][(int)tmp_x] && (game->square_map[(int)tmp_y][(int)tmp_x] != '1'))
		{
			if (x > 0.0f)
				find_coordinate_grid(&tmp_y, &tmp_x, game->info->view, game);
			else
				find_coordinate_grid(&tmp_y, &tmp_x, from_zero_to_2_pi((float)PI + game->info->view), game);
			if (!check_hit_wall(game->square_map, tmp_y, tmp_x)) // доп проверка для попадание в стену
				break ;
		}
		move_x = x * (float)cos(from_zero_to_2_pi(game->info->view));
		move_y = y * (float)-sin(from_zero_to_2_pi(game->info->view));
	}
	else// движение влево-вправо (поправил рассчёт)
	{
		while (game->square_map[(int)tmp_y][(int)tmp_x] && (game->square_map[(int)tmp_y][(int)tmp_x] != '1'))
		{
			if (x > 0.0f)
				find_coordinate_grid(&tmp_y, &tmp_x, from_zero_to_2_pi(game->info->view - (float)PI / 2.0f), game);
			else
				find_coordinate_grid(&tmp_y, &tmp_x, from_zero_to_2_pi(game->info->view + (float)PI / 2.0f), game);
			if (!check_hit_wall(game->square_map, tmp_y, tmp_x)) // доп проверка для попадание в стену
				break ;
		}
		move_x = x * (float)-cos(from_zero_to_2_pi(game->info->view + (float)PI / 2.0f));
		move_y = y * (float)sin(from_zero_to_2_pi(game->info->view - (float)PI / 2.0f));
	}
	// printf ("x = %f  player = %f\n", tmp_x, game->info->player_pos_x);
	// printf (" length  = %f  length 2 = %f\n", pow(tmp_x - game->info->player_pos_x , 2) + pow(tmp_y - game->info->player_pos_y, 2), pow(move_x, 2) + pow(move_y, 2));
	if ((float)pow(tmp_x - game->info->player_pos_x , 2) + (float)pow(tmp_y - game->info->player_pos_y, 2) >= (float)pow(move_x, 2) + (float)pow(move_y, 2))
	{
		game->info->player_pos_x += move_x;
		game->info->player_pos_y += move_y;
	}
	// tmp_x += move_x;
	// tmp_y += move_y;
	// if (tmp_x >= 0 && tmp_y >= 0 && tmp_y <= game->x - 1 && tmp_x <= game->y - 1)//герой не пойдёт за пределы карты
	// {
	// 	game->info->player_pos_x = tmp_x;
	// 	game->info->player_pos_y = tmp_y;
	// }
	// set_map(game);
}

void	look(t_game *game, float x)
{
	game->info->view = from_zero_to_2_pi(game->info->view + x * (float)RADIAN);
	// set_map(game);
	// return(1);
}

int	red_cross(int keycode, t_game *game)
{
	(void)game;
	(void)keycode;
	exit(0);
	return (0);
}

int	move(int keycode, t_game *game)
{
	if (keycode == 13) // w
		move_all(game, 0.2f, 0.2f);
	else if (keycode == 0) // a
		move_all(game, -0.2f, 0.2f);
	else if (keycode == 1) // s
		move_all(game, -0.2f, -0.2f);
	else if (keycode == 2) // d
		move_all(game, 0.2f, -0.2f);
	else if (keycode == 123) // l
		look(game, 2.0f);
	else if (keycode == 124) // r
		look(game, -2.0f);
	else if (keycode == 53) // esc
	{
		mlx_destroy_window(game->vars->mlx, game->vars->win);
		free(game->vars);
		cleaner(game);
		exit(0);
	}
	return (0);
}
