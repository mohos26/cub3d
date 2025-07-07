/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:42:46 by mhoussas          #+#    #+#             */
/*   Updated: 2025/07/07 19:09:07 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void ft_free(void *ptr, int flag)
{
	static void *lst[INT_MAX];
	static int i;
	int j;

	if (flag)
	{
		j = 0;
		while (lst[j])
			free(lst[j++]);
	}
	else
		lst[i++] = ptr;
}

void ft_exit(int status)
{
	ft_free(NULL, 1);
	exit(status);
}

void *ft_calloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_exit(1);
	ft_free(ptr, 0);
	ft_bzero(ptr, size);
	return (ptr);
}
