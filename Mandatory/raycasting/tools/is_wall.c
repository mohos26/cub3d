/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:21:35 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/01 11:14:39 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	is_wall(double x, double y, t_game *data)
{
	int	wx;
	int	wy;

	wx = floor(x / TILE);
	wy = floor(y / TILE);
	if (wx < 0 || wx >= data->map_width || wy < 0 || wy >= data->map_height)
		return (1);
	return (data->map[wy][wx] == '1');
}

int	is_collesion(double x, double y, t_game *data)
{
	if (is_wall(x + RADIUS, y, data) || is_wall(x - RADIUS, y, data)
		|| is_wall(x, y + RADIUS, data) || is_wall(x, y - RADIUS, data)
		|| is_wall(x, y, data))
		return (1);
	return (0);
}
