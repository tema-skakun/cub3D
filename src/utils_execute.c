# include "cub3D.h"

float	ft_abs(float number)
{
	if (number < 0.0f)
		return (-number);
	return (number);
}

float	set_camera_degree(float degree, int *sign)
{
	if (degree <= (float)PI / 2.0f || (degree >= (float)PI && degree <= 3.0f * (float)PI / 2.0f))
		*sign = 1.0f;
	if (degree < (float)PI) 
		return ((float)PI / 2.0f);
	return (3.0f * (float)PI / 2.0f);
}
