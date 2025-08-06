/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:22:31 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/06 10:27:20 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static bool	ft_append_rgb(int *count, int *color, int *n, char **s)
{
	while (*((*s) + 1) && *((*s) + 1) == ' ')
		(*s)++;
	(*count)++;
	*color = (*color << 8) + *n;
	*n = 0;
	return (true);
}

int	ft_parse_rgb_string(char *s)
{
	int		n;
	bool	flag;
	int		count;
	int		color;

	(true, n = 0, flag = false, count = 0, color = 0);
	while (*s)
	{
		if (ft_isdigit(*s))
		{
			flag = false;
			n = n * 10 + *s - 48;
			if (n > 255)
				return (-1);
		}
		else if (*s == ',' && !flag && count < 2)
			flag = ft_append_rgb(&count, &color, &n, &s);
		else
			return (-1);
		s++;
	}
	if (flag || count != 2)
		return (-1);
	return ((color << 8) + n);
}
