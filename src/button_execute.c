#include "cub3D.h"

void	slide(t_game *game, float x, float y)
{
	float	tmp_degree;

	// printf("LOL\n");// раскомментируй - заработает.
	if (game->info->wall == 1)//горизонтальная - НЕ работает
	{
		tmp_degree = (float) PI;
		if (cos(game->info->view) >= 0)
			tmp_degree = 0.0f;
		if (ray(game, tmp_degree, -1) > 0.2f)
			game->info->player_pos_x += x;
	}
	else//вертикальная - работает
	{
		tmp_degree = (float) 3 * PI / 2;
		if (sin(game->info->view) >= 0)
			tmp_degree = (float) PI / 2;
		if (ray(game, tmp_degree, -1) > 0.2f)
			game->info->player_pos_y += y;
	}
}

void	move_all(t_game *game, float x, float y, float degree)
{
	float	move_x;
	float	move_y;

	if (x == y)//движение вперёд-назад (поправил рассчёт)
	{
		move_x = x * (float)cos(from_zero_to_2_pi(game->info->view));
		move_y = y * (float)-sin(from_zero_to_2_pi(game->info->view));
	}
	else// движение влево-вправо (поправил рассчёт)
	{
		move_x = x * (float)-cos(from_zero_to_2_pi(game->info->view + (float)PI / 2.0f));
		move_y = y * (float)sin(from_zero_to_2_pi(game->info->view - (float)PI / 2.0f));
	}
	// printf ("ray1 = %f, ray2 = %f \n", ray(game, from_zero_to_2_pi(degree)), pythagor(0, 0, move_x, move_y));
	if (ray(game, from_zero_to_2_pi(degree), -1) > 0.2f)
	{
		game->info->player_pos_x += move_x;
		game->info->player_pos_y += move_y;
	}
	else
	{
		if (x == y && x > 0)
			slide(game, move_x, move_y);
	}
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
		move_all(game, 0.2f, 0.2f, game->info->view);
	else if (keycode == 0) // a
		move_all(game, -0.2f, 0.2f, game->info->view + (float) PI / 2);
	else if (keycode == 1) // s
		move_all(game, -0.2f, -0.2f, game->info->view + (float) PI);
	else if (keycode == 2) // d
		move_all(game, 0.2f, -0.2f, game->info->view - (float) PI / 2);
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
