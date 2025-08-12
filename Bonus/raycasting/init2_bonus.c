/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:09:47 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/12 11:19:39 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	init_sprites2(t_game *data, char *sp3)
{
	data->sprt.frm[2].img_ptr = mlx_xpm_file_to_image(data->mlx, sp3,
			&data->sprt.frm[2].width, &data->sprt.frm[2].height);
	if (!data->sprt.frm[2].img_ptr)
		cleanup_exit("Error\nFailed loading third sprite!\n", data);
	data->sprt.frm[2].data = mlx_get_data_addr(data->sprt.frm[2].img_ptr,
			&data->sprt.frm[2].bbp, &data->sprt.frm[2].row_len,
			&data->sprt.frm[2].endian);
}
