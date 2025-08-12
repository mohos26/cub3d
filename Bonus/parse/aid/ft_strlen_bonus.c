/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:52:04 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/12 10:08:46 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

size_t ft_strlen(const char *s)
{
	size_t lenght;

	lenght = 0;
	while (s && *s++)
		lenght++;
	return (lenght);
}
