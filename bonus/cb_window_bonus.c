/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_window_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiturria <aiturria@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:13:51 by aiturria          #+#    #+#             */
/*   Updated: 2024/09/22 15:26:15 by aiturria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cb_newwindow(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	if (game->img != NULL)
		mlx_delete_image(game->mlx42, game->img);
	game->img = mlx_new_image(game->mlx42, SCREEN_W, SCREEN_H);
	cb_raycasting(game);
	if (!game->open)
		cb_shooting(game);
	cb_closedoor(game, 0, 0);
	if (game->minimap)
		cb_paintmap(game);
	cb_opening(game);
	mlx_image_to_window(game->mlx42, game->img, 0, 0);
}

void	cb_playerangle(t_game *game)
{
	char	c;

	c = game->map->map2d[game->map->playery][game->map->playerx];
	if (c == 'N')
		game->pyr->angle = M_PI / 2;
	if (c == 'S')
		game->pyr->angle = 3 * M_PI / 2;
	if (c == 'E')
		game->pyr->angle = 0;
	if (c == 'W')
		game->pyr->angle = M_PI;
	game->pyr->pyrx = (game->map->playerx * SIZE) + SIZE / 2;
	game->pyr->pyry = (game->map->playery * SIZE) + SIZE / 2;
	game->pyr->fovrad = (FOV * M_PI / 180);
	game->shoot = 0;
	game->open = 0;
	game->time = 0;
	game->minimap = 1;
	game->red = 0;
}

void	cb_keypress2(mlx_key_data_t keydata, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_PRESS))
		game->shoot = true;
	else if (keydata.key == MLX_KEY_M && (keydata.action == MLX_PRESS))
		game->minimap = !game->minimap;
	else if (keydata.key == MLX_KEY_R && (keydata.action == MLX_PRESS))
		game->red = !game->red;
}

void	cb_mousepointer(void *data)
{
	t_game	*game;

	game = data;
	mlx_get_mouse_pos(game->mlx42, &game->pyr->mousex, &game->pyr->mousey);
	game->pyr->angle -= (double)(game->pyr->mousex - (SCREEN_W / 2)) * 0.0005;
	mlx_set_mouse_pos(game->mlx42, (SCREEN_W / 2), (SCREEN_H / 2));
	if (mlx_is_mouse_down(game->mlx42, MLX_MOUSE_BUTTON_LEFT) == true)
		game->shoot = true;
}

void	cb_initgame(t_game *game)
{
	if (FOV > 179 || FOV < 1)
		cb_error(game, "Error: parameters outside allowed range");
	game->pyr = malloc(sizeof(t_player));
	game->ray = malloc(sizeof(t_ray));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx42 = mlx_init(SCREEN_W, SCREEN_H, "cub 3D", true);
	if (!game->mlx42)
		cb_error(game, "Error: MLX42 window did not open");
	cb_playerangle(game);
	cb_loadtextures(game);
	mlx_key_hook(game->mlx42, &cb_keypress, game);
	mlx_loop_hook(game->mlx42, &cb_newwindow, game);
	mlx_set_cursor_mode(game->mlx42, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(game->mlx42, (void *)cb_mousepointer, game);
	mlx_loop(game->mlx42);
}
