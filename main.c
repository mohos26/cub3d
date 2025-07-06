/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/03 17:08:48 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	core_logique(t_game *data)
{
	double	r_angle;
	int		i;

	i = 0;
	r_angle = data->player.angle - ((FOV * (M_PI / 180)) / 2);
	while (i < RAYS_NUM)
	{
		r_angle = normalize_angle(r_angle);
		cast_rays(r_angle, data);
		rendring3d(data, r_angle, i);
		r_angle += (FOV * (M_PI / 180)) / RAYS_NUM;
		i++;
	}
}

int	game_loop(void *args)
{
	t_game	*data;

	data = (t_game *)args;
	move_controle(data);
	clear_image(&data->image, 0);
	core_logique(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img_ptr, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	data;

	ft_memset(&data, 0, sizeof(t_game));
	//TODO: parsing goes here
	init(&data);//NOTE: this maybe must be in parsing functions
	data.mlx = mlx_init();
	if (!data.mlx)
		cleanup_exit("Error\nMlx session failed!!\n", &data);
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data.win)
		cleanup_exit("Error\nWindow creation failed!!\n", &data);
	data.image.img_ptr = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.image.img_ptr)
		cleanup_exit("Error\nImage creation failed!!\n", &data);
	data.image.data = mlx_get_data_addr(data.image.img_ptr, &data.image.bbp,
			&data.image.row_len, &data.image.endian);
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 3, 0, key_release, &data);
	mlx_hook(data.win, 17, 0, destroy, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
