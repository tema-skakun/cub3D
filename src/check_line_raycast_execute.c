# include "cub3D.h"

static void	check_horizontal_line(double *points, double ppy, double ppx, double angle)//i = ppy; j = ppx
{
	if (angle > 0 && angle < PI)
	{
		points[1] = ceil(ppy - 1);
		points[0] = ppx + (ppy - points[1]) * 1 / tan(angle);
	}
	else if (angle > PI)
	{
		points[1] = trunc(ppy + 1);
		points[0] = ppx - (points[1] - ppy) * 1 / tan(angle);
	}
	else
	{
		points[1] = ppy;
		points[0] = ceil(ppx + cos(angle));
		if (cos(angle) > 0)
			points[0] = trunc(ppx + cos(angle));
	}
}

static void	check_vertical_line(double *points, double i, double j, double angle)
{
	if (angle < PI / 2 || angle > 3 * PI / 2)
	{
		points[2] = trunc(j + 1);
		points[3] = i - (points[2] - j) * tan(angle);
	}
	else if (angle > PI / 2 || angle < 3 * PI / 2)
	{
		points[2] = ceil(j - 1);
		points[3] = i + (j - points[2]) * tan(angle);
	}
	else
	{
		points[2] = j;
		points[3] = trunc(i - sin(angle));
		if (sin(angle) > 0)
			points[3] = ceil(i - sin(angle));
	}
}

void	full_raycasting(double *ppy, double *ppx, double angle, t_game *game)
{
	double	points[4];
	double	delta;

	game->info->wall = 0;
	check_horizontal_line(points, *ppy, *ppx, angle);//поиск пересечения с сеткой
	check_vertical_line(points, *ppy, *ppx, angle);//поиск пересечения с сеткой
	delta = sqrt(pow(points[0] - *ppx, 2) + pow(points[1] - *ppy, 2));//расстояние до сетки
	if (delta < sqrt(pow(points[2] - *ppx, 2) + pow(points[3] - *ppy, 2)))
	{
		*ppy = points[1];
		*ppx = points[0];
		game->info->wall = 1;//горизонтальная линия
	}
	else
	{
		*ppy = points[3];
		*ppx = points[2];
		game->info->wall = 2;//вертикальная линия
	}
}

int	check_hit_wall(char **map, double i, double j)//округляет координаты стены
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
	// printf("y = %f, x = %f\n", i, j);
	if (map[(int)i][(int)j] && map[(int)i][(int)j] == '1')
		return (0);
	return (1);
}
