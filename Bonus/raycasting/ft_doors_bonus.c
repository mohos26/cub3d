/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:42:51 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/18 15:33:47 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	get_door_idx(t_game *data, int mx, int my)
{
	int	i;

	if (!data->doors)
		return (-1);
	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == mx && data->doors[i].y == my)
			return (i);
		i++;
	}
	return (-1);
}

void	interact_door(t_game *data)
{
	double ang = data->player.angle;
	double tx = data->player.x + cos(ang) * (TILE * 1.1);
	double ty = data->player.y + sin(ang) * (TILE * 1.1);
	int mx = (int)(tx / TILE);
	int my = (int)(ty / TILE);
	int id;

	if (mx < 0 || my < 0 || mx >= data->map_width || my >= data->map_height)
		return ;
	if (data->map[my][mx] != '2')
		return ;
	id = get_door_idx(data, mx, my);
	if (id < 0)
		return ;
	data->doors[id].open = !data->doors[id].open;
	ma_sound_seek_to_pcm_frame(&data->sound.d_sound, 0);
	ma_sound_start(&data->sound.d_sound);
}

void	init_door(t_game *data)
{
	char	*door;

	door = "Bonus/textures/door_tex1.xpm";
	data->door_tex.img_ptr = mlx_xpm_file_to_image(data->mlx, door,
			&data->door_tex.width, &data->door_tex.height);
	if (!data->door_tex.img_ptr)
		cleanup_exit("Error\nFailed loading door texture!!\n", data);
	data->door_tex.data = mlx_get_data_addr(data->door_tex.img_ptr,
			&data->door_tex.bbp, &data->door_tex.row_len,
			&data->door_tex.endian);
}

bool	door_is_open_at(t_game *data, int mx, int my)
{
	int id = get_door_idx(data, mx, my);
	if (id < 0)
		return (false);
	return (data->doors[id].open);
}
