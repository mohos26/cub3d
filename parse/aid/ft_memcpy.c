/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:08:27 by mhoussas          #+#    #+#             */
/*   Updated: 2025/07/07 19:09:45 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *ptr;
	const unsigned char *aid;

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
