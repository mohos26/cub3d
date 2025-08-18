/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_wall_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:46:32 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/18 15:19:31 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

int	found_wall_h(int map_x, int map_y, int *is_wall_found, t_game *data)
{
	int	is_hit;

	is_hit = data->map[map_y][map_x] == '1' || (data->map[map_y][map_x] == '2'
			&& !door_is_open_at(data, map_x, map_y));
	if (map_y >= 0 && map_x >= 0 && map_y < data->map_height
		&& map_x < data->map_width && is_hit)
	{
		*is_wall_found = 1;
		data->ray.h_hit_x = data->ray.next_x;
		data->ray.h_hit_y = data->ray.next_y;
		data->ray.h_distance = r_distance(data->player.x, data->player.y,
				data->ray.h_hit_x, data->ray.h_hit_y);
		return (0);
	}
	return (1);
}

int	found_wall_v(int map_x, int map_y, int *is_wall_found, t_game *data)
{
	int	is_hit;

	is_hit = data->map[map_y][map_x] == '1' || (data->map[map_y][map_x] == '2'
			&& !door_is_open_at(data, map_x, map_y));
	if (map_y >= 0 && map_x >= 0 && map_y < data->map_height
		&& map_x < data->map_width && is_hit)
	{
		*is_wall_found = 1;
		data->ray.v_hit_x = data->ray.next_x;
		data->ray.v_hit_y = data->ray.next_y;
		data->ray.v_distance = r_distance(data->player.x, data->player.y,
				data->ray.v_hit_x, data->ray.v_hit_y);
		return (0);
	}
	return (1);
}
