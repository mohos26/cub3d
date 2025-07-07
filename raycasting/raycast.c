/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:13:44 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void hiro_intersec_check(t_game *data, int map_x, int map_y)
{
	int is_wall_found;

	is_wall_found = 0;
	while (data->ray.next_x >= 0 && data->ray.next_x < data->map_width * TILE && data->ray.next_y >= 0 && data->ray.next_y < data->map_height * TILE)
	{
		map_x = (int)data->ray.next_x / TILE;
		map_y = (int)data->ray.next_y / TILE;
		if (data->ray.face_up)
			map_y = (int)((data->ray.next_y - 1) / TILE);
		if (map_y >= 0 && map_x >= 0 && map_y < data->map_height && map_x < data->map_width && data->map[map_y][map_x] == '1')
		{
			is_wall_found = 1;
			data->ray.h_hit_x = data->ray.next_x;
			data->ray.h_hit_y = data->ray.next_y;
			data->ray.h_distance = r_distance(data->player.x, data->player.y,
											  data->ray.h_hit_x, data->ray.h_hit_y);
			break;
		}
		data->ray.next_x += data->ray.x_step;
		data->ray.next_y += data->ray.y_step;
	}
	if (!is_wall_found)
		data->ray.h_distance = INFINITY;
}

void hiro_intersec(double r_angle, t_game *data)
{
	int map_x;
	int map_y;

	map_x = 0;
	map_y = 0;
	data->ray.y_intersec = floor(data->player.y / TILE) * TILE;
	if (data->ray.face_down)
		data->ray.y_intersec += TILE;
	data->ray.x_intersec = data->player.x + (data->ray.y_intersec - data->player.y) / tan(r_angle);
	data->ray.y_step = TILE;
	if (data->ray.face_up)
		data->ray.y_step *= -1;
	data->ray.x_step = TILE / tan(r_angle);
	if ((data->ray.face_right && data->ray.x_step < 0) || (data->ray.face_left && data->ray.x_step > 0))
		data->ray.x_step *= -1;
	data->ray.next_x = data->ray.x_intersec;
	data->ray.next_y = data->ray.y_intersec;
	hiro_intersec_check(data, map_x, map_y);
}

void vert_intersec_check(t_game *data, int map_x, int map_y)
{
	int is_wall_found;

	is_wall_found = 0;
	while (data->ray.next_x >= 0 && data->ray.next_x < data->map_width * TILE && data->ray.next_y >= 0 && data->ray.next_y < data->map_height * TILE)
	{
		map_x = (int)data->ray.next_x / TILE;
		map_y = (int)data->ray.next_y / TILE;
		if (data->ray.face_left)
			map_x = (int)((data->ray.next_x - 1) / TILE);
		if (map_y >= 0 && map_x >= 0 && map_y < data->map_height && map_x < data->map_width && data->map[map_y][map_x] == '1')
		{
			is_wall_found = 1;
			data->ray.v_hit_x = data->ray.next_x;
			data->ray.v_hit_y = data->ray.next_y;
			data->ray.v_distance = r_distance(data->player.x, data->player.y,
											  data->ray.v_hit_x, data->ray.v_hit_y);
			break;
		}
		data->ray.next_x += data->ray.x_step;
		data->ray.next_y += data->ray.y_step;
	}
	if (!is_wall_found)
		data->ray.v_distance = INFINITY;
}

void vert_intersec(double r_angle, t_game *data)
{
	int map_x;
	int map_y;

	map_x = 0;
	map_y = 0;
	data->ray.x_intersec = floor(data->player.x / TILE) * TILE;
	if (data->ray.face_right)
		data->ray.x_intersec += TILE;
	data->ray.y_intersec = data->player.y + ((data->ray.x_intersec - data->player.x) * tan(r_angle));
	data->ray.x_step = TILE;
	if (data->ray.face_left)
		data->ray.x_step *= -1;
	data->ray.y_step = TILE * tan(r_angle);
	if ((data->ray.face_up && data->ray.y_step > 0) || (data->ray.face_down && data->ray.y_step < 0))
		data->ray.y_step *= -1;
	data->ray.next_x = data->ray.x_intersec;
	data->ray.next_y = data->ray.y_intersec;
	vert_intersec_check(data, map_x, map_y);
}

void cast_rays(double r_angle, t_game *data)
{
	where_ray_face(r_angle, data);
	hiro_intersec(r_angle, data);
	vert_intersec(r_angle, data);
	if (data->ray.h_distance <= data->ray.v_distance)
	{
		data->ray.final_hit_x = data->ray.h_hit_x;
		data->ray.final_hit_y = data->ray.h_hit_y;
		data->ray.final_distance = data->ray.h_distance;
		data->ray.was_vertical = 0; // NOTE: this just to for simple shadow effect|| vertival walls will be gray || horizontal will be white
	}
	else
	{
		data->ray.final_hit_x = data->ray.v_hit_x;
		data->ray.final_hit_y = data->ray.v_hit_y;
		data->ray.final_distance = data->ray.v_distance;
		data->ray.was_vertical = 1; // NOTE: the opposite
	}
}
