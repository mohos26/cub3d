/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:21:35 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/15 15:34:02 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

int	is_wall(double x, double y, t_game *data)
{
	int		wx;
	int		wy;
	char	c;

	wx = floor(x / TILE);
	wy = floor(y / TILE);
	if (wx < 0 || wx >= data->map_width || wy < 0 || wy >= data->map_height)
		return (1);
	c = data->map[wy][wx];
	if (c == '1')
		return (1);
	if (c == '2')
	{
		int id = get_door_idx(data, wx, wy);
		if (id >= 0)
			return (!data->doors[id].open);
		return (1);
	}
	return (0);
}

int	is_collesion(double x, double y, t_game *data)
{
	if (is_wall(x + RADIUS, y, data) || is_wall(x - RADIUS, y, data)
		|| is_wall(x, y + RADIUS, data) || is_wall(x, y - RADIUS, data)
		|| is_wall(x, y, data))
		return (1);
	return (0);
}
