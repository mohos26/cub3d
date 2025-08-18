/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sound_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:07:28 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/18 15:30:50 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	init_sound2(t_game *data, char *s2, char *s3, ma_result *res)
{
	*res = ma_sound_init_from_file(&data->sound.engine, s2,
			MA_SOUND_FLAG_DECODE, NULL, NULL, &data->sound.s_sound);
	if (*res != MA_SUCCESS)
		cleanup_exit("ERROR\nfailed loading shooting sound\n", data);
	ma_sound_set_looping(&data->sound.s_sound, MA_FALSE);
	data->sound.is_s = 1;
	*res = ma_sound_init_from_file(&data->sound.engine, s3,
		MA_SOUND_FLAG_DECODE, NULL, NULL, &data->sound.d_sound);
	if (*res != MA_SUCCESS)
		cleanup_exit("ERROR\nfailed loading door sound\n", data);
	ma_sound_set_looping(&data->sound.d_sound, MA_FALSE);
	data->sound.is_d = 1;
}

void	init_sound(t_game *data)
{
	ma_result	res;
	char		*s1;
	char		*s2;
	char		*s3;

	s1 = "Bonus/sound/walk.mp3";
	s2 = "Bonus/sound/shoot.mp3";
	s3 = "Bonus/sound/door.mp3";
	res = ma_engine_init(NULL, &data->sound.engine);
	if (res != MA_SUCCESS)
		cleanup_exit("ERROR\nfailed initialize sound\n", data);
	data->sound.is_engine = 1;
	res = ma_sound_init_from_file(&data->sound.engine, s1,
			MA_SOUND_FLAG_DECODE, NULL, NULL, &data->sound.w_sound);
	if (res != MA_SUCCESS)
		cleanup_exit("ERROR\nfailed loading walking sound\n", data);
	ma_sound_set_looping(&data->sound.w_sound, MA_TRUE);
	data->sound.is_w = 1;
	init_sound2(data, s2, s3, &res);
}
