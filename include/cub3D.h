/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:58 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/27 22:11:49 by fdarkhaw         ###   ########.fr       */
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
// # include <mlx.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_size
{
	int	x;
	int	y;
}				t_size;

int		parser(int argc, char *av);
int 	ft_error(char *str);
char    *get_next_line(int fd);

#endif
