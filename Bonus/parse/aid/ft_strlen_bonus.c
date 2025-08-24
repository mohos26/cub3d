/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:52:04 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/24 09:56:43 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	lenght;

	lenght = 0;
	while (s && *s++)
		lenght++;
	return (lenght);
}
