/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jg <jg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:58 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/08/18 00:12:22 by jg               ###   ########.fr       */
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
# define RADIAN 0.0174533

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

// execute need some parametres
typedef struct s_info
{
	double player_pos_x;
	double player_pos_y;
	double view;
	// 4 void*;
}	t_info;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;


typedef struct s_game
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];
	int		num_str;
	int		x;
	int		y;
	int		len;
	int		hero;
	char	**file;
	char	**map;
	int		*digit_map;
	t_vars	*vars;
	t_info	*info;
}				t_game;

// parser;
int		parser(int argc, char *av, t_game *game);
int		ft_error(char *str);
void	cleaner(t_game *game);
void	free_point_str(char **p_str);
char	*get_next_line(int fd);
// char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoin_gnl(char *s1, char const *s2);
void	get_map(t_game *game, char *base);
void	validation_check_map(t_game *game);
// void	add_path_texture(char **path, char *line, char *str, int *key);
// void	add_color(int *rgb, char *line, int *key);
int		check_textures(t_game *game);
void	convert_digit(int *rgb, char **digit);
char	*return_word_and_plus_i(char *line, int *i);

// execute;
void execute(t_game *game);

//del;
void	print_game(t_game *game);

#endif
