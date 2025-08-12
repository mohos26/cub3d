/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_ray_face_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:47:15 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/12 11:35:06 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

void	where_ray_face(double angle, t_game *data)
{
	data->ray.face_down = angle > 0 && angle < M_PI;
	data->ray.face_up = !data->ray.face_down;
	data->ray.face_right = angle < M_PI_2 || angle > 3 * M_PI_2;
	data->ray.face_left = !data->ray.face_right;
}
