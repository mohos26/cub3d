/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:33:18 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/18 15:31:42 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

int	destroy(void *args)
{
	t_game	*data;

	data = (t_game *)args;
	cleanup_exit(NULL, data);
	return (0);
}

void	cleanup_sounds(t_game *data)
{
	if (data->door_tex.img_ptr)
		mlx_destroy_image(data->mlx, data->door_tex.img_ptr);
	if (data->sound.is_w)
		ma_sound_uninit(&data->sound.w_sound);
	if (data->sound.is_s)
		ma_sound_uninit(&data->sound.s_sound);
	if (data->sound.is_d)
		ma_sound_uninit(&data->sound.d_sound);
	if (data->sound.is_engine)
		ma_engine_uninit(&data->sound.engine);
}

void	cleanup_exit(char *message, t_game *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->image.img_ptr)
		mlx_destroy_image(data->mlx, data->image.img_ptr);
	if (data->tex.no_tex.img_ptr)
		mlx_destroy_image(data->mlx, data->tex.no_tex.img_ptr);
	if (data->tex.so_tex.img_ptr)
		mlx_destroy_image(data->mlx, data->tex.so_tex.img_ptr);
	if (data->tex.ea_tex.img_ptr)
		mlx_destroy_image(data->mlx, data->tex.ea_tex.img_ptr);
	if (data->tex.we_tex.img_ptr)
		mlx_destroy_image(data->mlx, data->tex.we_tex.img_ptr);
	if (data->m_mp.mini_img.img_ptr)
		mlx_destroy_image(data->mlx, data->m_mp.mini_img.img_ptr);
	if (data->sprt.frm[0].img_ptr)
		mlx_destroy_image(data->mlx, data->sprt.frm[0].img_ptr);
	if (data->sprt.frm[1].img_ptr)
		mlx_destroy_image(data->mlx, data->sprt.frm[1].img_ptr);
	if (data->sprt.frm[2].img_ptr)
		mlx_destroy_image(data->mlx, data->sprt.frm[2].img_ptr);
	cleanup_sounds(data);
	if (message)
		ft_putstr_fd(message, 2);
	ft_exit(1);
}
