/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:33:30 by mhoussas          #+#    #+#             */
/*   Updated: 2025/06/22 15:34:32 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

char	**ft_append_map(char **lst, char *line)
{
	char	**res;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (lst && len < (int)ft_strlen(lst[0]))
		len = ft_strlen(lst[0]);
	i = 0;
	while (lst && lst[i])
		i++;
	res = ft_calloc(sizeof(char *) * (i + 2));
	i = 0;
	while (lst && lst[i])
	{
		res[i] = ft_prepare_line(lst[i], len);
		i++;
	}
	res[i] = ft_prepare_line(line, len);
	res[i + 1] = NULL;
	return (res);
}
