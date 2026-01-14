/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_shotgun_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiturria <aiturria@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:52:51 by aiturria          #+#    #+#             */
/*   Updated: 2024/09/23 13:22:27 by aiturria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cb_paintgun(t_game *game, mlx_texture_t *texture, int newx, int newy)
{
	uint32_t	*pixel;
	uint32_t	color;
	uint32_t	i;
	uint32_t	j;

	pixel = (uint32_t *)texture->pixels;
	newx = (SCREEN_W / 2) - (texture->width / 2);
	newy = SCREEN_H - texture->height;
	i = 0;
	while (i < texture->height)
	{
		j = 0;
		while (j < texture->width)
		{
			color = cb_revbytes(pixel[i * texture->width + j]);
			if (game->red == 1)
				color = cb_shading(game, color);
			if ((color & 0xFF000000) != 0x00000000)
				mlx_put_pixel(game->img, newx + j, newy + i, color);
			j++;
		}
		i++;
	}
}

void	cb_shooting(t_game *game)
{
	double	time;
	int		frame;

	if (!game->shoot)
		return (cb_paintgun(game, game->texture->shotgun[0], 0, 0));
	if (game->time == 0)
		game->time = mlx_get_time();
	time = mlx_get_time() - game->time;
	frame = (int)(time * 10);
	if (frame >= 15)
	{
		game->shoot = false;
		game->time = 0;
	}
	else
		cb_paintgun(game, game->texture->shotgun[frame], 0, 0);
}

void	cb_opening(t_game *game)
{
	double	time;
	int		frame;

	if (!game->open)
		return ;
	if (game->time == 0)
		game->time = mlx_get_time();
	time = mlx_get_time() - game->time;
	frame = (int)(time * 7);
	if (frame >= 7)
	{
		game->open = false;
		game->time = 0;
	}
	else
		cb_paintgun(game, game->texture->opening[frame], 0, 0);
}

void	cb_loadshotgun(t_game *game)
{
	char		*shotgun[15];
	int			i;

	i = 0;
	shotgun[0] = "./images/shotgun1.png";
	shotgun[1] = "./images/shotgun2.png";
	shotgun[2] = "./images/shotgun3.png";
	shotgun[3] = "./images/shotgun4.png";
	shotgun[4] = "./images/shotgun5.png";
	shotgun[5] = "./images/shotgun6.png";
	shotgun[6] = "./images/shotgun7.png";
	shotgun[7] = "./images/shotgun8.png";
	shotgun[8] = "./images/shotgun9.png";
	shotgun[9] = "./images/shotgun10.png";
	shotgun[10] = "./images/shotgun11.png";
	shotgun[11] = "./images/shotgun12.png";
	shotgun[12] = "./images/shotgun13.png";
	shotgun[13] = "./images/shotgun14.png";
	shotgun[14] = "./images/shotgun15.png";
	while (i < 15)
	{
		game->texture->shotgun[i] = mlx_load_png(shotgun[i]);
		if (!game->texture->shotgun[i++])
			cb_error(game, "Error: loading MLX texture");
	}
}

void	cb_loadtextures(t_game *game)
{
	char		*opening[7];
	int			i;

	i = 0;
	opening[0] = "./images/opening11.png";
	opening[1] = "./images/opening12.png";
	opening[2] = "./images/opening13.png";
	opening[3] = "./images/opening14.png";
	opening[4] = "./images/opening15.png";
	opening[5] = "./images/opening16.png";
	opening[6] = "./images/opening17.png";
	while (i < 7)
	{
		game->texture->opening[i] = mlx_load_png(opening[i]);
		if (!game->texture->opening[i++])
			cb_error(game, "Error: loading MLX texture");
	}
	game->texture->door1 = mlx_load_png("./images/metal5.png");
	if (game->texture->door1 == NULL)
		cb_error(game, "Error: loading MLX texture");
	cb_loadshotgun(game);
}
