/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:33:30 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/15 10:33:07 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*ft_prepare_line(char *line, int len)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup(line);
	while (res[i])
	{
		if (res[i] == ' ')
			res[i] = '1';
		i++;
	}
	while ((int)ft_strlen(res) < len)
		res = ft_strjoin(res, "1");
	return (res);
}

void	ft_append_map(t_game *data, char *line)
{
	int		height;
	char	**lst;
	int		len;
	int		i;

	lst = data->map;
	len = ft_strlen(line);
	if (lst && len < (int)ft_strlen(lst[0]))
		len = ft_strlen(lst[0]);
	height = 1;
	while (lst && lst[height])
		height++;
	data->map = ft_calloc(sizeof(char *) * (height + 2));
	i = 0;
	while (lst && lst[i])
	{
		data->map[i] = ft_prepare_line(lst[i], len);
		i++;
	}
	data->map[i] = ft_prepare_line(line, len);
	data->map[i + 1] = NULL;
	data->map_height = height + 1;
	data->map_width = len;
}
