/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_zoom_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:29:57 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/24 17:21:39 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

void	handle_zooming_feature(int keycode, t_game *data)
{
	if (keycode == ZOOM_IN || keycode == ZOOM_OUT)
	{
		if (keycode == ZOOM_IN)
		{
			if (data->m_mp.tile_2_show == 8)
				return ;
			else if (data->m_mp.tile_2_show == 12)
				data->m_mp.tile_2_show = 8;
			else
				data->m_mp.tile_2_show = 12;
		}
		if (keycode == ZOOM_OUT)
		{
			if (data->m_mp.tile_2_show == 16)
				return ;
			else if (data->m_mp.tile_2_show == 8)
				data->m_mp.tile_2_show = 12;
			else
				data->m_mp.tile_2_show = 16;
		}
		data->m_mp.tile = data->m_mp.width / data->m_mp.tile_2_show;
	}
}
