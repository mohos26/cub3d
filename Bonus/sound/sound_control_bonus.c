/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_control_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:43:25 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/18 15:32:35 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	sound_controle(t_game *data)
{
	int	is_walking;

	is_walking = data->input.up || data->input.down || data->input.right
		|| data->input.left;
	if (is_walking && !ma_sound_is_playing(&data->sound.w_sound))
	{
		ma_sound_seek_to_pcm_frame(&data->sound.w_sound, 0);
		ma_sound_start(&data->sound.w_sound);
	}
	else if (!is_walking && ma_sound_is_playing(&data->sound.w_sound))
		ma_sound_stop(&data->sound.w_sound);
}

void	sound_controle2(t_game *data)
{
	ma_sound_seek_to_pcm_frame(&data->sound.s_sound, 0);
	ma_sound_start(&data->sound.s_sound);
}
