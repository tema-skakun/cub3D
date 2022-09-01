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

void	move_all(t_game *game, double x, double y)
{
	double	move_x;
	double	move_y;
	double	tmp_x;
	double	tmp_y;

	tmp_x = game->info->player_pos_x;
	tmp_y = game->info->player_pos_y;
	if (x == y)// движение вперёд-назад (поправил рассчёт)
	{
		move_x = x * cos(from_zero_to_pi(game->info->view));
		move_y = y * -sin(from_zero_to_pi(game->info->view));
	}
	else// движение влево-вправо (поправил рассчёт)
	{
		move_x = x * -cos(from_zero_to_pi(game->info->view + PI / 2));
		move_y = y * sin(from_zero_to_pi(game->info->view - PI / 2));
	}
	tmp_x += move_x;
	tmp_y += move_y;
	if (tmp_x >= 0 && tmp_y >= 0 && tmp_y <= game->x - 1 && tmp_x <= game->y - 1)//герой не пойдёт за пределы карты
	{
		game->info->player_pos_x = tmp_x;
		game->info->player_pos_y = tmp_y;
	}
	// set_map(game);
}

void	look(t_game *game, double x)
{
	game->info->view = from_zero_to_pi(game->info->view + x * RADIAN);
	// set_map(game);
	// return(1);
}

int	move(int keycode, t_game *game)
{
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
		look(game, 3);
	else if (keycode == 124) // r
		look(game, -3);
	return (0);
}
