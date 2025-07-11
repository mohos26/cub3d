/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoussas <mhoussas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:18:08 by aouanni           #+#    #+#             */
/*   Updated: 2025/07/09 16:44:48 by mhoussas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <string.h>
#include "mlx.h"
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define TILE 32
#define RADIUS 8 // for bonus
#define PLAYERSPEED 2
#define ROTATIONSPEED 2 // in degree
#define WIN_WIDTH 1680
#define WIN_HEIGHT 1050

#define PLAYER_UP 13
#define PLAYER_DOWN 1
#define PLAYER_RIGHT 2
#define PLAYER_LEFT 0
#define ROTATE_RIGHT 124
#define ROTATE_LEFT 123
#define ESC 53

#define FOV 60 // in degree
#define RAYS_NUM WIN_WIDTH

typedef struct s_color
{
	double tile_c;
	double flor_c;
	double ceiling_c;
	double player_c;
} t_color;

typedef struct s_input
{
	int up;
	int down;
	int right;
	int left;
	int rot_right;
	int rot_left;
	int escap;
} t_input;

typedef struct s_texture
{
	char *no;
	char *so;
	char *we;
	char *ea;
} t_texture;

typedef struct s_player
{
	double x;
	double y;
	double angle; // in radian
} t_player;

typedef struct s_image
{
	void *img_ptr;
	char *data;
	int bbp;
	int row_len;
	int endian;
} t_image;

typedef struct s_render
{
	double wall_height;
	double wall_top;
	double wall_bottom;
} t_render;

typedef struct s_ray
{
	int face_right;
	int face_left;
	int face_up;
	int face_down;
	double h_hit_x;
	double h_hit_y;
	double h_distance;
	double v_hit_x;
	double v_hit_y;
	double v_distance;
	double final_hit_x;
	double final_hit_y;
	double final_distance;
	double x_intersec;
	double y_intersec;
	double x_step;
	double y_step;
	double next_x;
	double next_y;
	int was_vertical;
} t_ray;

typedef struct s_game
{
	void *mlx;
	void *win;
	char **map;
	double map_width;
	double map_height;
	t_player player;
	t_color colors;
	t_texture textures;
	t_input input;
	t_image image;
	t_ray ray;
	t_render render;
} t_game;

#define BUFFER_SIZE 42

typedef struct s_data
{
	char **map;
	char *img_no;
	char *img_so;
	char *img_we;
	char *img_ea;
	int map_width;
	int map_height;
	int ceil_color;
	int floor_color;
} t_data;

void *ft_memset(void *b, int c, size_t len);
void ft_putstr_fd(char *s, int fd);
int key_release(int keycode, t_game *data);
int key_press(int keycode, t_game *data);
void cleanup_exit(char *message, t_game *data);
double normalize_angle(double angle);
int is_wall(double x, double y, t_game *data);
void init(t_game *data);
int destroy(void *args);
void cleanup_exit(char *message, t_game *data);
void put_pixel_to_image(t_image *img, int x, int y, int color);
void clear_image(t_image *img, int color);
void where_ray_face(double angle, t_game *data);
double r_distance(double x1, double y1, double x2, double y2);
void cast_rays(double r_angle, t_game *data);
void rendring3d(t_game *data, double r_angle, int i);
void move_controle(t_game *data);
void put_pixel_to_image(t_image *img, int x, int y, int color);
void parse(int ac, char **av, t_game *data);
bool ft_isdigit(int c);
char *get_next_line(int fd);
size_t ft_strlen(const char *s);
char *ft_strdup(const char *s1);
void ft_bzero(void *s, size_t n);
void ft_putendl_fd(char *s, int fd);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strjoin(char const *s1, char const *s2);
void *ft_memcpy(void *dst, const void *src, size_t n);
/* -------------------------------------------------------------------------- */

/* src */
void ft_exit(int status);
void *ft_calloc(size_t size);
char *ft_get_file(char *file_name);
bool ft_valid_file(char *file_name);
char *ft_append_str(char *s, char c);
t_data *ft_parse_map(t_data *ptr, int fd);
t_data *ft_init_scene_data(char *file_name);
void ft_append_map(t_data *ptr, char *line);
bool ft_parse_instruction(t_data *ptr, char *s);
bool ft_validate_line(char *line, char *prev_line, char *next_line);
