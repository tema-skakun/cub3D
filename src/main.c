/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:42:07 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/26 14:57:26 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){};;
	parser(argc, argv[1], &game);//квадратная карта лежит в game->square_map

	execute(&game); // execute;

	cleaner(&game);


	return (0);
}
