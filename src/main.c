/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulagrezina <ulagrezina@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:42:07 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/21 23:09:51 by ulagrezina       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){};
	parser(argc, argv[1], &game);//квадратная карта лежит в game->squre_map

	// execute(&game); // execute;

	cleaner(&game);


	return (0);
}
