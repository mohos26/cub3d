/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:29:00 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/14 10:17:09 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	mouse_move(int x, int y, void *args)
{
	t_game		*data;
	int			dx;

	data = (t_game *)args;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0
		|| data->input.rot_left || data->input.rot_right)
		return (0);
	dx = x - data->input.prev_x;
	data->player.angle += dx * 0.004;
	data->player.angle = normalize_angle(data->player.angle);
	data->input.prev_x = x;
	return (0);
}
