# include "cub3D.h"

void execute(t_game *game){
    (void) game;
    game->vars = malloc(sizeof(t_vars));
    game->vars->mlx = mlx_init();
    void    *floor;
    void    *wall;
    void    *start;


    int	width = 32;
	int hight = 32;

	floor = mlx_xpm_file_to_image(game->vars->mlx, "/Users/mmeredit/Desktop/cubas/Textures/floor.xpm", &width, &hight);
	wall = mlx_xpm_file_to_image(game->vars->mlx, "/Users/mmeredit/Desktop/cubas/Textures/wall.xpm", &width, &hight);
	start = mlx_xpm_file_to_image(game->vars->mlx, "/Users/mmeredit/Desktop/cubas/Textures/dot.xpm", &width, &hight); 

	char **map = game->map;
	int i = 0;
	int j = 0;

    game->vars->win = mlx_new_window(game->vars->mlx, 2240, 1080, "cub3D");

    // printf("MYMAP\n");
    // while (map[i]){
    //     printf ("%s", map[i]);
    //     i++;
    // }
    // i = 0;

	while (map[i])
	{
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == '1' || map[i][j] == ' ')
			{
				mlx_put_image_to_window(game->vars->mlx, game->vars->win, wall, j * 64, i * 64);
			}
			else if (map[i][j] == '0')
			{
				mlx_put_image_to_window(game->vars->mlx, game->vars->win, floor, j * 64, i * 64);
			}
			else if (map[i][j] == 'N')
			{
				mlx_put_image_to_window(game->vars->mlx, game->vars->win, floor, j * 64, i * 64);
				mlx_put_image_to_window(game->vars->mlx, game->vars->win, start, j * 64, i * 64);
			}
			j++;
		}
		j = 0;
		i++;
	}
    mlx_loop(game->vars->mlx);
}