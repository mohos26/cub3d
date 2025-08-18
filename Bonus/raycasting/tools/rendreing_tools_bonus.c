/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendreing_tools_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:12:14 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/18 13:46:28 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

t_image	*get_texture(t_game *data)
{
	int	hit_mx;
	int	hit_my;

	hit_mx = data->ray.final_hit_x / TILE;
	hit_my = data->ray.final_hit_y / TILE;
	if (data->ray.face_up)
		hit_my = (data->ray.final_hit_y - 1) / TILE;
	if (data->ray.face_left)
		hit_mx = (data->ray.final_hit_x - 1) / TILE;
	if (data->map[hit_my][hit_mx] == '2')
		return (&data->door_tex);
	if (data->ray.was_vertical)
	{
		if (data->ray.face_right)
			return (&data->tex.ea_tex);
		else
			return (&data->tex.we_tex);
	}
	else
	{
		if (data->ray.face_up)
			return (&data->tex.no_tex);
		else
			return (&data->tex.so_tex);
	}
}

double	get_x_offset(t_game *data)
{
	if (data->ray.was_vertical)
		return (fmod(data->ray.final_hit_y, TILE));
	else
		return (fmod(data->ray.final_hit_x, TILE));
}
