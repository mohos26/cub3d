/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:12 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/11 10:38:03 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
//NOTE: for debbug
void	draw_tile(int y, int x, t_game *data, int is_wall)
{
	for (int i = 0; i < TILE; i++)
	{
		for (int j = 0; j < TILE; j++)
		{
			if (is_wall)
				put_pixel_to_image(&data->image, x + j, y + i, data->colors.tile_c);
			else if (!is_wall)
				put_pixel_to_image(&data->image, x + j, y + i, 0);
		}
	}
}

void	draw_map(t_game *data)
{
	for (int y = 0; y < data->map_height; y++)
	{
		for (int x=0; x < data->map_width; x++)
		{
			draw_tile(y * TILE, x * TILE, data, data->map[y][x] == '1');
		}
	}
}

void draw_line_bresenham(int x0, int y0, int x1, int y1, int color, t_game *data)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1) {
		put_pixel_to_image(&data->image, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
	}
}

void   draw_line(double angle, int len, double x, double y , int color , t_game *data)
{
	double dx = cos(angle) * len;
	double dy = sin(angle) * len;
	for(int i = 0; i < len; i++)
	{
		int px = x + dx * i / len;
		int py = y + dy * i / len;
		put_pixel_to_image(&data->image, px, py, color);
	}
}
void	draw_player(t_game *data)
{
	draw_line(data->player.angle, 20 , data->player.x, data->player.y, 16757940, data);
	for (int i = -RADIUS; i <=RADIUS; i++)
	{
		for (int j = -RADIUS; j <= RADIUS; j++)
		{
			if (pow(i, 2) + pow(j, 2) <= pow(RADIUS, 2))
				put_pixel_to_image(&data->image, (int)(data->player.x + j) , (int)(data->player.y + i) , data->colors.player_c);
		}
	}
}
*/

void core_logique(t_game *data)
{
	double r_angle;
	int i;

	i = 0;
	r_angle = data->player.angle - ((FOV * (M_PI / 180)) / 2);
	while (i < RAYS_NUM)
	{
		r_angle = normalize_angle(r_angle);
		cast_rays(r_angle, data);
		rendring3d(data, r_angle, i);
		// draw_line_bresenham((int)data->player.x, (int)data->player.y,
		//         (int)data->ray.final_hit_x, (int)data->ray.final_hit_y,
		//         0xFF0000, data);//NOTE: for debbug
		r_angle += (FOV * (M_PI / 180)) / RAYS_NUM;
		i++;
	}
}

int game_loop(void *args)
{
	t_game *data;

	data = (t_game *)args;
	move_controle(data);
	clear_image(&data->image, 0);
	// draw_map(data);//NOTE: for debbug
	core_logique(data);
	// draw_player(data);//NOTE: for debbug
	mlx_put_image_to_window(data->mlx, data->win, data->image.img_ptr, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_game data;

	ft_memset(&data, 0, sizeof(t_game));
	data.colors.tile_c = 16710599;
	data.colors.player_c = 6204374;
	parse(ac, av, &data);
	data.mlx = mlx_init();
	if (!data.mlx)
		cleanup_exit("Error\nMlx session failed!!\n", &data);
	init(&data); // NOTE: this maybe must be in parsing functions
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data.win)
		cleanup_exit("Error\nWindow creation failed!!\n", &data);
	data.image.img_ptr = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.image.img_ptr)
		cleanup_exit("Error\nImage creation failed!!\n", &data);
	data.image.data = mlx_get_data_addr(data.image.img_ptr, &data.image.bbp,
										&data.image.row_len, &data.image.endian);
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 3, 0, key_release, &data);
	mlx_hook(data.win, 17, 0, destroy, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
