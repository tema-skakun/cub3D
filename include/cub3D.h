/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:58 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/07/29 21:02:31 by fdarkhaw         ###   ########.fr       */
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

typedef struct s_game
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	int		x;
	int		y;
	char	hero;
}				t_game;



int		parser(int argc, char *av, t_game *game);
int 	ft_error(char *str);
void	cleane(t_game *game);
char    *get_next_line(int fd);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoin_gnl(char *s1, char const *s2);

#endif
