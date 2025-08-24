/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:17:54 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/24 16:06:09 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static bool	ft_check_finish(t_game *data)
{
	if (data->colors.ceiling_c < 0 || data->colors.floor_c < 0)
		return (false);
	else if (!data->tex.ea || !data->tex.so || !data->tex.we || !data->tex.no)
		return (false);
	return (true);
}

static void	ft_local_init(t_game *data, bool *start)
{
	*start = true;
	data->map = NULL;
	data->tex.ea = NULL;
	data->tex.no = NULL;
	data->tex.so = NULL;
	data->tex.we = NULL;
	data->colors.ceiling_c = -1;
	data->colors.floor_c = -1;
}

static bool	ft_finalize_scene(t_game *data, bool start, int fd)
{
	if (start)
		return (ft_error("Empty File", fd));
	if (!ft_check_finish(data))
		return (ft_error("Missing or incomplete texture/color data", fd));
	if (!ft_parse_map(data, fd))
		return (ft_error("Failed to parse the map layout", fd));
	return (close(fd), true);
}

bool	ft_init_scene_data(char *file_name, t_game *data)
{
	int		fd;
	char	*line;
	bool	start;

	ft_local_init(data, &start);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_error("Failed to open cub file", -1));
	while (true)
	{
		if (ft_check_finish(data))
			break ;
		line = get_next_line(fd);
		if (!line)
			break ;
		start = false;
		if (*line == '\n')
			continue ;
		if (!ft_parse_instruction(data, line))
			return (close(fd), false);
	}
	return (ft_finalize_scene(data, start, fd));
}
