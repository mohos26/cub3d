/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:29:00 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/12 11:36:30 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	mouse_move(int x, int y, void *args)
{
	t_game	*data;
	int		dx;
	int		center_x;
	int		center_y;

	data = (t_game *)args;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	if ((x == center_x && y == center_y)
		|| data->input.rot_left || data->input.rot_right)
		return (0);
	dx = x - center_x;
	data->player.angle += dx * 0.02;
	data->player.angle = normalize_angle(data->player.angle);
	mlx_mouse_move(data->win, center_x, center_y);
	return (0);
}
