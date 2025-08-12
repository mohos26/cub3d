/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:33:18 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/04 11:29:25 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	destroy(void *args)
{
	t_game	*data;

	data = (t_game *)args;
	cleanup_exit(NULL, data);
	return (0);
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
	if (message)
		ft_putstr_fd(message, 2);
	ft_exit(1);
}
