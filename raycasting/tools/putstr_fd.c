/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:37:33 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/07 19:09:45 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
