/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendreing_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:12:14 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/01 17:14:32 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

t_image	*get_texture(t_game *data)
{
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
