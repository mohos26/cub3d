/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:54:24 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/24 09:45:42 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

char	*ft_get_file(char *file_name)
{
	int	length;

	if (!ft_valid_file(file_name))
		return (NULL);
	length = ft_strlen(file_name);
	if (length < 5)
		return (NULL);
	if (ft_strcmp(file_name + length - 4, ".cub"))
		return (NULL);
	return (file_name);
}
