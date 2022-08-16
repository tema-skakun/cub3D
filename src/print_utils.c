#include "cub3D.h"

void	print_game(t_game *game)//del
{
	int	i = 0;
	printf("no -%s\n", game->no);
	printf("so -%s\n", game->so);
	printf("we -%s\n", game->we);
	printf("ea -%s\n", game->ea);
	printf("f - r=%d,\tg=%d,\tb=%d\n", game->f[0], game->f[1], game->f[2]);
	printf("c - r=%d,\tg=%d,\tb=%d\n", game->c[0], game->c[1], game->c[2]);
	printf("x - %d\n", game->x);
	printf("y - %d\n", game->y);
	if (game->map)
	{
		while (game->map[i])
		{
			printf("%s", game->map[i]);
			i++;
		}
	}
	(void)game;
	printf("parser is OK\n");
}
