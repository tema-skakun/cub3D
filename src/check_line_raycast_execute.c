# include "cub3D.h"

static int	check_horizontal_line(double *points, double i, double j, double degree)
{
	if (degree > 0 && degree < PI)
	{
		points[1] = ceil(i - 1);
		points[0] = j + (i - points[1]) * 1 / tan(degree);
		return (1);//попал в линию
	}
	else if (degree > PI)
	{
		points[1] = trunc(i + 1);
		points[0] = j - (points[1] - i) * 1 / tan(degree);
		return (1);
	}
	else
	{
		points[1] = i;
		points[0] = ceil(j + cos(degree));
		if (cos(degree) > 0)
		{
			points[0] = trunc(j + cos(degree));
			return (1);
		}
	}
	return (3);//не попал в линию
}

static int	check_vertical_line(double *points, double i, double j, double degree)
{
	if (degree < PI / 2 || degree > 3 * PI / 2)
	{
		points[2] = trunc(j + 1);
		points[3] = i - (points[2] - j) * tan(degree);
		return (2);
	}
	else if (degree > PI / 2 || degree < 3 * PI / 2)
	{
		points[2] = ceil(j - 1);
		points[3] = i + (j - points[2]) * tan(degree);
		return (2);
	}
	else
	{
		points[2] = j;
		points[3] = trunc(i - sin(degree));
		if (sin(degree) > 0)
		{
			points[3] = ceil(i - sin(degree));
			return (2);
		}
	return (3);
	}
}

void	full_raycasting(double *i, double *j, double degree, t_game *game)
{
	double	points[4];
	double	delta;

	game->info->wall = 0;
	game->info->wall = check_horizontal_line(points, *i, *j, degree);//поиск пересечения с сеткой
	check_vertical_line(points, *i, *j, degree);//поиск пересечения с сеткой
	delta = sqrt(pow(points[0] - *j, 2) + pow(points[1] - *i, 2));//расстояние до сетки
	if (delta < sqrt(pow(points[2] - *j, 2) + pow(points[3] - *i, 2)))
	{
		*i = points[1];
		*j = points[0];
	}
	else
	{
		*i = points[3];
		*j = points[2];
	}
}

int	check_hit_wall(char **map, double i, double j)//как работает эта ф-ция?
{
	if (i == (int) i)
	{
		i = i - 1;
		j = trunc(j);
	}
	else if (j == (int) j)
	{
		j = j - 1;
		i = trunc(i);
	}
	if (map[(int)i][(int)j] && map[(int)i][(int)j] == '1')
		return (0);
	return (1);
}
