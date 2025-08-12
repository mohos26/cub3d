/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:30:44 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/12 10:08:46 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

char *ft_append_str(char *s, char c)
{
	char *res;
	int i;

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
