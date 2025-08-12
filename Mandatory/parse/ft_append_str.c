/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:30:44 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/05 12:00:28 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_append_str(char *s, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc((ft_strlen(s) + 2) * sizeof(char));
	while (s && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	return (res);
}
