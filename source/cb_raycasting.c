/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiturria <aiturria@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:52:48 by aiturria          #+#    #+#             */
/*   Updated: 2024/09/25 10:35:33 by aiturria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cb_position(float angle, float *first, float *step, int check)
{
	if (check)
	{
		if (angle > M_PI && angle < 2 * M_PI)
		{
			*first += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*first += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	cb_wallcheck(t_game *game, float x, float y, int pos)
{
	int	mapx;
	int	mapy;

	if (x < 0 || y < 0)
		return (0);
	mapx = floor(x / SIZE);
	mapy = floor(y / SIZE);
	if (mapx < 0 || mapy < 0 || mapy >= game->map->rows)
		return (0);
	if (mapx >= ft_strlen(game->map->map2d[mapy]))
		return (0);
	if (pos == 1 && (game->map->map2d[mapy - 1][mapx] == '1'
		|| game->map->map2d[mapy][mapx] == '1'
		|| game->map->map2d[mapy][mapx] == ' '))
		return (0);
	else if (pos == 2 && (game->map->map2d[mapy][mapx - 1] == '1'
		|| game->map->map2d[mapy][mapx] == '1'
		|| game->map->map2d[mapy][mapx] == ' '))
		return (0);
	return (1);
}

double	cb_gethorizontal(t_game *game, double rayangle)
{
	float	first_x;
	float	first_y;
	float	x_step;
	float	y_step;
	int		adjust;

	y_step = SIZE;
	x_step = SIZE / tan(rayangle);
	first_y = floor(game->pyr->pyry / SIZE) * SIZE;
	adjust = cb_position(rayangle, &first_y, &y_step, 1);
	x_step *= adjust;
	first_x = game->pyr->pyrx + (game->pyr->pyry - first_y) / tan(rayangle);
	while (cb_wallcheck(game, first_x, first_y, 1))
	{
		first_x += x_step;
		first_y += y_step;
	}
	game->ray->horizx = first_x;
	game->ray->horizy = first_y;
	return (sqrt(pow(first_x - game->pyr->pyrx, 2)
			+ pow(first_y - game->pyr->pyry, 2)));
}

double	cb_getvertical(t_game *game, double rayangle)
{
	float	first_x;
	float	first_y;
	float	x_step;
	float	y_step;
	int		adjust;

	x_step = SIZE;
	y_step = SIZE * tan(game->ray->angle);
	first_x = floor(game->pyr->pyrx / SIZE) * SIZE;
	adjust = cb_position(rayangle, &first_x, &x_step, 0);
	y_step *= adjust;
	first_y = game->pyr->pyry + (game->pyr->pyrx - first_x) * tan(rayangle);
	while (cb_wallcheck(game, first_x, first_y, 2))
	{
		first_x += x_step;
		first_y += y_step;
	}
	game->ray->vertx = first_x;
	game->ray->verty = first_y;
	return (sqrt(pow(first_x - game->pyr->pyrx, 2)
			+ pow(first_y - game->pyr->pyry, 2)));
}

void	cb_raycasting(t_game *game)
{
	double	horizontal;
	double	vertical;
	int		ray;

	ray = SCREEN_W;
	game->ray->angle = fmod((game->pyr->angle - (game->pyr->fovrad / 2)
				+ 2 * M_PI), 2 * M_PI);
	while (ray > 0)
	{
		game->ray->vertwall = 0;
		horizontal = cb_gethorizontal(game, game->ray->angle);
		vertical = cb_getvertical(game, game->ray->angle);
		if (horizontal <= vertical)
			game->ray->distance = horizontal;
		else
		{
			game->ray->distance = vertical;
			game->ray->vertwall = 1;
		}
		game->ray->index = ray;
		cb_drawing(game);
		game->ray->angle += (game->pyr->fovrad / SCREEN_W);
		game->ray->angle = fmod(game->ray->angle + 2 * M_PI, 2 * M_PI);
		ray--;
	}
}
