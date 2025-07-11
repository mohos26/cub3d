/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:44:14 by mhoussas          #+#    #+#             */
/*   Updated: 2025/07/09 15:46:06 by mhoussas         ###   ########.fr       */
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
	puts("!!! Valid file_name !!!");
	ptr = ft_init_scene_data(file_name);
	if (!ptr)
		(ft_putendl_fd("Erorr", 2), ft_exit(1));
	//NOTE: this must be better and alighned with the global struct
	data->map_height = ptr->map_height + 1; // NOTE: the calculation of the height in the parsing is messign 1 line
	data->map_width = ptr->map_width;
	data->map = ptr->map;
	// NOTE : need to capture also teh ceiling and the floor and the xpms !!!!!
}
