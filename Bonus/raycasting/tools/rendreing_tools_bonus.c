/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendreing_tools_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:12:14 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/15 15:14:49 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

t_image	*get_texture(t_game *data)
{
	int hit_mx = (int)(data->ray.final_hit_x / TILE);
	int hit_my = (int)(data->ray.final_hit_y / TILE);

	if (hit_mx >= 0 && hit_my >= 0 && hit_mx < data->map_width && hit_my < data->map_height)
	{
		if (data->map[hit_my][hit_mx] == '2')
		{
			puts("*");
			return (&data->door_tex);
		}
	}
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
