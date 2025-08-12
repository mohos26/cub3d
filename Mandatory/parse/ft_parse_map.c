/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:12:02 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/07 14:39:42 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*ft_skip_empty_lines(int fd)
{
	char	*line;

	line = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (*line != '\n')
			break ;
	}
	return (line);
}

static bool	ft_read_next_line(char **line, bool end_line, int fd)
{
	if (!end_line)
	{
		*line = get_next_line(fd);
		if (!*line || **line == '\n')
			return (false);
	}
	else
		*line = NULL;
	return (true);
}

static char	*ft_local_init(int fd, char **next, char **prev, bool *end_line)
{
	*end_line = false;
	*prev = NULL;
	*next = NULL;
	return (ft_skip_empty_lines(fd));
}

bool	ft_parse_map(t_game *data, int fd)
{
	char	*line;
	bool	end_line;
	char	*prev_line;
	char	*next_line;

	line = ft_local_init(fd, &next_line, &prev_line, &end_line);
	if (!line)
		return (false);
	while (true)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		else
			end_line = true;
		if (!ft_read_next_line(&next_line, end_line, fd)
			|| !ft_validate_line(line, prev_line, next_line))
			return (false);
		ft_append_map(data, line);
		prev_line = line;
		if (!next_line)
			break ;
		line = next_line;
	}
	return (true);
}
