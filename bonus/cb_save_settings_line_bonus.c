/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_save_settings_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:26:25 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/19 16:57:50 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == ' ')
		i++;
	if (!str || !str[i])
		return (NULL);
	return (str + i);
}

static int	cb_save_texture(mlx_texture_t **texture, char *str)
{
	char	*newline;
	char	*path;

	if (!texture)
		return (0);
	newline = ft_strchr(str, '\n');
	if (!newline)
		return (0);
	path = ft_substr(str, 0, newline - str);
	if (!path)
		return (0);
	*texture = mlx_load_png(path);
	free(path);
	if (!*texture)
		return (0);
	return (1);
}

static int	*cb_get_color_array(char *str)
{
	int		*color_array;
	int		i;
	char	limit;

	color_array = (int *)ft_calloc(sizeof(int), 3);
	if (!color_array)
		return (NULL);
	i = -1;
	limit = ',';
	while (str && ++i < 3)
	{
		if (i == 2)
			limit = '\n';
		while (str && *str != limit)
		{
			if (!ft_isdigit(*str))
				return (free(color_array), NULL);
			color_array[i] = color_array[i] * 10 + (*str++ - '0');
		}
		if (str)
			str++;
	}
	if (!str)
		return (free(color_array), NULL);
	return (color_array);
}

static int	cb_save_color(unsigned int *color, char *str)
{
	int	*color_array;
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if ((str[i] == ',')
			&& (i == 0 || !ft_isdigit(str[i - 1]) || !ft_isdigit(str[i + 1])))
			return (0);
	}
	color_array = cb_get_color_array(str);
	if (!color_array)
		return (0);
	if (color_array[0] < 0 || color_array[1] < 0 || color_array[2] < 0
		|| color_array[0] > 255 || color_array[1] > 255 || color_array[2] > 255)
		return (free(color_array), 0);
	*color = 255 + (unsigned int)color_array[2] * 256;
	*color += (unsigned int)color_array[1] * 256 * 256;
	*color += (unsigned int)color_array[0] * 256 * 256 * 256;
	free(color_array);
	return (1);
}

int	cb_save_settings_line(t_game *game, char *line, int i, int fd)
{
	int	ok;

	if (!line || !line[0] || line[0] == '\n')
		return (0);
	ok = 0;
	if (!ft_strncmp("NO ", line, 3) && i == 0)
		ok = cb_save_texture(&game->texture->north, skip_spaces(line + 3));
	if (!ft_strncmp("SO ", line, 3) && i == 1)
		ok = cb_save_texture(&game->texture->south, skip_spaces(line + 3));
	if (!ft_strncmp("WE ", line, 3) && i == 2)
		ok = cb_save_texture(&game->texture->west, skip_spaces(line + 3));
	if (!ft_strncmp("EA ", line, 3) && i == 3)
		ok = cb_save_texture(&game->texture->east, skip_spaces(line + 3));
	if (!ft_strncmp("F ", line, 2) && i == 4)
		ok = cb_save_color(&game->map->rgb[COLOR_F], skip_spaces(line + 2));
	if (!ft_strncmp("C ", line, 2) && i == 5)
		ok = cb_save_color(&game->map->rgb[COLOR_C], skip_spaces(line + 2));
	if (!ok)
	{
		close(fd);
		cb_error(game, "Error: while processing the settings");
	}
	return (ok);
}
