/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/14 16:32:31 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

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
	update_sprite_animation(data);
	clear_image(&data->image, 0, WIN_WIDTH, WIN_HEIGHT);
	core_logique(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win,
		data->m_mp.mini_img.img_ptr, 0, 0);
	draw_sprite(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	data;

	ft_memset(&data, 0, sizeof(t_game));
	parse(ac, av, &data);
	init_player(&data);
	data.mlx = mlx_init();
	if (!data.mlx)
		cleanup_exit("Error\nMlx session failed!!\n", &data);
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data.win)
		cleanup_exit("Error\nWindow creation failed!!\n", &data);
	init_all_img(&data);
	init_sound(&data);
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 3, 0, key_release, &data);
	mlx_hook(data.win, 17, 0, destroy, &data);
	mlx_hook(data.win, 6, 0, mouse_move, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
