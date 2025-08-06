/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/03 17:08:16 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	parse(ac, av, &data);
	init_player(&data);
	//NOTE: in bonus i must also get the player color and tile color!! for minimap
	//NOTE: also for bonus sprites i need to load also the 3 images of sprites!!!
	data.mlx = mlx_init();
	if (!data.mlx)
		cleanup_exit("Error\nMlx session failed!!\n", &data);
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data.win)
		cleanup_exit("Error\nWindow creation failed!!\n", &data);
	init_all_img(&data);
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 3, 0, key_release, &data);
	mlx_hook(data.win, 17, 0, destroy, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
