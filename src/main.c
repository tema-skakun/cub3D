/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:42:07 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/25 21:48:25 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	(void)argv;
	printf("argc = %i\n", argc);
	if (parser(argc, argv))
		ft_error();
	printf("parser - OK\n");
	return (argc);
}
