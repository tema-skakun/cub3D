# include "cub3D.h"

double	ft_abs(double number)
{
	if (number < 0)
		return (-number);
	return (number);
}

double	set_camera_degree(double degree, int *sign)
{
	if (degree <= PI / 2 || (degree >= PI && degree <= 3 * PI / 2))
		*sign = 1;
	if (degree < PI) 
		return (PI / 2);
	return (3 * PI / 2);
}