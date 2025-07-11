/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:14:41 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/11 14:42:44 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void draw_wall(double wall_top, double wall_bouttom, t_game *data, double x)
{
	int wall_height = wall_bouttom - wall_top + 1;
	for (int y = wall_top; y <= wall_bouttom; y++)
	{
		double sample_pos = (y - wall_top) / (double)wall_height;
		int tex_y = (int)(sample_pos * data->textures.tex_h);

		// address into texture data buffer:
		char *pixel = data->textures.curr_tex_data
					+ (tex_y * data->textures.curr_line)
					+ (data->textures.tex_x * (data->textures.curr_bpp / 8));
		int color = *(int *)pixel;  // assuming endian matches

		put_pixel_to_image(&data->image, x, y, color);
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
