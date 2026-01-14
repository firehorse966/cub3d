/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_drawing2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiturria <aiturria@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:16:51 by aiturria          #+#    #+#             */
/*   Updated: 2024/09/23 16:35:55 by aiturria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cb_paintboth(t_game *game, int top, int bottom)
{
	int			i;
	uint32_t	floor;
	uint32_t	ceiling;

	i = 0;
	floor = game->map->rgb[COLOR_F];
	ceiling = game->map->rgb[COLOR_C];
	if (game->red == 1)
	{
		floor = cb_shading(game, floor);
		ceiling = cb_shading(game, ceiling);
	}
	while (i < top)
		mlx_put_pixel(game->img, game->ray->index, i++, ceiling);
	i = bottom;
	while (i < SCREEN_H)
		mlx_put_pixel(game->img, game->ray->index, i++, floor);
}

int	cb_revbytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	cb_closedoor(t_game *game, int x, int y)
{
	int	pyrx;
	int	pyry;

	pyrx = (int)round(game->pyr->pyrx / SIZE);
	pyry = (int)round(game->pyr->pyry / SIZE);
	if ((game->map->map2d[pyry][pyrx] != 'd'
		&& game->map->map2d[pyry + 1][pyrx] != 'd'
		&& game->map->map2d[pyry - 1][pyrx] != 'd'
		&& game->map->map2d[pyry][pyrx + 1] != 'd'
		&& game->map->map2d[pyry][pyrx - 1] != 'd'))
	{
		while (game->map->map2d[y])
		{
			x = 0;
			while (game->map->map2d[y][x])
			{
				if (game->map->map2d[y][x] == 'd')
					game->map->map2d[y][x] = 'D';
				x++;
			}
			y++;
		}
	}
}

void	cb_opendoor2(t_game *game, int doorx, int doory)
{
	int	pyrx;
	int	pyry;

	pyrx = game->pyr->pyrx / SIZE;
	pyry = game->pyr->pyry / SIZE;
	if (((abs(doorx - pyrx) <= 1 && doory == pyry)
			|| (abs(doory - pyry) <= 1 && doorx == pyrx))
		&& game->map->map2d[doory][doorx] == 'D')
	{
		game->map->map2d[doory][doorx] = 'd';
		game->open = 1;
	}
}

void	cb_opendoor(t_game *game)
{
	int	doorx;
	int	doory;
	int	angle1;
	int	angle2;

	angle1 = (int)(game->ray->angle * 100);
	angle2 = (int)(game->pyr->angle * 100);
	if ((game->ray->doorx == 1 || game->ray->doory == 1) && angle1 == angle2)
	{
		if (game->ray->vertwall == 1)
		{
			doorx = game->ray->vertx / SIZE;
			doory = game->ray->verty / SIZE;
			if (game->map->map2d[doory][doorx] != 'D')
				doorx = (game->ray->vertx / SIZE) - 1;
		}
		else
		{
			doorx = game->ray->horizx / SIZE;
			doory = game->ray->horizy / SIZE;
			if (game->map->map2d[doory][doorx] != 'D')
				doory = (game->ray->horizy / SIZE) - 1;
		}
		cb_opendoor2(game, doorx, doory);
	}
}
