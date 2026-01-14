/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:15:59 by aiturria          #+#    #+#             */
/*   Updated: 2024/09/18 17:10:49 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	cb_getwallhit(t_game *game, mlx_texture_t *texture)
{
	double	wallhit;

	if (game->ray->vertwall == 1)
	{
		wallhit = fmodf((game->ray->verty / SIZE), 1.0) * texture->width;
		if (game->ray->angle > M_PI / 2 && game->ray->angle < 1.5 * M_PI)
			wallhit = texture->width - wallhit;
	}
	else
	{
		wallhit = fmodf((game->ray->horizx / SIZE), 1.0) * texture->width;
		if (game->ray->angle > M_PI && game->ray->angle < 2 * M_PI)
			wallhit = texture->width - wallhit;
	}
	return (wallhit);
}

mlx_texture_t	*cb_findtexture(t_game *game)
{
	if (game->ray->vertwall == 1)
	{
		if (game->ray->angle > M_PI / 2 && game->ray->angle < 1.5 * M_PI)
			return (game->texture->west);
		else
			return (game->texture->east);
	}
	else
	{
		if (game->ray->angle < M_PI)
			return (game->texture->north);
		else
			return (game->texture->south);
	}
}

uint32_t	cb_shading(t_game *game, uint32_t color)
{
	double		shading_factor;
	int			red;
	int			green;
	int			blue;

	shading_factor = 1.0 - (game->ray->distance / 150);
	if (shading_factor < 0.2)
		shading_factor = 0.2;
	red = ((color >> 24) & 0xFF) * shading_factor;
	green = ((color >> 16) & 0xFF) * shading_factor;
	blue = ((color >> 8) & 0xFF) * shading_factor;
	color = (red << 24) | (green << 16) | (blue << 8) | (color & 0xFF);
	return (color);
}

void	cb_paintwall(t_game *game, int top, int bottom, uint32_t color)
{
	mlx_texture_t	*texture;
	uint32_t		*pixel;
	double			wallhit;
	double			pixely;
	double			move;

	texture = cb_findtexture(game);
	pixel = (uint32_t *)texture->pixels;
	wallhit = cb_getwallhit(game, texture);
	move = texture->height / game->ray->height;
	pixely = (top - (SCREEN_H / 2) + (game->ray->height / 2)) * move;
	if (pixely < 0)
		pixely = 0;
	while (top < bottom)
	{
		color = cb_revbytes(pixel[(int)wallhit + (int)pixely * texture->width]);
		color = cb_shading(game, color);
		mlx_put_pixel(game->img, game->ray->index, top++, color);
		pixely += move;
	}
}

void	cb_drawing(t_game *game)
{
	double	top;
	double	bottom;

	game->ray->distance = cos(game->ray->angle - game->pyr->angle)
		* game->ray->distance;
	game->ray->height = (SIZE / game->ray->distance) * ((SCREEN_W / 2)
			/ tan(game->pyr->fovrad / 2));
	top = (SCREEN_H / 2) - (game->ray->height / 2);
	if (top < 0)
		top = 0;
	bottom = (SCREEN_H / 2) + (game->ray->height / 2);
	if (bottom > SCREEN_H)
		bottom = SCREEN_H;
	cb_paintwall(game, top, bottom, 0);
	cb_paintboth(game, top, bottom);
}
