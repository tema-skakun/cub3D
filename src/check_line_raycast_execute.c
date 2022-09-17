# include "cub3D.h"

static void	check_horizontal_line(float *xy, float ppy, float ppx, float angle)
{
	if (angle > 0 && angle < (float)PI)//Если луч направлен вверх
	{
		xy[1] = (float)ceil(ppy - 1.0f);//координата гор сетки
		xy[0] = ppx + (ppy - xy[1]) / (float)tan(angle);//координата верт сетки
	}
	else if (angle > (float)PI && angle < 2.0f * (float)PI)//Если луч направлен вниз
	{
		xy[1] = (float)trunc(ppy + 1.0f);//координата гор сетки
		xy[0] = ppx - (xy[1] - ppy) / (float)tan(angle);//координата верт сетки
	}
}

static void	check_vertical_line(float *xy, float ppy, float ppx, float angle)
{
	if (angle < (float)PI / 2.0f || angle > 3.0f * (float)PI / 2.0f)//если луч брошен вправо
	{
		xy[2] = (float)trunc(ppx + 1.0f);
		xy[3] = ppy - (xy[2] - ppx) * (float)tan(angle);
	}
	else if (angle > (float)PI / 2.0f || angle < 3 * (float)PI / 2.0f)//если луч брошен влево
	{
		xy[2] = (float)ceil(ppx - 1.0f);
		xy[3] = ppy + (ppx - xy[2]) * (float)tan(angle);
	}
}

float	pythagor(float x1, float y1, float x2, float y2)
{
	float	hypotenuse;

	hypotenuse = (float)sqrt((float)pow(x1 - x2, 2.0f) + (float)pow(y1 - y2, 2.0f));
	return (hypotenuse);
}

void	find_coordinate_grid(float *beam_coor_y, float *beam_coor_x, float angle, t_game *game)
{
	float	xy[4];
	float	hypotenuse[2];

	game->info->wall = 0;
	check_horizontal_line(xy, *beam_coor_y, *beam_coor_x, angle);//поиск пересечения с сеткой
	check_vertical_line(xy, *beam_coor_y, *beam_coor_x, angle);//поиск пересечения с сеткой
	hypotenuse[0] = pythagor(xy[0], xy[1], *beam_coor_x, *beam_coor_y);//расстояние до горизонтальной сетки
	hypotenuse[1] = pythagor(xy[2], xy[3], *beam_coor_x, *beam_coor_y);//расстояние до вертикальной сетки
	if (hypotenuse[0] < hypotenuse[1])//если гор сетка ближе чем верт
	{
		*beam_coor_x = xy[0];
		*beam_coor_y = xy[1];
		game->info->wall = 1;//горизонтальная линия
	}
	else if (hypotenuse[0] >= hypotenuse[1])
	{
		*beam_coor_x = xy[2];
		*beam_coor_y = xy[3];
		game->info->wall = 2;//вертикальная линия
	}
}

int	check_hit_wall(char **map, float beam_coor_y, float beam_coor_x)//проверка попадания в стену
{
	if (beam_coor_y == (int)beam_coor_y)
	{
		beam_coor_y = beam_coor_y - 1.0f;
		beam_coor_x = (float)trunc(beam_coor_x);
	}
	else if (beam_coor_x == (int)beam_coor_x)
	{
		beam_coor_x = beam_coor_x - 1.0f;
		beam_coor_y = (float)trunc(beam_coor_y);
	}
	if (map[(int)beam_coor_y][(int)beam_coor_x] \
		&& map[(int)beam_coor_y][(int)beam_coor_x] == '1')
		return (0);
	return (1);
}
