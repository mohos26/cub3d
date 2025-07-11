/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:31:08 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/11 15:28:35 by mhoussas         ###   ########.fr       */
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
	int w = TILE;
	int h = TILE;

	data->textures.no_img = mlx_xpm_file_to_image(data->mlx, data->textures.no_path, &w, &h);
	data->textures.no_data = mlx_get_data_addr(data->textures.no_img, &data->textures.no_bpp, &data->textures.no_line, &data->textures.no_end);
	data->textures.no_w = w;
	data->textures.no_h = h;

	data->textures.ea_img = mlx_xpm_file_to_image(data->mlx, data->textures.ea_path, &w, &h);
	data->textures.ea_data = mlx_get_data_addr(data->textures.ea_img, &data->textures.ea_bpp, &data->textures.ea_line, &data->textures.ea_end);
	data->textures.ea_w = w;
	data->textures.ea_h = h;

	data->textures.so_img = mlx_xpm_file_to_image(data->mlx, data->textures.so_path, &w, &h);
	data->textures.so_data = mlx_get_data_addr(data->textures.so_img, &data->textures.so_bpp, &data->textures.so_line, &data->textures.so_end);
	data->textures.so_w = w;
	data->textures.so_h = h;

	data->textures.we_img = mlx_xpm_file_to_image(data->mlx, data->textures.we_path, &w, &h);
	data->textures.we_data = mlx_get_data_addr(data->textures.we_img, &data->textures.we_bpp, &data->textures.we_line, &data->textures.we_end);
	data->textures.we_w = w;
	data->textures.we_h = h;
	// NOTE: related to bonus!!! minimap
	//  data->colors.tile_c = 16710599;
	//  data->colors.player_c = 6204374;
}
