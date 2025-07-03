/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:27:00 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/03 09:27:23 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, M_2_PI);
	if (angle < 0)
		angle += M_2_PI;
	return (angle);
}
