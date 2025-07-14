/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:44:14 by mhoussas          #+#    #+#             */
/*   Updated: 2025/07/12 11:25:56 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void parse(int ac, char **av, t_game *data)
{
	char *file_name;
	t_data *ptr;

	if (ac != 2)
		(ft_putendl_fd("Erorr", 2), ft_exit(1));
	file_name = ft_get_file(*++av);
	if (!file_name)
		(ft_putendl_fd("Erorr", 2), ft_exit(1));
	ptr = ft_init_scene_data(file_name);
	if (!ptr)
		(ft_putendl_fd("Erorr", 2), ft_exit(1));
	//NOTE: this must be better and alighned with the global struct
	data->map_height = ptr->map_height + 1;
	data->map_width = ptr->map_width;
	data->map = ptr->map;

	data->textures.no_path = ptr->img_no;
	data->textures.ea_path = ptr->img_ea;
	data->textures.so_path = ptr->img_so;
	data->textures.we_path = ptr->img_we;

	data->colors.ceiling_c = ptr->ceil_color;
	data->colors.flor_c = ptr->floor_color;
}
