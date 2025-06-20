/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:44:14 by mhoussas          #+#    #+#             */
/*   Updated: 2025/06/20 15:37:38 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	char	*file_name;
	t_data	*ptr;

	if (ac != 2)
		(ft_putendl_fd("Erorr", 2), ft_exit(1));
	file_name = ft_get_file(*++av);
	if (!file_name)
		(ft_putendl_fd("Erorr", 2), ft_exit(1));
	puts("!!! Valid file_name !!!");
	ptr = ft_init_scene_data(file_name);
	if (!ptr)
		(ft_putendl_fd("Erorr", 2), ft_exit(1));
	puts("!!! Valid instruction !!!");
	ft_exit(0);
}
