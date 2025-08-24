/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:08:27 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/24 09:55:40 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*aid;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	ptr = (unsigned char *)dst;
	aid = (const unsigned char *)src;
	while (n--)
		*ptr++ = *aid++;
	return (dst);
}
