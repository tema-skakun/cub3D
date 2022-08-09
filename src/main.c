/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:42:07 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/30 17:51:19 by jg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	game = (t_game){};
	parser(argc, argv[1], &game);

	execute(&game); // execute;

	cleaner(&game);


	return (0);
}
