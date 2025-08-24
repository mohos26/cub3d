/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:44:14 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/24 09:54:48 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	parse(int ac, char **av, t_game *data)
{
	char	*file_name;

	if (ac != 2)
	{
		ft_putendl_fd("Erorr", 2);
		ft_putendl_fd("Expected 1 argument (map file path).", 2);
		ft_exit(1);
	}
	file_name = ft_get_file(*++av);
	if (!file_name)
	{
		ft_putendl_fd("Erorr", 2);
		ft_putendl_fd("Invalid map file path or file extension.", 2);
		ft_exit(1);
	}
	if (!ft_init_scene_data(file_name, data))
		ft_exit(1);
	ft_scan_doors(data);
}
