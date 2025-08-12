/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:28:12 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/06 10:28:32 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	ft_error(char *message, int fd)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	close(fd);
	return (false);
}
