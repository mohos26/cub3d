/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:14:41 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/14 23:18:45 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void draw_wall(double wall_top, double wall_bouttom, t_game *data, double x)
{
	double wall_height = wall_bouttom - wall_top;
	for (int y = wall_top; y <= wall_bouttom; y++)
	{
		if (y < 0 || y >= WIN_HEIGHT)
			continue;
		double sample_pos = (y - wall_top) / wall_height;
		int tex_y = (int)(sample_pos * data->textures.tex_h);

		if (tex_y >= data->textures.tex_h)
			tex_y = data->textures.tex_h - 1;
		if (tex_y < 0)
			tex_y = 0;

		// address into texture data buffer:
		char *pixel = data->textures.curr_tex_data
					+ (tex_y * data->textures.curr_line)
					+ (data->textures.tex_x * (data->textures.curr_bpp / 8));
		int color = *(int *)pixel;  // assuming endian matches

		put_pixel_to_image(&data->image, x, y, color);
	}
}

static void	ft_aid(t_game *data, double r_angle, int x)
{
	int		wall_bottom_pixel;
	int		wall_top_pixel;
	double	wall_distance;
	double	wall_height;
	int		y;

	wall_distance = data->ray.final_distance * cos(r_angle - data->player.angle);
	wall_height = (TILE / wall_distance) * ((WIN_WIDTH / 2) / tan(FOV * M_PI / 360));

	wall_top_pixel = (WIN_HEIGHT / 2) - (wall_height / 2);
	wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

	wall_bottom_pixel = (WIN_HEIGHT / 2) + (wall_height / 2);
	wall_bottom_pixel = wall_bottom_pixel >= WIN_HEIGHT ? WIN_HEIGHT - 1 : wall_bottom_pixel;

	// Draw ceiling
	y = 0;
	while (y < wall_top_pixel)
		put_pixel_to_image(&data->image, x, y++, data->colors.ceiling_c);

	// Draw wall (already done here, just keep your current wall texture code)
	draw_wall(data->render.wall_top, data->render.wall_bottom, data, x);

	// Draw floor
	y = wall_bottom_pixel + 1;
	while (y < WIN_HEIGHT)
		put_pixel_to_image(&data->image, x, y++, data->colors.flor_c);
}

void rendring3d(t_game *data, double r_angle, int x)
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
	// if (data->render.wall_height > WIN_HEIGHT)
	// 	data->render.wall_height = WIN_HEIGHT;
	if (data->render.wall_height < 1)
		data->render.wall_height = 1;

	data->render.wall_top = (WIN_HEIGHT / 2) - (data->render.wall_height / 2);
	data->render.wall_bottom = (WIN_HEIGHT / 2) + (data->render.wall_height / 2);

	printf("%f; %f\n", data->render.wall_top, data->render.wall_bottom);

	ft_aid(data, r_angle, x);
}
