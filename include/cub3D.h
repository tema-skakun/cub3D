/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:52:58 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/09/18 14:23:31 by fdarkhaw         ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 720
# define RADIAN 0.0174533f
# define PI		3.1415926f
# define SCALE_MINI_MAP 3
# define FOV	60

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		hight;
	float	length;
	float	ray_x;
	float	ray_y;
}	t_img;

// execute need some parametres
typedef struct s_info
{
	float	player_pos_x;
	float	player_pos_y;
	float	view;
	int		wall;//1 - горизонтальная; 2 - вертикальная
	t_img	tex[4];
}	t_info;

typedef struct s_game
{
	char	*no;//северная текстура
	char	*so;//южная
	char	*we;//западная
	char	*ea;//восточная
	int		f[3];//цвет F
	int		c[3];//цвет C
	int		i;
	int		num_str;//считаю кол-во строк в файле
	int		x;//кол-во строк в карте
	int		y;//максимальное кол-во столбцов карте
	int		len;//временная переменная для поиска длиннейшей строки
	int		hero;//кол-во героев на карте
	char	**file;//здесь лежит весь файл
	char	**map;//это карта без конфигураций
	char	**square_map;//квадратная карта
	float	angle;// угол каждого луча
	t_vars	*vars;
	t_info	*info;
	t_img	img;
}				t_game;

// parser;
void	parser(int argc, char *av, t_game *game);
int		ft_error(char *str);
void	cleaner(t_game *game);
void	free_point_str(char **p_str);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char const *s2);
void	validation_check_map(t_game *game);
void	check_colors(char **digits);
void	convert_digit(int *rgb, char **digit);
void	*ft_calloc_8(size_t count, size_t size);
void	squaring_map(t_game *game);
void	get_map(t_game *game);

// execute;
void	execute(t_game *game);
void	init_info(t_game *game);
int		argb_to_int(int a, int r, int g, int b);
void	draw_all(t_game *game);
int		set_map(t_game *game);
void	set_minimap(t_game *game);
void	raycasting(t_game *game);
float	from_zero_to_2_pi(float degree);
int		move(int keycode, t_game *game);
int		red_cross(int keycode, t_game *game);
void	find_coordinate_grid(float *i, float *j, float degree, t_game *game);
int		check_hit_wall(char **map, float i, float j);
// float	ft_abs(float number);
// float	set_camera_degree(float degree, int *sign);
void	my_pixel_put(t_game *game, int x, int y, t_img *img);
float	pythagor(float x1, float y1, float x2, float y2);
float	ray(t_game *game, int counter, float ang);

#endif
