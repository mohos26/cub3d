/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_ray_face.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouanni <aouanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:47:15 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/03 09:49:15 by aouanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	where_ray_face(double angle, t_game *data)
{
	data->ray.face_down = angle > 0 && angle < 180;
	data->ray.face_up = !data->ray.face_down;
	data->ray.face_right = angle > 270 || angle < 90;
	data->ray.face_down = !data->ray.face_right;
}
