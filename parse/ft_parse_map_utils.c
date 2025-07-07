/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:43:02 by mhoussas          #+#    #+#             */
/*   Updated: 2025/07/07 19:09:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static bool ft_aid4(char c)
{
	if (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (true);
	return (false);
}

static bool ft_check_surrounded(int i, char *line, char *prev, char *next)
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

bool ft_validate_line(char *line, char *prev_line, char *next_line)
{
	int i;
	static bool player_flag;

	i = 0;
	while (line[i])
	{
		if (ft_aid4(line[i]))
		{
			if (line[i] != '0')
			{
				if (player_flag)
					return (false);
				player_flag = true;
			}
			if (!ft_check_surrounded(i, line, prev_line, next_line))
				return (false);
		}
		else if (!(line[i] == '1' || line[i] == ' '))
			return (false);
		i++;
	}
	if (!next_line && !player_flag)
		return (false);
	return (true);
}
