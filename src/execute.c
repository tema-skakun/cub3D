/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:23:57 by mmeredit          #+#    #+#             */
/*   Updated: 2022/09/14 21:16:49 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int	set_map(t_game *game)
{
	// if (game->i == 65)//зачем это замедление?
	// {
	game->img.ptr = mlx_new_image(game->vars->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bits_per_pixel, \
										&game->img.size_line, &game->img.endian);
	mlx_clear_window(game->vars->mlx, game->vars->win);//можно вообще не вызывать - ликов не будет
	draw_all(game);//заполнение пола, неба и стен
	mlx_put_image_to_window(game->vars->mlx, game->vars->win, game->img.ptr, 0, 0);//помещаю итоговое img в окно
	mlx_destroy_image(game->vars->mlx, game->img.ptr);//разрушаю img, что бы не кушать много физической памяти
	// game->i = 0;
	// }
	// game->i++;
	return (0);
}

void	execute(t_game *game)
{
	init_info(game); // Инициализация данных
	// set_textures(game);
	// set_map(game);// можно вызывать только в mlx_loop_hook
	mlx_hook(game->vars->win, 2, 0, &move, game);
	mlx_hook(game->vars->win, 17, 0, &red_cross, game);//выход красным крестиком
	mlx_loop_hook(game->vars->mlx, &set_map, game);
    mlx_loop(game->vars->mlx);
}
