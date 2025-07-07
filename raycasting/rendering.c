/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:14:41 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void draw_wall(double wall_top, double wall_bouttom, t_game *data, double x)
{
	int y;

	y = wall_top;
	while (y <= wall_bouttom)
	{
		if (data->ray.was_vertical)
			put_pixel_to_image(&data->image, x, y, 14540253);
		else
			put_pixel_to_image(&data->image, x, y, 16777215);
		y++;
	}
}

void rendring3d(t_game *data, double r_angle, int i)
{
	double new_angle;
	double ray_angle_diff;
	double corrected_distance;
	double distance_to_plan;

	new_angle = (FOV / 2) * (M_PI / 180);
	distance_to_plan = (WIN_WIDTH / 2) / tan(new_angle);
	ray_angle_diff = (r_angle - data->player.angle);
	corrected_distance = data->ray.final_distance * cos(ray_angle_diff);
	data->render.wall_height = (TILE / corrected_distance) * distance_to_plan;
	if (data->render.wall_height > WIN_HEIGHT)
		data->render.wall_height = WIN_HEIGHT;
	data->render.wall_top = (WIN_HEIGHT / 2) - (data->render.wall_height / 2);
	data->render.wall_bottom = (WIN_HEIGHT / 2) + (data->render.wall_height / 2);
	draw_wall(data->render.wall_top, data->render.wall_bottom, data, i);
}
