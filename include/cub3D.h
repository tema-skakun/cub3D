/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:58 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/06 20:45:02 by jg               ###   ########.fr       */
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
# include <mlx.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_game
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];
	int		x;
	int		y;
	int		hero;
	char	**map;
	t_vars	*vars;
}				t_game;

int		parser(int argc, char *av, t_game *game);
int		ft_error(char *str);
void	cleaner(t_game *game);
void	free_point_str(char **p_str);
char	*get_next_line(int fd);
// char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoin_gnl(char *s1, char const *s2);

// execute;
void execute(t_game *game);

#endif
