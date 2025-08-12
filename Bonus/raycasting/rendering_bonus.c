/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:14:41 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/12 11:30:19 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_wall(t_game *data, int x, int y, t_image *current)
{
	char	*tex_addr;
	int		color;

	data->tex.distance_diff = (y + (data->render.wall_height / 2)
			- (WIN_HEIGHT / 2));
	data->tex.tex_y = (int)((data->tex.distance_diff
				/ data->render.wall_height) * current->height);
	if (data->tex.tex_y < 0)
		data->tex.tex_y = 0;
	else if (data->tex.tex_y >= current->height)
		data->tex.tex_y = current->height - 1;
	tex_addr = current->data + (data->tex.tex_y * current->row_len)
		+ (data->tex.tex_x * (current->bbp / 8));
	color = *(unsigned int *)tex_addr;
	put_pixel_to_image(&data->image, x, y, color);
}

void	pixel_selection(t_game *data, int x)
{
	t_image	*current;
	int		y;

	if (x < 0 || x >= WIN_WIDTH)
		return ;
	current = get_texture(data);
	data->tex.x_offset = get_x_offset(data);
	data->tex.tex_x = (int)((data->tex.x_offset / TILE) * current->width);
	if (data->tex.tex_x < 0)
		data->tex.tex_x = 0;
	else if (data->tex.tex_x >= current->width)
		data->tex.tex_x = current->width - 1;
	y = data->render.wall_top;
	while (y < data->render.wall_bottom)
	{
		draw_wall(data, x, y, current);
		y++;
	}
}

void	draw_floor_ceiling(int x, t_game *data)
{
	int	y;

	y = 0;
	while (y < data->render.wall_top && y < WIN_HEIGHT)
	{
		put_pixel_to_image(&data->image, x, y, data->colors.ceiling_c);
		y++;
	}
	y = data->render.wall_bottom;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(&data->image, x, y, data->colors.floor_c);
		y++;
	}
}

void	rendring3d(t_game *data, double r_angle, int i)
{
	double	new_angle;
	double	ray_angle_diff;
	double	corrected_distance;
	double	distance_to_plan;

	new_angle = (FOV / 2) * (M_PI / 180);
	distance_to_plan = (WIN_WIDTH / 2) / tan(new_angle);
	ray_angle_diff = (r_angle - data->player.angle);
	corrected_distance = data->ray.final_distance * cos(ray_angle_diff);
	data->render.wall_height = (TILE / corrected_distance) * distance_to_plan;
	data->render.wall_top = (WIN_HEIGHT / 2) - (data->render.wall_height / 2);
	if (data->render.wall_top < 0)
		data->render.wall_top = 0;
	data->render.wall_bottom = (WIN_HEIGHT / 2)
		+ (data->render.wall_height / 2);
	if (data->render.wall_bottom > WIN_HEIGHT)
		data->render.wall_bottom = WIN_HEIGHT;
	draw_floor_ceiling(i, data);
	pixel_selection(data, i);
}
