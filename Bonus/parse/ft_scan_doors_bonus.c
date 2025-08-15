/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_doors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 09:55:32 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/15 15:47:13 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

static int	ft_doors_length(char **map)
{
	int	res;
	int	i;
	int	j;

	i = 0;
	res = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				res++;
			j++;
		}
		i++;
	}
	return (res);
}

static void	ft_set_door(t_game *data, int i, int j, int d)
{
	data->doors[d].x = j;
	data->doors[d].y = i;
	data->doors[d].open = 0;
}

void	ft_scan_doors(t_game *data)
{
	int i;
	int j;
	int d;

	data->door_count = ft_doors_length(data->map);
	if (!data->door_count)
	{
		data->doors = NULL;
		return ;
	}
	d = 0;
	i = 0;
	data->doors = ft_calloc(sizeof(t_door) * (data->door_count + 1));
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '2')
				ft_set_door(data, i, j, d++);
			j++;
		}
		i++;
	}
}
