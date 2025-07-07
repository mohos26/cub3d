/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_controle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:14:43 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int key_press(int keycode, t_game *data)
{
	if (keycode == PLAYER_UP)
		data->input.up = 1;
	if (keycode == PLAYER_DOWN)
		data->input.down = 1;
	if (keycode == PLAYER_RIGHT)
		data->input.right = 1;
	if (keycode == PLAYER_LEFT)
		data->input.left = 1;
	if (keycode == ROTATE_RIGHT)
		data->input.rot_right = 1;
	if (keycode == ROTATE_LEFT)
		data->input.rot_left = 1;
	if (keycode == ESC)
		data->input.escap = 1;
	return (0);
}

int key_release(int keycode, t_game *data)
{
	if (keycode == PLAYER_UP)
		data->input.up = 0;
	if (keycode == PLAYER_DOWN)
		data->input.down = 0;
	if (keycode == PLAYER_RIGHT)
		data->input.right = 0;
	if (keycode == PLAYER_LEFT)
		data->input.left = 0;
	if (keycode == ROTATE_RIGHT)
		data->input.rot_right = 0;
	if (keycode == ROTATE_LEFT)
		data->input.rot_left = 0;
	if (keycode == ESC)
		data->input.escap = 0;
	return (0);
}

void move_player(t_game *data, double *new_x, double *new_y)
{
	if (data->input.up)
	{
		*new_x += cos(data->player.angle) * PLAYERSPEED;
		*new_y += sin(data->player.angle) * PLAYERSPEED;
	}
	if (data->input.down)
	{
		*new_x -= cos(data->player.angle) * PLAYERSPEED;
		*new_y -= sin(data->player.angle) * PLAYERSPEED;
	}
	if (data->input.right)
	{
		*new_x += cos(data->player.angle + M_PI_2) * PLAYERSPEED;
		*new_y += sin(data->player.angle + M_PI_2) * PLAYERSPEED;
	}
	if (data->input.left)
	{
		*new_x += cos(data->player.angle - M_PI_2) * PLAYERSPEED;
		*new_y += sin(data->player.angle - M_PI_2) * PLAYERSPEED;
	}
}

void move_controle(t_game *data)
{
	double new_x;
	double new_y;

	new_x = data->player.x;
	new_y = data->player.y;
	if (data->input.escap)
		cleanup_exit(NULL, data);
	move_player(data, &new_x, &new_y);
	if (data->input.rot_right)
		data->player.angle += ROTATIONSPEED * (M_PI / 180);
	if (data->input.rot_left)
		data->player.angle -= ROTATIONSPEED * (M_PI / 180);
	data->player.angle = normalize_angle(data->player.angle);
	if (!is_wall(new_x, data->player.y, data))
		data->player.x = new_x;
	if (!is_wall(data->player.x, new_y, data))
		data->player.y = new_y;
}
