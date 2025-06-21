/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene_data_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:20:08 by mhoussas          #+#    #+#             */
/*   Updated: 2025/06/21 21:29:57 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static bool	ft_set_texture_path(t_data *ptr, char *key, char *value)
{
	if (!ft_valid_file(value))
		return (false);
	if (!ft_strcmp(key, "NO") && !ptr->img_no)
		ptr->img_no = value;
	else if (!ft_strcmp(key, "SO") && !ptr->img_so)
		ptr->img_so = value;
	else if (!ft_strcmp(key, "WE") && !ptr->img_we)
		ptr->img_we = value;
	else if (!ft_strcmp(key, "EA") && !ptr->img_ea)
		ptr->img_ea = value;
	else
		return (false);
	return (true);
}

static void	ft_append_rgb(int *count, bool *flag, int *color, int *n)
{
	(*count)++;
	*flag = true;
	*color = (*color << 8) + *n;
	*n = 0;
}

static int	ft_parse_rgb_string(char *s)
{
	int		n;
	bool	flag;
	int		count;
	int		color;

	(true, n = 0, flag = false, count = 0, color = 0);
	while (*s)
	{
		if (ft_isdigit(*s))
		{
			flag = false;
			n = n * 10 + *s - 48;
			if (n > 255)
				return (-1);
		}
		else if (*s == ',' && !flag && count < 2)
			ft_append_rgb(&count, &flag, &color, &n);
		else
			return (-1);
		s++;
	}
	if (flag || count != 2)
		return (-1);
	return ((color << 8) + n);
}

static bool	ft_set_color_value(t_data *ptr, char *key, char *value)
{
	int	color;

	color = ft_parse_rgb_string(value);
	if (color < 0)
		return (false);
	if (!ft_strcmp(key, "F") && ptr->floor_color < 0)
		ptr->floor_color = color;
	else if (!ft_strcmp(key, "C") && ptr->ceil_color < 0)
		ptr->ceil_color = color;
	else
		return (false);
	return (true);
}

bool	ft_parse_instruction(t_data *ptr, char *s)
{
	char		*key;
	char		*value;

	(true, key = NULL, value = NULL);
	if (s[ft_strlen(s) - 1] == '\n')
		s[ft_strlen(s) - 1] = '\0';
	while (*s)
	{
		if (*s != ' ')
			key = ft_append_str(key, *s);
		else
		{
			value = ft_strdup(s);
			break ;
		}
		s++;
	}
	if (!key || !value || *value != ' ')
		return (false);
	while (*value && *value == ' ')
		value++;
	if (!ft_set_texture_path(ptr, key, value)
		&& !ft_set_color_value(ptr, key, value))
		return (false);
	return (true);
}
