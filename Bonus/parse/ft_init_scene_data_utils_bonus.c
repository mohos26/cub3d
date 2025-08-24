/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene_data_utils_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:20:08 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/24 09:51:53 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

static bool	ft_set_texture_path(t_game *data, char *key, char *value)
{
	if (!ft_valid_file(value))
		return (false);
	if (!ft_strcmp(key, "NO") && !data->tex.no)
		data->tex.no = value;
	else if (!ft_strcmp(key, "SO") && !data->tex.so)
		data->tex.so = value;
	else if (!ft_strcmp(key, "WE") && !data->tex.we)
		data->tex.we = value;
	else if (!ft_strcmp(key, "EA") && !data->tex.ea)
		data->tex.ea = value;
	else
		return (false);
	return (true);
}

static bool	ft_set_color_value(t_game *data, char *key, char *value)
{
	int	color;

	color = ft_parse_rgb_string(value);
	if (color < 0)
		return (false);
	if (!ft_strcmp(key, "F") && data->colors.floor_c < 0)
		data->colors.floor_c = color;
	else if (!ft_strcmp(key, "C") && data->colors.ceiling_c < 0)
	{
		data->colors.ceiling_c = color;
	}
	else
		return (false);
	return (true);
}

static bool	ft_handle_instruction(t_game *data, char *key, char *value)
{
	if (!key || !value || *value != ' ')
		return (ft_error("Invalid instruction format. Expected '<key> <value>'",
				2));
	while (*value && *value == ' ')
		value++;
	if (!ft_set_texture_path(data, key, value)
		&& !ft_set_color_value(data, key, value))
		return (ft_error("Unknown or malformed instruction key/value", 2));
	return (true);
}

bool	ft_parse_instruction(t_game *data, char *s)
{
	char	*key;
	char	*value;

	while (*s == ' ')
		s++;
	(true, key = NULL, value = NULL);
	if (s[ft_strlen(s) - 1] == '\n')
		s[ft_strlen(s) - 1] = '\0';
	while (*s)
	{
		if (*s && *s != ' ')
			key = ft_append_str(key, *s);
		else
		{
			value = ft_strdup(s);
			break ;
		}
		s++;
	}
	return (ft_handle_instruction(data, key, value));
}
