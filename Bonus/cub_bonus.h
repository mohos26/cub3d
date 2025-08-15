/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:27:11 by aouanni           #+#    #+#             */
/*   Updated: 2025/08/15 18:10:50 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include <libc.h>
# include <string.h>
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include "sound/miniaudio_bonus.h"

# define TILE 32
# define RADIUS 5
# define PLAYERSPEED 2
# define ROTATIONSPEED 2//in degree
# define WIN_WIDTH 1680
# define WIN_HEIGHT 1050

# define PLAYER_UP 13
# define PLAYER_DOWN 1
# define PLAYER_RIGHT 2
# define PLAYER_LEFT 0
# define ROTATE_RIGHT 124
# define ROTATE_LEFT 123
# define ESC 53
# define DOOR_OPEN 49

# define FOV 60//in degree
# define RAYS_NUM WIN_WIDTH

# define BUFFER_SIZE 42

# define MINI_TILE 12
# define TILE_2_SHOW 12

# define SHOOT_KEY 7

typedef struct s_door
{
	int x; // map coord (tile x)
	int y; // map coord (tile y)
	int open; // 0 = closed, 1 = open
}	t_door;

typedef struct s_color
{
	int	floor_c;
	int	ceiling_c;
	int	tail_c;
	int	player_c;
}	t_color;

typedef struct s_input
{
	int	up;
	int	down;
	int	right;
	int	left;
	int	rot_right;
	int	rot_left;
	int	escap;
	int	shoot;
	int	prev_x;
}	t_input;

typedef struct s_image
{
	void	*img_ptr;
	char	*data;
	int		bbp;
	int		row_len;
	int		endian;
	int		height;
	int		width;
}	t_image;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_image	no_tex;
	t_image	so_tex;
	t_image	we_tex;
	t_image	ea_tex;
	double	x_offset;
	double	y_offset;
	int		tex_x;
	int		tex_y;
	double	distance_diff;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;//in radian
}	t_player;

typedef struct s_render
{
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
}	t_render;

typedef struct s_ray
{
	int		face_right;
	int		face_left;
	int		face_up;
	int		face_down;
	double	h_hit_x;
	double	h_hit_y;
	double	h_distance;
	double	v_hit_x;
	double	v_hit_y;
	double	v_distance;
	double	final_hit_x;
	double	final_hit_y;
	double	final_distance;
	double	x_intersec;
	double	y_intersec;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	int		was_vertical;

}	t_ray;

typedef struct s_minimap
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		width;
	int		height;
	t_image	mini_img;
}	t_mini_mp;

typedef struct s_sprites
{
	t_image	frm[4];
	int		is_shooting;
	int		current_frame;
	int		frame_counter;
	int		animation_complete;
	int		sprite_x;
	int		sprite_y;
}	t_sprites;

typedef struct s_sound
{
	ma_engine	engine;
	ma_sound	w_sound;
	ma_sound	s_sound;
	int			is_engine;
	int			is_w;
	int			is_s;
}	t_sound;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	double		map_width;
	double		map_height;
	t_door		*doors;
	int			door_count;
	t_image		door_tex;
	t_player	player;
	t_color		colors;
	t_texture	tex;
	t_input		input;
	t_image		image;
	t_ray		ray;
	t_render	render;
	t_mini_mp	m_mp;
	t_sprites	sprt;
	t_sound		sound;
}	t_game;

void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	where_ray_face(double angle, t_game *data);
double	normalize_angle(double angle);
int		is_collesion(double x, double y, t_game *data);
double	r_distance(double x1, double y1, double x2, double y2);

void	clear_image(t_image *img, int color, int width, int height);
void	put_pixel_to_image(t_image *img, int x, int y, int color);

int		destroy(void *args);
void	cleanup_exit(char *message, t_game *data);

t_image	*get_texture(t_game *data);
double	get_x_offset(t_game *data);

int		key_release(int keycode, t_game *data);
int		key_press(int keycode, t_game *data);
void	move_controle(t_game *data);
void	init_player(t_game *data);
void	init_all_img(t_game *data);
void	cast_rays(double r_angle, t_game *data);
void	rendring3d(t_game *data, double r_angle, int i);
void	put_pixel_to_minimap(t_game *data, int x, int y, int color);
void	draw_minimap(t_game *data);
int		mouse_move(int x, int y, void *args);
void	draw_sprite(t_game *data);
void	update_sprite_animation(t_game *data);
void	init_sprites2(t_game *data, char *sp3);
void	init_sound(t_game *data);
void	sound_controle(t_game *data);
void	sound_controle2(t_game *data);
/* doors */
void	init_door(t_game *data);
void	interact_door(t_game *data);
int		get_door_idx(t_game *data, int mx, int my);
bool	door_is_open_at(t_game *data, int mx, int my);
/* -------------------------------------------------------------------------- */

bool	ft_isdigit(int c);
void	ft_exit(int status);
char	*get_next_line(int fd);
void	*ft_calloc(size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_scan_doors(t_game *data);
void	ft_bzero(void *s, size_t n);
int		ft_parse_rgb_string(char *s);
char	*ft_get_file(char *file_name);
void	ft_putendl_fd(char *s, int fd);
bool	ft_valid_file(char *file_name);
bool	ft_error(char *message, int fd);
char	*ft_append_str(char *s, char c);
bool	ft_parse_map(t_game *data, int fd);
void	parse(int ac, char **av, t_game *data);
void	ft_append_map(t_game *data, char *line);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
bool	ft_parse_instruction(t_game *data, char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
bool	ft_init_scene_data(char *file_name, t_game *data);
bool	ft_validate_line(char *line, char *prev_line, char *next_line);

#endif
