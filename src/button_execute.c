#include "cub3D.h"

int	close_esc(int keycode, t_game *game)
{
	(void) game;
	if (keycode == 53)
	{
		mlx_destroy_window(game->vars->mlx, game->vars->win);
		free(game->vars);
		cleaner(game);
		exit(0);
	}
	return (0);
}

int	move_all(t_game *game, double x, double y)
{
	if (x == y)
	{
		game->info->player_pos_x += y * cos(from_zero_to_pi(game->info->view + PI / 6));
		game->info->player_pos_y += x * sin(from_zero_to_pi(game->info->view + PI / 6));
	}
	else
	{
		game->info->player_pos_x += y * cos(from_zero_to_pi(game->info->view - PI / 3));
		game->info->player_pos_y += x * sin(from_zero_to_pi(game->info->view + 2 * PI / 3));
	}
	set_map(game);
	return (1);
}

int	look(t_game *game, double x)
{
	game->info->view = from_zero_to_pi(game->info->view + x * RADIAN);
	set_map(game);
	return(1);
}

int move(int keycode, t_game *game){
	close_esc(keycode, game);
	if (keycode == 13) // w
		move_all(game, 0.4, 0.4);
	else if (keycode == 0) // a
		move_all(game, -0.4, 0.4);
	else if (keycode == 1) // s
		move_all(game, -0.4, -0.4);
	else if (keycode == 2) // d
		move_all(game, 0.4, -0.4);
	else if (keycode == 123) // l
		look(game, -3);
	else if (keycode == 124) // r
		look(game, 3);
	return (0);
}