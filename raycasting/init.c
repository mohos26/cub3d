/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:31:08 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void init(t_game *data)
{
	int y;
	int x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' ||
				data->map[y][x] == 'W' || data->map[y][x] == 'E')
			{
				data->player.x = (x * TILE) + (TILE / 2);
				data->player.y = (y * TILE) + (TILE / 2);
				if (data->map[y][x] == 'N')
					data->player.angle = 270 * (M_PI / 180);
				else if (data->map[y][x] == 'S')
					data->player.angle = 90 * (M_PI / 180);
				else if (data->map[y][x] == 'W')
					data->player.angle = 180 * (M_PI / 180);
				else if (data->map[y][x] == 'E')
					data->player.angle = 0 * (M_PI / 180);
				break;
			}
			x++;
		}
		y++;
	}
	// TODO: initialize textures??
	// NOTE: related to bonus!!! minimap
	//  data->colors.tile_c = 16710599;
	//  data->colors.player_c = 6204374;
}
