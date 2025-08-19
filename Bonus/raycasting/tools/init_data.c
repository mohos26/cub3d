/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:35:16 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/19 13:36:04 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

void	init_data(t_game *data)
{
	data->m_mp.tile_2_show = 12;
	data->m_mp.width = 144;
	data->m_mp.height = 144;
	data->m_mp.tile = data->m_mp.width / data->m_mp.tile_2_show;
	data->colors.player_c = 6204374;
	data->colors.tail_c = 16710599;
	data->colors.door_c = 16753485;
	data->input.prev_x = WIN_WIDTH / 2;
}
