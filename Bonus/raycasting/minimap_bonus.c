/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:36:01 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/19 11:59:09 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_minimap_tiles(int x, int y, t_game *data, int color)
{
	int	pixel_y;
	int	pixel_x;

	pixel_y = y;
	while (pixel_y < y + data->m_mp.tile)
	{
		pixel_x = x;
		while (pixel_x < x + data->m_mp.tile)
		{
			put_pixel_to_minimap(data, pixel_x, pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_minimap2(t_game *data, int map_cords[2])
{
	int	minimap_tile_x;
	int	minimap_tile_y;
	int	color;

	if (map_cords[0] < 0 || map_cords[1] < 0
		|| map_cords[0] >= data->map_height || map_cords[1] >= data->map_width)
		color = data->colors.tail_c;
	else
	{
		if (data->map[map_cords[0]][map_cords[1]] == '1')
			color = data->colors.tail_c;
		else if (data->map[map_cords[0]][map_cords[1]] == '2'
			&& !door_is_open_at(data, map_cords[1], map_cords[0]))
			color = data->colors.door_c;
		else
			color = 0;
	}
	minimap_tile_x = (map_cords[1] - data->m_mp.start_x) * data->m_mp.tile;
	minimap_tile_y = (map_cords[0] - data->m_mp.start_y) * data->m_mp.tile;
	draw_minimap_tiles(minimap_tile_x, minimap_tile_y, data,
		color);
}

void	draw_border(t_game *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->m_mp.height)
	{
		x = 0;
		while (x < data->m_mp.width)
		{
			if (x >= data->m_mp.width - 2 || y >= data->m_mp.height - 2)
				put_pixel_to_minimap(data, x, y, 16777215);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_game *data)
{
	int	mini_player_x;
	int	mini_player_y;
	int	i;
	int	j;

	i = -RADIUS;
	mini_player_x = (data->player.x / TILE - data->m_mp.start_x)
		* data->m_mp.tile;
	mini_player_y = (data->player.y / TILE - data->m_mp.start_y)
		* data->m_mp.tile;
	while (i <= RADIUS)
	{
		j = -RADIUS;
		while (j <= RADIUS)
		{
			if (pow(i, 2) + pow(j, 2) <= pow(RADIUS, 2))
				put_pixel_to_minimap(data, (int)mini_player_x + j,
					(int)mini_player_y + i, data->colors.player_c);
			j++;
		}
		i++;
	}
	draw_border(data);
}

void	draw_minimap(t_game *data)
{
	int	player_x;
	int	player_y;
	int	half_tiles;
	int	map_cords[2];

	clear_image(&data->m_mp.mini_img, 0, data->m_mp.width, data->m_mp.height);
	player_x = floor(data->player.x / TILE);
	player_y = floor(data->player.y / TILE);
	half_tiles = data->m_mp.tile_2_show / 2;
	data->m_mp.start_x = player_x - half_tiles;
	data->m_mp.start_y = player_y - half_tiles;
	data->m_mp.end_x = player_x + half_tiles;
	data->m_mp.end_y = player_y + half_tiles;
	map_cords[0] = data->m_mp.start_y;
	while (map_cords[0] < data->m_mp.end_y)
	{
		map_cords[1] = data->m_mp.start_x;
		while (map_cords[1] < data->m_mp.end_x)
		{
			draw_minimap2(data, map_cords);
			map_cords[1]++;
		}
		map_cords[0]++;
	}
	draw_minimap_player(data);
}
