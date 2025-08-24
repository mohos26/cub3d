/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:43:02 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/24 13:33:12 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

static bool	ft_aid4(char c)
{
	if (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E' || c == 'D')
		return (true);
	return (false);
}

static bool	ft_check_surrounded(int i, char *line, char *prev, char *next)
{
	if (i)
	{
		if (!line[i + 1] || line[i + 1] == ' ' || line[i - 1] == ' ')
			return (false);
	}
	else
		return (false);
	if (prev)
	{
		if (i > (int)ft_strlen(prev) - 1 || prev[i] == ' ')
			return (false);
	}
	else
		return (false);
	if (next)
	{
		if (i > (int)ft_strlen(next) - 1 || next[i] == ' ')
			return (false);
	}
	else
		return (false);
	return (true);
}

static bool	ft_aid(int i, char *line, char *prev, char *next)
{
	if (line[i] != 'D')
		return (true);
	if (i && line[i - 1] == '1' && line[i + 1] == '1')
		return (true);
	if (i < (int)ft_strlen(prev) && prev[i] == '1'
		&& i < (int)ft_strlen(next) && next[i] == '1')
		return (true);
	return (false);
}

bool	ft_validate_line(char *line, char *prev_line, char *next_line)
{
	static bool	player_flag;
	int			i;

	if (*line == '\n')
		return (false);
	i = 0;
	while (line[i])
	{
		if (ft_aid4(line[i]))
		{
			if (line[i] != '0' && line[i] != 'D')
			{
				if (player_flag)
					return (false);
				player_flag = true;
			}
			if (!ft_check_surrounded(i, line, prev_line, next_line)
				|| !ft_aid(i, line, prev_line, next_line))
				return (false);
		}
		else if (!(line[i] == '1' || line[i] == ' '))
			return (false);
		i++;
	}
	return (next_line || player_flag);
}
