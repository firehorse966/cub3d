/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_savemap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiturria <aiturria@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:36:12 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/22 15:34:28 by aiturria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cb_save_settings(t_game *game, int fd)
{
	int		i;
	int		n_lines;
	int		not_nl;
	char	*line;

	i = 0;
	n_lines = 0;
	line = get_next_line(fd);
	while (line && i < 6)
	{
		not_nl = cb_save_settings_line(game, line, i, fd);
		free(line);
		i += not_nl;
		line = get_next_line(fd);
		n_lines++;
	}
	if (!line)
	{
		close(fd);
		cb_error(game, "Error: not all settings were saved");
	}
	free(line);
	return (n_lines);
}

static int	cb_count_map_lines(t_game *game, int fd)
{
	char	*line;
	int		n_lines;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		close(fd);
		cb_error(game, "Error: map is empty");
	}
	n_lines = 0;
	while (line)
	{
		free(line);
		n_lines++;
		line = get_next_line(fd);
	}
	return (n_lines);
}

static void	cb_save_map2d(t_game *game, int fd,
					int n_set_lines, int n_map_lines)
{
	int		i;
	char	*line;

	game->map->map2d = (char **)ft_calloc(n_map_lines + 1, sizeof(char *));
	if (!game->map->map2d)
		cb_error(game, "Error: when allocating memory");
	line = get_next_line(fd);
	while (line && (n_set_lines-- > 0 || line[0] == '\n'))
	{
		free(line);
		line = get_next_line(fd);
	}
	i = -1;
	while (line && ++i < n_map_lines)
	{
		game->map->map2d[i] = line;
		line = get_next_line(fd);
	}
	if (line)
		cb_error(game, "Error: map has not been fully read");
	game->map->rows = n_map_lines;
}

void	cb_savemap(t_game *game, char *file)
{
	int	fd;
	int	n_setting_lines;
	int	n_map_lines;

	game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	game->texture = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!game->map || !game->texture)
		cb_error(NULL, "Error: memory allocation failure");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		cb_error(game, "Error: while opening a file");
	n_setting_lines = cb_save_settings(game, fd);
	n_map_lines = cb_count_map_lines(game, fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		cb_error(game, "Error: while opening a file");
	cb_save_map2d(game, fd, n_setting_lines, n_map_lines);
	close(fd);
	cb_check_map(game);
}
