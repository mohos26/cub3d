/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:17:54 by mhoussas          #+#    #+#             */
/*   Updated: 2025/06/20 15:37:38 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static bool	ft_check_finish(t_data *ptr)
{
	if (ptr->ceil_color < 0 || ptr->floor_color < 0)
		return (false);
	else if (!ptr->img_ea || !ptr->img_so || !ptr->img_we || !ptr->img_no)
		return (false);
	return (true);
}

static t_data	*ft_local_init(void)
{
	t_data	*res;

	res = ft_calloc(sizeof(t_data));
	res->img_ea = NULL;
	res->img_no = NULL;
	res->img_so = NULL;
	res->img_we = NULL;
	res->ceil_color = -1;
	res->floor_color = -1;
	return (res);
}

t_data	*ft_init_scene_data(char *file_name)
{
	int		fd;
	char	*line;
	t_data	*res;

	res = ft_local_init();
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line == '\n')
			continue ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_check_finish(res) || !ft_parse_instruction(res, line))
			return (close(fd), NULL);
	}
	close(fd);
	if (!ft_check_finish(res))
		return (NULL);
	return (res);
}
