/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_check_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiturria <aiturria@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:00:33 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/22 15:35:52 by aiturria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_character(t_game *game, int y, int x)
{
	char	c;

	c = game->map->map2d[y][x];
	if (c == '0' || c == '1' || c == ' ' || c == 'D')
		return (1);
	if ((c == 'N' || c == 'S' || c == 'E' || c == 'W')
		&& (game->map->playery == 0) && (game->map->playerx == 0))
	{
		game->map->playery = y;
		game->map->playerx = x;
		return (1);
	}
	return (0);
}

static int	check_characters(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map->rows)
	{
		j = -1;
		while (++j < ft_strlen(game->map->map2d[i]) - 1)
		{
			if (!check_character(game, i, j))
				return (0);
		}
	}
	return (1);
}

static int	cb_check_surroundings(t_game *game, int i, int j)
{
	if (i <= 0)
		return (1);
	if (j <= 0)
		return (1);
	if (i >= game->map->rows - 1)
		return (1);
	if (j >= ft_strlen(game->map->map2d[i]) - 2)
		return (1);
	if (j >= ft_strlen(game->map->map2d[i - 1]) - 1)
		return (1);
	if (j >= ft_strlen(game->map->map2d[i + 1]) - 1)
		return (1);
	if (game->map->map2d[i - 1][j] == ' ')
		return (1);
	if (game->map->map2d[i][j - 1] == ' ')
		return (1);
	if (game->map->map2d[i + 1][j] == ' ')
		return (1);
	if (game->map->map2d[i][j + 1] == ' ')
		return (1);
	return (0);
}

static int	cb_map_is_closed(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < game->map->rows)
	{
		j = -1;
		while (++j < ft_strlen(game->map->map2d[i]) - 1)
		{
			c = game->map->map2d[i][j];
			if ((c == '0' || c == 'D'
					|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
				&& cb_check_surroundings(game, i, j))
				return (0);
		}
	}
	return (1);
}

void	cb_check_map(t_game *game)
{
	if (!check_characters(game))
		cb_error(game, "Error: incorrect character found");
	if (game->map->playerx == 0 && game->map->playery == 0)
		cb_error(game, "Error: no player found or map not closed");
	if (!cb_map_is_closed(game))
		cb_error(game, "Error: map is not closed");
	if (!cb_check_doors(game))
		cb_error(game, "Error: door has no exit or isn't between walls");
}
