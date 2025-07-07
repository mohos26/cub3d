/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:42:35 by mhoussas          #+#    #+#             */
/*   Updated: 2025/07/07 19:09:08 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool ft_valid_file(char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}
