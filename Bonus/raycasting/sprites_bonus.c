/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:10:18 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/12 11:52:49 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	update_sprite_animation(t_game *data)
{
	if (!data->sprt.is_shooting)
	{
		data->sprt.current_frame = 0;
		return ;
	}
	data->sprt.frame_counter++;
	if (data->sprt.frame_counter >= 5)
	{
		data->sprt.frame_counter = 0;
		data->sprt.current_frame++;
		if (data->sprt.current_frame >= 3)
		{
			data->sprt.is_shooting = 0;
			data->sprt.current_frame = 0;
			data->sprt.animation_complete = 1;
		}
	}
}

void	draw_sprite2(t_game *data, int *i, int *counter, t_image *current)
{
	if (data->sprt.animation_complete)
	{
		*i = 0;
		*counter = 0;
		data->sprt.animation_complete = 0;
	}
	mlx_put_image_to_window(data->mlx, data->win,
		current->img_ptr, data->sprt.sprite_x, data->sprt.sprite_y);
}

void	draw_sprite(t_game *data)
{
	t_image		*current;
	static int	counter;
	static int	i;

	current = &data->sprt.frm[data->sprt.current_frame];
	data->sprt.sprite_x = (WIN_WIDTH - current->width) / 2;
	data->sprt.sprite_y = (WIN_HEIGHT - current->height) + 10;
	if (!data->sprt.is_shooting)
	{
		counter++;
		if (counter >= 10)
		{
			counter = 0;
			i = (i + 1) % 4;
		}
		else if (i == 1)
			data->sprt.sprite_y += 5;
		else if (i == 3)
			data->sprt.sprite_y -= 5;
	}
	draw_sprite2(data, &i, &counter, current);
}
