/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:58 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/08 18:23:21 by mmeredit         ###   ########.fr       */
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
# define PI		3.1415926
# define scale_mini_map 4

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

// execute need some parametres
typedef struct s_info
{
	double	player_pos_x;
	double	player_pos_y;
	double	view;
	int		wall;//1 - горизонтальная; 2 - вертикальная
	int		color_wall;
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
	char	*no;//северная текстура
	char	*so;//южная
	char	*we;//западная
	char	*ea;//восточная
	int		f[3];//цвет F
	int		c[3];//цвет C
	int		i;
	// int		num_str;//считал кол-во строк в файле (сейчас малочу по дефолту 3000)
	int		x;//кол-во строк
	int		y;//максимальное кол-во столбцов
	int		len;//временная переменная для поиска длиннейшей строки
	int		hero;//кол-во героев на карте
	char	**file;//здесь лежит весь файл
	char	**map;//это карта без конфигураций
	char	**square_map;//квадратная карта
	t_vars	*vars;
	t_info	*info;
	t_img	img;
}				t_game;

// parser;
void		parser(int argc, char *av, t_game *game);
int		ft_error(char *str);
void	cleaner(t_game *game);
void	free_point_str(char **p_str);
char	*get_next_line(int fd);
// char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoin_gnl(char *s1, char const *s2);
// void	get_map(t_game *game, char *base);
void	validation_check_map(t_game *game);
void	check_colors(char **digits);
// void	add_path_texture(char **path, char *line, char *str, int *key);
// void	add_color(int *rgb, char *line, int *key);
// int		check_textures(t_game *game);
void	convert_digit(int *rgb, char **digit);
char	*return_word_and_plus_i(char *line, int *i);
void	*ft_calloc_8(size_t count, size_t size);
void	squaring_map(t_game *game);
void	from_file_to_map(char **map, char **file, int *i, int *j);

// execute;
void	execute(t_game *game);
void	init_info(t_game *game);
int		argb_to_int(int a, int r, int g, int b);
void	draw_all(t_game *game);
int		set_map(t_game *game);
void	set_minimap(t_game *game);
void	some_raycasting(t_game *game, double i, double j);
float	from_zero_to_pi(float degree);
int		move(int keycode, t_game *game);
int		red_cross(int keycode, t_game *game);
void	full_raycasting(double *i, double *j, double degree, t_game *game);
int		check_hit_wall(char **map, double i, double j);
double	ft_abs(double number);
double	set_camera_degree(double degree, int *sign);
void	my_pixel_put(t_img texture, int x, int y, int color);

//del;
void	print_game(t_game *game);

#endif
