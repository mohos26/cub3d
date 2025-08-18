/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:31:08 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/18 10:53:14 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	direction_coordinates(int x, int y, t_game *data)
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
}

void	init_player(t_game *data)
{
	int	y;
	int	x;

	y = 0;
	data->m_mp.width = TILE_2_SHOW * MINI_TILE;
	data->m_mp.height = data->m_mp.width;
	data->colors.player_c = 6204374;
	data->colors.tail_c = 16710599;
	data->colors.door_c = 16753485;
	data->input.prev_x = WIN_WIDTH / 2;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' ||
				data->map[y][x] == 'W' || data->map[y][x] == 'E')
			{
				direction_coordinates(x, y, data);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_sprites(t_game *data)
{
	char	*sp1;
	char	*sp2;
	char	*sp3;

	sp1 = "Bonus/sprites/idle-gun.xpm";
	sp2 = "Bonus/sprites/shoot-1.xpm";
	sp3 = "Bonus/sprites/shoot-2.xpm";
	data->sprt.frm[0].img_ptr = mlx_xpm_file_to_image(data->mlx, sp1,
			&data->sprt.frm[0].width, &data->sprt.frm[0].height);
	if (!data->sprt.frm[0].img_ptr)
		cleanup_exit("Error\nFailed loading first sprite!\n", data);
	data->sprt.frm[0].data = mlx_get_data_addr(data->sprt.frm[0].img_ptr,
			&data->sprt.frm[0].bbp, &data->sprt.frm[0].row_len,
			&data->sprt.frm[0].endian);
	data->sprt.frm[1].img_ptr = mlx_xpm_file_to_image(data->mlx, sp2,
			&data->sprt.frm[1].width, &data->sprt.frm[1].height);
	if (!data->sprt.frm[1].img_ptr)
		cleanup_exit("Error\nFailed loading second sprite!\n", data);
	data->sprt.frm[1].data = mlx_get_data_addr(data->sprt.frm[1].img_ptr,
			&data->sprt.frm[1].bbp, &data->sprt.frm[1].row_len,
			&data->sprt.frm[1].endian);
	init_sprites2(data, sp3);
}

void	init_all_img2(t_game *data)
{
	data->tex.ea_tex.img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->tex.ea, &data->tex.ea_tex.width,
			&data->tex.ea_tex.height);
	if (!data->tex.ea_tex.img_ptr)
		cleanup_exit("Error\nFailed loading EA texture!!\n", data);
	data->tex.ea_tex.data = mlx_get_data_addr(data->tex.ea_tex.img_ptr,
			&data->tex.ea_tex.bbp, &data->tex.ea_tex.row_len,
			&data->tex.ea_tex.endian);
	data->tex.we_tex.img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->tex.we, &data->tex.we_tex.width,
			&data->tex.we_tex.height);
	if (!data->tex.we_tex.img_ptr)
		cleanup_exit("Error\nFailed loading WE texture!!\n", data);
	data->tex.we_tex.data = mlx_get_data_addr(data->tex.we_tex.img_ptr,
			&data->tex.we_tex.bbp, &data->tex.we_tex.row_len,
			&data->tex.we_tex.endian);
	data->m_mp.mini_img.img_ptr = mlx_new_image(data->mlx,
			data->m_mp.width, data->m_mp.height);
	if (!data->m_mp.mini_img.img_ptr)
		cleanup_exit("Error\nminimap creation failed!!\n", data);
	data->m_mp.mini_img.data = mlx_get_data_addr(data->m_mp.mini_img.img_ptr,
			&data->m_mp.mini_img.bbp, &data->m_mp.mini_img.row_len,
			&data->m_mp.mini_img.endian);
	init_sprites(data);
	init_door(data);
}

void	init_all_img(t_game *data)
{
	data->image.img_ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->image.img_ptr)
		cleanup_exit("Error\nImage creation failed!!\n", data);
	data->image.data = mlx_get_data_addr(data->image.img_ptr, &data->image.bbp,
			&data->image.row_len, &data->image.endian);
	data->tex.no_tex.img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->tex.no, &data->tex.no_tex.width,
			&data->tex.no_tex.height);
	if (!data->tex.no_tex.img_ptr)
		cleanup_exit("Error\nFailed loading NO texture!!\n", data);
	data->tex.no_tex.data = mlx_get_data_addr(data->tex.no_tex.img_ptr,
			&data->tex.no_tex.bbp, &data->tex.no_tex.row_len,
			&data->tex.no_tex.endian);
	data->tex.so_tex.img_ptr = mlx_xpm_file_to_image(data->mlx,
			data->tex.so, &data->tex.so_tex.width,
			&data->tex.so_tex.height);
	if (!data->tex.so_tex.img_ptr)
		cleanup_exit("Error\nFailed loading SO texture!!\n", data);
	data->tex.so_tex.data = mlx_get_data_addr(data->tex.so_tex.img_ptr,
			&data->tex.so_tex.bbp, &data->tex.so_tex.row_len,
			&data->tex.so_tex.endian);
	init_all_img2(data);
}
