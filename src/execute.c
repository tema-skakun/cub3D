# include "cub3D.h"

void execute(t_game *game){
    (void) game;
    game->vars = malloc(sizeof(t_vars));
    game->vars->mlx = mlx_init();

    game->vars->win = mlx_new_window(game->vars->mlx, 382, 320, "cub3D");
    
    mlx_loop(game->vars->mlx);
}