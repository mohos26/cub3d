/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:29:16 by mhoussas          #+#    #+#             */
/*   Updated: 2025/08/12 10:08:46 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

char *ft_strdup(const char *s1)
{
	char *ptr;
	char *head;

	ptr = ft_calloc(ft_strlen(s1) * sizeof(char) + 1);
	head = ptr;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (head);
}
