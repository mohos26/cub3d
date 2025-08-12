/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_minimap_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:10:35 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/12 11:34:20 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

void	put_pixel_to_minimap(t_game *data, int x, int y, int color)
{
	char	*dst;
	t_image	*img;

	img = &data->m_mp.mini_img;
	if (x < 0 || x >= data->m_mp.width || y >= data->m_mp.height || y < 0)
		return ;
	dst = img->data + (y * img->row_len + x * (img->bbp / 8));
	*(unsigned *)dst = color;
}
