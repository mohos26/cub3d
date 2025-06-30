// int main() {
//     const char *cyan = "\033[38;2;0;255;255m";  // Bright Cyan
//     const char *reset = "\033[0m";

//     printf("%s \n███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    %s\n", cyan, reset);
//     printf("%s▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    %s\n", cyan, reset);
//     printf("%s▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    %s\n", cyan, reset);
//     printf("%s▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    %s\n", cyan, reset);
//     printf("%s▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒%s\n", cyan, reset);
//     printf("%s░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░%s\n", cyan, reset);
//     printf("%s░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░%s\n", cyan, reset);
//     printf("%s░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   %s\n", cyan, reset);
//     printf("%s       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░%s\n", cyan, reset);
// 	printf("\n\t\t\t\t🥇By: aouanni[Lomer] & abnaji-e🥇\n");
//     return 0;
// }


// export a="'"
// $als


#include <libc.h>
#include <string.h>
#include "mlx.h"
#include <math.h>
#include <limits.h>

#define tile 32
#define radius 8
#define mapwidth 20
#define maphigh 20
#define playerspeed 2//playersteps
#define rotationspeed 2//in degree
#define WIND_WIDTH 1680
#define WIND_HIGHT 1050
#define player_up 13
#define player_down 1
#define player_right 2
#define player_left 0
#define rotate_right 124
#define rotate_left 123
#define esc 53
#define FOV 60 //degree
#define RAYS_NUM WIND_WIDTH


char map[maphigh][mapwidth + 1] = {
    "11111111111111111111",
    "1E000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000110000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
	"10000000110000000001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "11111111111111111111"
};

typedef struct s_color
{
	double tail_c;
	double flor_c;
	double ceiling_c;
	double player_c;
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
} t_input;

typedef struct s_texture
{
	char *NO;
	char *SO;
	char *WE;
	char *WA;
}	t_texture;

typedef struct s_player
{
	double x;
	double y;
	double angle;//in degree
}	t_player;

typedef struct s_image
{
	void *img_ptr;
	char *data;
	int bbp;
	int row_len;
	int endian;
} t_image;

typedef struct s_ray
{
	int face_right;
	int face_left;
	int face_up;
	int face_dowm;
	double h_hit_x;
	double h_hit_y;
	double h_distance;
	double v_hit_x;
	double v_hit_y;
	double v_distance;
	double final_hit_x;
	double final_hit_y;
	double final_distance;
	int was_vertical;//need to know for what?
}	t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_player player;
	t_color colors;
	t_texture textures;
	t_input input;
	t_image image;
	t_ray ray;
}	t_game;

void	put_pixel_to_image(t_image *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= WIND_WIDTH || y >= WIND_HIGHT ||  y < 0)
		return ;
	dst = img->data + (y * img->row_len + x * (img->bbp / 8));
	*(unsigned *)dst=color;
}

void	clear_image(t_image *img, int color)
{
	int x,y;
	for(y = 0; y < WIND_HIGHT; y++)
	{
		for(x=0; x < WIND_WIDTH; x++)
		{
			put_pixel_to_image(img, (int)x, (int)y, color);
		}
	}
}

void	init(t_game *data)
{
	for (int y =0; y<maphigh; y++)
	{
		for(int x = 0; x < mapwidth; x++)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
			{
				data->player.x = x * tile + (tile/2);
				data->player.y = y * tile + (tile/2);
				if (map[y][x] == 'N') data->player.angle = 270.0;
				else if (map[y][x] == 'E') data->player.angle = 0.0;
				else if (map[y][x] == 'S') data->player.angle = 90.0;
				else if (map[y][x] == 'W') data->player.angle =  180.0;
				return ;
			}
		}

	}
}

void	draw_tile(int y, int x, t_game *data, int is_wall)
{
	for (int i = 0; i < tile; i++)
	{
		for (int j = 0; j < tile; j++)
		{
			if (is_wall)
				put_pixel_to_image(&data->image, x + j, y + i, data->colors.tail_c);
			else if (!is_wall)
				put_pixel_to_image(&data->image, x + j, y + i, 0);
		}
	}
}

void	draw_map(t_game *data)
{
	for (int y = 0; y < maphigh; y++)
	{
		for (int x=0; x < mapwidth; x++)
		{
			draw_tile(y * tile, x * tile, data, map[y][x] == '1');
		}
	}
}

int	is_wall(double x, double y)
{
int	wx = floor(x / tile);
int wy = floor(y / tile);
if (wx < 0 || wy < 0 || wx >= mapwidth || wy >= maphigh)
	return (1);
return (map[wy][wx] == '1');
}

int	key_press(int keycode, t_game *data)
{
	if (keycode == player_up)
		data->input.up = 1;
	if (keycode == player_down)
		data->input.down = 1;
	if (keycode == player_right)
		data->input.right = 1;
	if (keycode == player_left)
		data->input.left = 1;
	if (keycode == rotate_right)
		data->input.rot_right = 1;
	if (keycode == rotate_left)
		data->input.rot_left = 1;
	if (keycode == esc)
		data->input.escap = 1;
    return 0;
}

int	key_release(int keycode, t_game *data)
{
	if (keycode == player_up)
		data->input.up = 0;
	if (keycode == player_down)
		data->input.down = 0;
	if (keycode == player_right)
		data->input.right = 0;
	if (keycode == player_left)
		data->input.left = 0;
	if (keycode == rotate_right)
		data->input.rot_right = 0;
	if (keycode == rotate_left)
		data->input.rot_left = 0;
	if (keycode == esc)
		data->input.escap = 0;
    return 0;
}
void   draw_line(double angle, int len, double x, double y , int color , t_game *data)
{
	double dx = cos(angle * M_PI/180.0) * len;
	double dy = sin(angle * M_PI/180.0) * len;
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
	for (int i = -radius; i <=radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			if (pow(i, 2) + pow(j, 2) <= pow(radius, 2))
				put_pixel_to_image(&data->image, (int)(data->player.x + j), (int)(data->player.y + i), data->colors.player_c);
		}
	}
}



 void where_ray_face(double angle, t_game *data)
{
	data->ray.face_dowm = angle > 0 && angle < 180;
	data->ray.face_up = !data->ray.face_dowm;
	data->ray.face_right = angle > 270 || angle < 90;
	data->ray.face_left = !data->ray.face_right;

}

double r_distance(double x1, double y1 , double x2, double y2)
{
	return sqrt(pow(x2 - x1,2) + pow(y2 - y1, 2));
}

void hiro_intersec(double angle , t_game *data)
{
	double x_intersec;
	double y_intersec;
	double x_step;
	double y_step;
	angle *= M_PI / 180.0;

	y_intersec = floor(data->player.y / tile) * tile;
	if (data->ray.face_dowm)
		y_intersec += tile;
	x_intersec = data->player.x + (y_intersec - data->player.y) / tan(angle);
	y_step = tile;
	if (data->ray.face_up)
		y_step*=-1;
	x_step = tile / tan(angle);
	if ((data->ray.face_right && x_step < 0) || (data->ray.face_left && x_step > 0))
		x_step *=-1;
	double next_x = x_intersec;
	double next_y = y_intersec;
	int hit_found = 0;
	if (x_intersec < 0 || x_intersec >= mapwidth*tile || y_intersec < 0 || y_intersec >= maphigh*tile) {
    data->ray.h_distance = INFINITY;
    return;
}
	while (next_x >= 0 && next_x < mapwidth * tile && next_y >= 0 && next_y < maphigh * tile)
	{
		int map_x = (int)(next_x / tile);
		int map_y = (int)(next_y / tile);
		if (data->ray.face_up)
			map_y = (int)((next_y - 1) / tile);
		if (map_y >= 0 && map_y < maphigh && map_x >= 0 && map_x < mapwidth &&
		map[map_y][map_x] == '1')
		{
			hit_found = 1;
			data->ray.h_hit_x = next_x;
			data->ray.h_hit_y = next_y;
			data->ray.h_distance = r_distance(data->player.x, data->player.y, data->ray.h_hit_x, data->ray.h_hit_y);
			break;
		}
		next_x += x_step;
		next_y += y_step;
	}
	if(!hit_found)
		data->ray.h_distance = INT_MAX;
}
void vert_intersec(double angle , t_game *data)
{
	double x_intersec;
	double y_intersec;
	double x_step;
	double y_step;
	angle *= M_PI / 180.0;

	x_intersec = floor(data->player.x / tile) * tile;
	if (data->ray.face_right)
		x_intersec += tile;
	y_intersec = ((x_intersec - data->player.x) * tan(angle)) + data->player.y;
	x_step = tile;
	if (data->ray.face_left)
		x_step*=-1;
	y_step = tile * tan(angle);
	if ((data->ray.face_dowm && y_step < 0) || (data->ray.face_up && y_step > 0))
		y_step *=-1;
	double next_x = x_intersec;
	double next_y = y_intersec;
	int hit_found = 0;
	if (x_intersec < 0 || x_intersec >= mapwidth*tile || y_intersec < 0 || y_intersec >= maphigh*tile) {
    data->ray.v_distance = INFINITY;
    return;
}
	while (next_x >= 0 && next_x < mapwidth * tile && next_y >= 0 && next_y < maphigh * tile)
	{
		int map_x = (int)(next_x / tile);
		int map_y = (int)(next_y / tile);
		if (data->ray.face_left)
			map_x = (int)((next_x - 1) / tile);
		if (map_y >= 0 && map_y < maphigh && map_x >= 0 && map_x < mapwidth &&
    map[map_y][map_x] == '1')
		{
			hit_found = 1;
			data->ray.v_hit_x = next_x;
			data->ray.v_hit_y = next_y;
			data->ray.v_distance = r_distance(data->player.x, data->player.y, data->ray.v_hit_x, data->ray.v_hit_y);
			break;
		}
		next_x += x_step;
		next_y += y_step;
	}
	if(!hit_found)
		data->ray.v_distance =  INT_MAX;
}

double normalize_angle(double angle) {
    angle = fmod(angle, 360.0);
    if (angle < 0)
        angle += 360.0;
    return angle;
}

void	cast_rays(double angle, t_game *data)
{
	where_ray_face(angle, data);
	hiro_intersec(angle, data);
	vert_intersec(angle, data);
	if (data->ray.h_distance < data->ray.v_distance)
	{
		data->ray.final_hit_x = data->ray.h_hit_x;
		data->ray.final_hit_y = data->ray.h_hit_y;
		data->ray.final_distance = data->ray.h_distance;
		data->ray.was_vertical = 0;
	}
	else if (data->ray.v_distance < data->ray.h_distance)
	{
		data->ray.final_hit_x = data->ray.v_hit_x;
		data->ray.final_hit_y = data->ray.v_hit_y;
		data->ray.final_distance = data->ray.v_distance;
		data->ray.was_vertical = 1;
	}
}

void draw_line_DDA(int x0, int y0, int x1, int y1, int color, t_game *data)
{
    double dx = x1 - x0;
    double dy = y1 - y0;
    int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    double x_inc = dx / (double)steps;
    double y_inc = dy / (double)steps;
    double x = x0;
    double y = y0;
    for (int i = 0; i <= steps; i++) {
        put_pixel_to_image(&data->image, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}

void draw_FOV(t_game *data)
{
	double r_angle = data->player.angle - (FOV/2);
	for (double i = 0; i < RAYS_NUM; i++)
	// for (int i = 0; i < 1; i++)
	{
		r_angle = normalize_angle(r_angle);
		cast_rays(r_angle, data);
		draw_line_DDA((int)data->player.x, (int)data->player.y,
              (int)data->ray.final_hit_x, (int)data->ray.final_hit_y,
              14763060, data);
		r_angle += (double)FOV/RAYS_NUM;
	}
}

int	game_loop(void *args)
{
	t_game *data = (t_game*)args;
	double new_x;
	double new_y;
	double angle_rad = data->player.angle * M_PI/180.0;

	new_x = data->player.x;
	new_y = data->player.y;
	if (data->input.escap)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->image.img_ptr);
		exit(77);
	}
	if (data->input.up)
	{
		new_x += cos(angle_rad) * playerspeed;
		new_y += sin(angle_rad) * playerspeed;
	}
	if (data->input.down)
	{
		new_x -= cos(angle_rad) * playerspeed;
		new_y -= sin(angle_rad) * playerspeed;
	}
	if (data->input.right)
	{
		new_x += cos(angle_rad + M_PI_2) * playerspeed;
		new_y += sin(angle_rad + M_PI_2) * playerspeed;
	}
	if (data->input.left)
	{
		new_x += cos(angle_rad - M_PI_2) * playerspeed;
		new_y += sin(angle_rad - M_PI_2) * playerspeed;
	}
	if (data->input.rot_right)
		data->player.angle+=rotationspeed;
	if (data->input.rot_left)
		data->player.angle-=rotationspeed;
	data->player.angle = normalize_angle(data->player.angle);
	if (!is_wall(new_x, data->player.y))
        data->player.x = new_x;
    if (!is_wall(data->player.x, new_y))
        data->player.y = new_y;
	clear_image(&data->image, 0);
	draw_map(data);
	draw_FOV(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img_ptr, 0, 0);
	return 0;
}

int	destroy(void *args)
{
	t_game *data = (t_game *) args;
	exit(77);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->image.img_ptr);
	return 0;
}

int main()
{
	t_game data;
	memset(&data, 0, sizeof(t_game));
	data.colors.tail_c = 16710599;
	data.colors.player_c = 6204374;
	data.mlx=mlx_init();
	if (!data.mlx)
		exit(77);
	data.win=mlx_new_window(data.mlx, WIND_WIDTH, WIND_HIGHT, "where player facing");
	if (!data.win)
		exit(77);
	data.image.img_ptr = mlx_new_image(data.mlx, WIND_WIDTH, WIND_HIGHT);
	if (!data.image.img_ptr)
	{
		mlx_destroy_window(data.mlx, data.win);
		exit(77);
	}
	data.image.data= mlx_get_data_addr(data.image.img_ptr, &data.image.bbp, &data.image.row_len, &data.image.endian);
	init(&data);
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 3, 0, key_release, &data);
	mlx_hook(data.win, 17, 0, destroy, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
