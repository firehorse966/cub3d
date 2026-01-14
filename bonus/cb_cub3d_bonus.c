/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cub3d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:49:07 by aiturria          #+#    #+#             */
/*   Updated: 2024/09/23 19:29:26 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cb_error(t_game *game, char *str)
{
	while (*str)
		write (2, str++, 1);
	cb_freeall(game);
	exit (EXIT_FAILURE);
}

void	cb_free_textures(t_game *game)
{
	int	i;

	if (!game || !game->texture)
		return ;
	i = 0;
	while (i < 15 && game->texture->shotgun[i])
		mlx_delete_texture(game->texture->shotgun[i++]);
	i = 0;
	while (i < 7 && game->texture->opening[i])
		mlx_delete_texture(game->texture->opening[i++]);
	if (game->texture->north)
		mlx_delete_texture(game->texture->north);
	if (game->texture->south)
		mlx_delete_texture(game->texture->south);
	if (game->texture->east)
		mlx_delete_texture(game->texture->east);
	if (game->texture->west)
		mlx_delete_texture(game->texture->west);
	if (game->texture->door1)
		mlx_delete_texture(game->texture->door1);
	free(game->texture);
}

void	cb_freeall(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (game->map && game->map->map2d && game->map->map2d[i])
		free(game->map->map2d[i++]);
	if (game->map->map2d)
		free(game->map->map2d);
	if (game->map)
		free(game->map);
	if (game->pyr)
		free(game->pyr);
	if (game->ray)
		free(game->ray);
	if (game->mlx42)
	{
		mlx_delete_image(game->mlx42, game->img);
		mlx_close_window(game->mlx42);
		mlx_terminate(game->mlx42);
	}
	cb_free_textures(game);
	free(game);
}

static int	correct_extension(const char *s1, const char *s2)
{
	const char	*s;
	int			len;

	s = ft_strrchr(s1, '.');
	if (!s)
		return (0);
	len = ft_strlen(s);
	if (len < ft_strlen(s2))
		len = ft_strlen(s2);
	return (!ft_strncmp(s, s2, len));
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		cb_error(NULL, "Error: wrong number of arguments");
	if (!correct_extension(argv[1], ".cub"))
		cb_error(NULL, "Error: wrong file extension (.cub)");
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		cb_error(NULL, "Error: memory allocation failure");
	cb_savemap(game, argv[1]);
	cb_initgame(game);
	cb_freeall(game);
	ft_printf("exit");
	exit(EXIT_SUCCESS);
}
