/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:33:18 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:45 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int destroy(void *args)
{
	t_game *data;

	data = (t_game *)args;
	cleanup_exit(NULL, data);
	return (0);
}

void cleanup_exit(char *message, t_game *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->image.img_ptr)
		mlx_destroy_image(data->mlx, data->image.img_ptr);
	// TODO: destroy other textures images && call GC(map free maybe)
	if (message)
		ft_putstr_fd(message, 2);
	exit(1);
}
