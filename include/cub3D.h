/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:58 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/25 21:35:38 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>//read, close, write
# include <fcntl.h>//open
# include <stdio.h>//printf, perror
# include <stdlib.h>//malloc, free, exit
# include <string.h>//strerror
# include <math.h>

int		parser(int argc, char **argv);
void	ft_error(void);

#endif
