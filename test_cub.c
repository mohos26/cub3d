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
#include "MLX/mlx.h"
#include <math.h>
#include <limits.h>

#define TILE 32
#define radius 5//bonus
#define mapwidth 20
#define maphigh 15
#define PLAYERSPEED 2	// playersteps
#define rotationspeed 2 // in degree
#define WIND_WIDTH 1680
#define WIND_HIGHT 1050
#define PLAYER_UP 13
#define PLAYER_DOWN 1
#define PLAYER_RIGHT 2
#define PLAYER_LEFT 0
#define ROTATE_RIGHT 124
#define ROTATE_LEFT 123
#define esc 53
#define FOV 60 // degree
#define RAYS_NUM WIND_WIDTH
#define SHOOT_KEY 7




#define TILE_2_SHOW 12//bonus
#define M_TILE_SIZE 12 //bonus
#define MINI_MAP_W (TILE_2_SHOW * M_TILE_SIZE)//bonus
#define MINI_MAP_H (TILE_2_SHOW * M_TILE_SIZE)//bonus

char map[maphigh][mapwidth + 1] = {
	"11111111111111111111",
	"10000000000000000001",
	"10000000000000000001",
	"100001S1000000000001",
	"10000010000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000110000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"10000000000000000001",
	"11111111111111111111",
};

typedef struct s_color
{
	double tail_c;
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
	int shoot;
} t_input;

typedef struct s_image
{
	void *img_ptr;
	char *data;
	int bbp;
	int row_len;
	int endian;
	int width;
	int height;
} t_image;
typedef struct s_texture
{
	// char *NO;
	// char *SO;
	// char *WE;
	// char *EA;
	t_image NO;
	t_image SO;
	t_image WE;
	t_image EA;
} t_texture;

typedef struct s_player
{
	double x;
	double y;
	double angle; // in degree
} t_player;


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
	int was_vertical; // need to know for what?
} t_ray;

typedef	struct s_sprites
{
	t_image shoot_frames[4];
	int is_shooting;
	int current_frame;
	int frame_counter;
	int width;
	int height;
}t_sprites;

typedef struct s_game
{
	void *mlx;
	void *win;
	int	prev_mouse_x;
	t_player player;
	t_color colors;
	t_texture textures;
	t_input input;
	t_image image;
	t_image minimap;//bonus
	t_sprites sprite;
	t_ray ray;
	// t_image wall_texture;//bonus
} t_game;

void	put_pixel_to_image(t_image *img, int x, int y, int color , int width, int hight)
{
	char *dst;

	if (x < 0 || x >= width || y >= hight ||  y < 0)
		return ;
	dst = img->data + (y * img->row_len + x * (img->bbp / 8));
	*(unsigned *)dst=color;
}

void	clear_image(t_image *img,int width, int height)
{
	int x,y;
	for(y = 0; y < height; y++)
	{
		for(x=0; x < width; x++)
		{
			put_pixel_to_image(img, (int)x, (int)y, 0, width, height);
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
				data->player.x = x * TILE + (TILE/2);
				data->player.y = y * TILE + (TILE/2);
				if (map[y][x] == 'N') data->player.angle = 270.0;
				else if (map[y][x] == 'E') data->player.angle = 0.0;
				else if (map[y][x] == 'S') data->player.angle = 90.0;
				else if (map[y][x] == 'W') data->player.angle =  180.0;
				return ;
			}
		}

	}
}

// void	draw_tile(int y, int x, t_game *data, int is_wall)
// {
// 	for (int i = 0; i < TILE; i++)
// 	{
// 		for (int j = 0; j < TILE; j++)
// 		{
// 			if (is_wall)
// 				put_pixel_to_image(&data->image, x + j, y + i, data->colors.tail_c);
// 			else if (!is_wall)
// 				put_pixel_to_image(&data->image, x + j, y + i, 0);
//         }
//     }
// }

// void	draw_map(t_game *data)
// {
//     for (int y = 0; y < maphigh; y++)
//     {
// 		for (int x=0; x < mapwidth; x++)
//         {
// 			draw_tile(y * TILE, x * TILE, data, map[y][x] == '1');
//         }
//     }
// }

int	is_wall(double x, double y)
{
int	wx = floor(x / TILE);
int wy = floor(y / TILE);
if (wx < 0 || wy < 0 || wx >= mapwidth || wy >= maphigh)
	return (1);
return (map[wy][wx] == '1');
}

int is_collesion(double x ,double y)
{
	if (is_wall(x + radius, y) || is_wall(x - radius, y)
		|| is_wall(x, y+radius) || is_wall(x, y-radius) || is_wall(x, y))
			return 1;
	return 0;
}

int	key_press(int keycode, t_game *data)
{
	if (keycode == PLAYER_UP)
		data->input.up = 1;
	if (keycode == PLAYER_DOWN)
		data->input.down = 1;
	if (keycode == PLAYER_RIGHT)
		data->input.right = 1;
	if (keycode == PLAYER_LEFT)
		data->input.left = 1;
	if (keycode == ROTATE_RIGHT)
		data->input.rot_right = 1;
	if (keycode == ROTATE_LEFT)
		data->input.rot_left = 1;
	if (keycode == esc)
		data->input.escap = 1;
if (keycode == SHOOT_KEY && !data->sprite.is_shooting) // Prevent rapid shooting
    {
        data->input.shoot = 1;
        data->sprite.is_shooting = 1;
        data->sprite.current_frame = 0; // Start with first shoot frame
        data->sprite.frame_counter = 0;
    }
    return 0;
}

int	key_release(int keycode, t_game *data)
{
	if (keycode == PLAYER_UP)
		data->input.up = 0;
	if (keycode == PLAYER_DOWN)
		data->input.down = 0;
	if (keycode == PLAYER_RIGHT)
		data->input.right = 0;
	if (keycode == PLAYER_LEFT)
		data->input.left = 0;
	if (keycode == ROTATE_RIGHT)
		data->input.rot_right = 0;
	if (keycode == ROTATE_LEFT)
		data->input.rot_left = 0;
	if (keycode == esc)
		data->input.escap = 0;
	if (keycode == SHOOT_KEY)
        data->input.shoot = 0;
    return 0;
}
// void   draw_line(double angle, int len, double x, double y , int color , t_game *data)
// {
// 	double dx = cos(angle * M_PI/180.0) * len;
// 	double dy = sin(angle * M_PI/180.0) * len;
// 	for(int i = 0; i < len; i++)
// 	{
// 		int px = x + dx * i / len;
// 		int py = y + dy * i / len;
// 		put_pixel_to_image(&data->image, px, py, color);
// 	}
// }
void	draw_player(int x, int y, t_game *data)//bonus
{
	for (int i = -radius; i <=radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			if (pow(i, 2) + pow(j, 2) <= pow(radius, 2))
				put_pixel_to_image(&data->minimap, (int)(x + j) , (int)(y + i) , data->colors.player_c, MINI_MAP_W, MINI_MAP_H);
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

void hiro_intersec(double angle, t_game *data)
{
	double x_intersec;
	double y_intersec;
	double x_step;
	double y_step;
	angle *= M_PI / 180;

	y_intersec = floor(data->player.y / TILE) * TILE;
	if (data->ray.face_dowm)
		y_intersec += TILE;
	x_intersec = data->player.x + (y_intersec - data->player.y) / tan(angle);
	y_step = TILE;
	if (data->ray.face_up)
		y_step *= -1;
	x_step = TILE / tan(angle);
	if ((data->ray.face_right && x_step < 0) || (data->ray.face_left && x_step > 0))
		x_step *= -1;
	double next_x = x_intersec;
	double next_y = y_intersec;
	int hit_found = 0;

	while (next_x >= 0 && next_x < mapwidth * TILE && next_y >= 0 && next_y < maphigh * TILE)
	{
		int map_x = (int)(next_x / TILE);
		int map_y = (int)(next_y / TILE);
		if (data->ray.face_up)
			map_y = (int)((next_y - 1) / TILE);
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
	if (!hit_found)
		data->ray.h_distance = INFINITY;
}
void vert_intersec(double angle, t_game *data)
{
	double x_intersec;
	double y_intersec;
	double x_step;
	double y_step;
	angle *= M_PI / 180;

	x_intersec = floor(data->player.x / TILE) * TILE;
	if (data->ray.face_right)
		x_intersec += TILE;
	y_intersec = ((x_intersec - data->player.x) * tan(angle)) + data->player.y;
	x_step = TILE;
	if (data->ray.face_left)
		x_step *= -1;
	y_step = TILE * tan(angle);
	if ((data->ray.face_dowm && y_step < 0) || (data->ray.face_up && y_step > 0))
		y_step *= -1;
	double next_x = x_intersec;
	double next_y = y_intersec;
	int hit_found = 0;
	while (next_x >= 0 && next_x < mapwidth * TILE && next_y >= 0 && next_y < maphigh * TILE)
	{
		int map_x = (int)(next_x / TILE);
		int map_y = (int)(next_y / TILE);
		if (data->ray.face_left)
			map_x = (int)((next_x - 1) / TILE);
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
	if (!hit_found)
		data->ray.v_distance = INFINITY;
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
	if (data->ray.h_distance <= data->ray.v_distance)
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

// void draw_line_bresenham(int x0, int y0, int x1, int y1, int color, t_game *data)
// {
//     int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
//     int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
//     int err = dx + dy, e2;

//     while (1) {
//         put_pixel_to_image(&data->image, x0, y0, color);
//         if (x0 == x1 && y0 == y1) break;
//         e2 = 2 * err;
//         if (e2 >= dy) { err += dy; x0 += sx; }
//         if (e2 <= dx) { err += dx; y0 += sy; }
//     }
// }

void draw_wall(double wall_top, double wall_bouttom, t_game *data, double x, double r_angle, double wal_height)
{
// 	for (int y = wall_top; y <= wall_bouttom; y++)
// 	{
// 		if (data->ray.was_vertical && data->ray.face_right)//red
// 			put_pixel_to_image(&data->image, x, y, 16711680, WIND_WIDTH, WIND_HIGHT);
// 		else if (data->ray.was_vertical && data->ray.face_left)//green
// 			put_pixel_to_image(&data->image, x, y, 65280, WIND_WIDTH, WIND_HIGHT);
// 		else if (!data->ray.was_vertical && data->ray.face_dowm) // blue
// 			put_pixel_to_image(&data->image, x, y, 255, WIND_WIDTH, WIND_HIGHT);
// 		else
// 			put_pixel_to_image(&data->image, x, y, 16777215, WIND_WIDTH, WIND_HIGHT);
//  }
t_image *current;
if (data->ray.was_vertical && data->ray.face_right)
	current = &data->textures.EA;
else if (data->ray.was_vertical && data->ray.face_left)
	current = &data->textures.WE;
else if (!data->ray.was_vertical && data->ray.face_up)
	current = &data->textures.NO;
else if (!data->ray.was_vertical && data->ray.face_dowm)
	current = &data->textures.SO;
if (x < 0 || x >= WIND_WIDTH)
	return ;
	double x_offset ;
	if (data->ray.was_vertical)
		x_offset = fmod(data->ray.final_hit_y, TILE);
	else
		x_offset =fmod(data->ray.final_hit_x, TILE);
	int tex_x = (x_offset / TILE) * current->width;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= current->width)
		tex_x = current->width - 1;
	int y = wall_top;
	while (y < wall_bouttom)
	{
		double distance_form_top = (y + (wal_height / 2) - (WIND_HIGHT / 2));
		int tex_y = (int)((distance_form_top / wal_height) * current->height);
		if (tex_y < 0)
			tex_y= 0;
		else if (tex_y >= current->height)
			tex_y = current->height - 1;
		char *p = current->data + (tex_y * current->row_len) + (tex_x * (current->bbp / 8));
		int color = *(unsigned int *)p;
		put_pixel_to_image(&data->image, x, y, color, WIND_WIDTH, WIND_HIGHT);
		y++;
	}
}

void rendring3d(t_game *data, double r_angle, int i)
{
	double angle = (FOV / 2) * (M_PI / 180);
	double project_plan_distance = (WIND_WIDTH / 2) / tan(angle);

	double ray_angle_diff = (r_angle - data->player.angle) * (M_PI / 180.0);
	double corrected_distance = data->ray.final_distance * cos(ray_angle_diff);

	double wall_hight = (TILE / corrected_distance) * project_plan_distance;
	double wall_top = (WIND_HIGHT / 2) - (wall_hight / 2);
	if (wall_top < 0)
		wall_top = 0;
	double wall_bottom = (WIND_HIGHT / 2) + (wall_hight / 2);
	if (wall_bottom > WIND_HIGHT)
		wall_bottom = WIND_HIGHT;
	for (int y = 0; y < wall_top && y < WIND_HIGHT; y++)
		put_pixel_to_image(&data->image, i, y, data->colors.ceiling_c, WIND_WIDTH, WIND_HIGHT);
	for (int y = wall_bottom; y < 	WIND_HIGHT; y++)
		put_pixel_to_image(&data->image, i, y, data->colors.flor_c, WIND_WIDTH, WIND_HIGHT);
	draw_wall(wall_top, wall_bottom, data, i, r_angle, wall_hight);
}

void draw_FOV(t_game *data)
{
	double r_angle = data->player.angle - (FOV / 2);
	for (double i = 0; i < RAYS_NUM; i++)
	// for (int i = 0; i < 1; i++)
	{
		r_angle = normalize_angle(r_angle);
		cast_rays(r_angle, data);
		rendring3d(data, r_angle, i);
		// draw_line_bresenham((int)data->player.x, (int)data->player.y,
		//             (int)data->ray.final_hit_x, (int)data->ray.final_hit_y,
		//             0xFF0000, data);
		r_angle += (double)FOV / RAYS_NUM;
	}
}

void draw_minimap_tiles(int x, int y, int color, t_image *img)//bonus
{
	for (int pixel_y = y; pixel_y < y + M_TILE_SIZE; pixel_y++)
	{
		for (int pixel_x = x; pixel_x < x + M_TILE_SIZE; pixel_x++)
		{
			put_pixel_to_image(img, pixel_x, pixel_y, color, MINI_MAP_W, MINI_MAP_H);
		}
	}
}

void	draw_minimap(t_game *data)//bonus
{
	clear_image(&data->minimap, MINI_MAP_W, MINI_MAP_H);
	int player_x = floor(data->player.x / TILE);
	int player_y = floor(data->player.y / TILE);
	int half_tiles = TILE_2_SHOW / 2;
	int map_start_x = player_x - half_tiles;
	int map_start_y = player_y - half_tiles;
	int map_end_x = player_x + half_tiles;
	int map_end_y = player_y + half_tiles;
	for (int map_y = map_start_y; map_y < map_end_y; map_y++)
	{
		for (int map_x = map_start_x; map_x < map_end_x; map_x++)
		{
			int tile_color;
			if (map_x < 0 || map_x >= mapwidth || map_y < 0 || map_y  >= maphigh)
				tile_color = data->colors.tail_c;
			else
			{
				if (map[map_y][map_x] == '1')
					tile_color = data->colors.tail_c;
				else
					tile_color = 0;
			}
			int minimap_tile_x = (map_x - map_start_x) * M_TILE_SIZE;
			int minimap_tile_y = (map_y - map_start_y) * M_TILE_SIZE;
			draw_minimap_tiles(minimap_tile_x , minimap_tile_y, tile_color, &data->minimap);
		}
	}
	for (int  y = 0; y  < MINI_MAP_H; y++)
	{
		for (int x  = 0; x < MINI_MAP_W; x ++)
		{
			if (x >= MINI_MAP_W - 2 || y >= MINI_MAP_H - 2)
				put_pixel_to_image(&data->minimap, x, y, 16777215, MINI_MAP_W, MINI_MAP_H);
		}
	}
	int player_minimap_x = MINI_MAP_W / 2;
	int player_minimap_y = MINI_MAP_H / 2;
	draw_player(player_minimap_x, player_minimap_y, data);
}


void update_sprite_animation(t_game *data)
{
    if (!data->sprite.is_shooting)
    {
        data->sprite.current_frame = 0;
        return;
    }

    data->sprite.frame_counter++;

    if (data->sprite.frame_counter >= 5)
    {
        data->sprite.frame_counter = 0;
        data->sprite.current_frame++;

        if (data->sprite.current_frame >= 3)
        {
            data->sprite.is_shooting = 0;
            data->sprite.current_frame = 0;
        }
    }
}

void draw_sprite(t_game *data)
{
    int sprite_x = (WIND_WIDTH - data->sprite.width) / 2;
	int sprite_y = WIND_HIGHT - data->sprite.height + 10;

    t_image *current_sprite = &data->sprite.shoot_frames[data->sprite.current_frame];
    mlx_put_image_to_window(data->mlx, data->win, current_sprite->img_ptr, sprite_x, sprite_y);
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
		new_x += cos(angle_rad) * PLAYERSPEED;
		new_y += sin(angle_rad) * PLAYERSPEED;
	}
	if (data->input.down)
	{
		new_x -= cos(angle_rad) * PLAYERSPEED;
		new_y -= sin(angle_rad) * PLAYERSPEED;
	}
	if (data->input.right)
	{
		new_x += cos(angle_rad + M_PI_2) * PLAYERSPEED;
		new_y += sin(angle_rad + M_PI_2) * PLAYERSPEED;
	}
	if (data->input.left)
	{
		new_x += cos(angle_rad - M_PI_2) * PLAYERSPEED;
		new_y += sin(angle_rad - M_PI_2) * PLAYERSPEED;
	}
	if (data->input.rot_right)
		data->player.angle+=rotationspeed;
	if (data->input.rot_left)
		data->player.angle-=rotationspeed;
	data->player.angle = normalize_angle(data->player.angle);
	if (!is_collesion(new_x, data->player.y))
        data->player.x = new_x;
    if (!is_collesion(data->player.x, new_y))
        data->player.y = new_y;
	update_sprite_animation(data);
	clear_image(&data->image,WIND_WIDTH, WIND_HIGHT);
	// draw_map(data);
	draw_FOV(data);
	draw_minimap(data);//bonus
	// draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr, 0, 0);//bonus
	draw_sprite(data);
	return 0;
}


int	destroy(void *args)
{
	t_game *data = (t_game *) args;
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->image.img_ptr);
	mlx_destroy_image(data->mlx, data->minimap.img_ptr);//bonus
	exit(77);
	return 0;
}

int	mouse_move(int x, int y, void *args)//for bonus
{
	t_game *data;
	int dx;

	data = (t_game *)args;
	int center_x = WIND_WIDTH / 2;
	int center_y = WIND_HIGHT / 2;
	if (x == center_x && y == center_y)
		return 0;
	dx = x - center_x;
	data->player.angle += dx * 0.05;
	data->player.angle = normalize_angle(data->player.angle);
	mlx_mouse_move(data->win, center_x, center_y);
	return (0);
}


int main()
{
	t_game data;
	memset(&data, 0, sizeof(t_game));
	data.colors.tail_c = 16710599;
	data.colors.player_c = 6204374;
	data.colors.flor_c =6710886;
	data.colors.ceiling_c = 12186367;
	data.prev_mouse_x = 0;
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
	data.image.data= mlx_get_data_addr(data.image.img_ptr, &data.image.bbp, &data.image.row_len, &data.image.endian);//bonus
	data.minimap.img_ptr = mlx_new_image(data.mlx, MINI_MAP_W, MINI_MAP_H);//bonus
	if (!data.minimap.img_ptr)//bonus
	{
		mlx_destroy_window(data.mlx, data.win);
		exit(77);
	}
	data.minimap.data = mlx_get_data_addr(data.minimap.img_ptr, &data.minimap.bbp, &data.minimap.row_len, &data.minimap.endian);//bonus
	data.sprite.shoot_frames[0].img_ptr = mlx_xpm_file_to_image(data.mlx, "sprites1/idle-gun.xpm", &data.sprite.width, &data.sprite.height);
	data.sprite.shoot_frames[0].data = mlx_get_data_addr(data.sprite.shoot_frames[0].img_ptr, &data.sprite.shoot_frames[0].bbp, &data.sprite.shoot_frames[0].row_len, &data.sprite.shoot_frames[0].endian);

	data.sprite.shoot_frames[1].img_ptr = mlx_xpm_file_to_image(data.mlx, "sprites1/shoot-1.xpm", &data.sprite.width, &data.sprite.height);
	data.sprite.shoot_frames[1].data = mlx_get_data_addr(data.sprite.shoot_frames[1].img_ptr, &data.sprite.shoot_frames[1].bbp, &data.sprite.shoot_frames[1].row_len, &data.sprite.shoot_frames[1].endian);

	data.sprite.shoot_frames[2].img_ptr = mlx_xpm_file_to_image(data.mlx, "sprites1/shoot-2.xpm", &data.sprite.width, &data.sprite.height);
	data.sprite.shoot_frames[2].data = mlx_get_data_addr(data.sprite.shoot_frames[2].img_ptr, &data.sprite.shoot_frames[2].bbp, &data.sprite.shoot_frames[2].row_len, &data.sprite.shoot_frames[2].endian);

 	data.sprite.is_shooting = 0;
    data.sprite.current_frame = 0; // Start with idle frame
    data.sprite.frame_counter = 0;
	// data.wall_texture.img_ptr = mlx_xpm_file_to_image(data.mlx, "REDBRICKS.xpm", &data.wall_texture.width, &data.wall_texture.height);
	// data.wall_texture.data = mlx_get_data_addr(data.wall_texture.img_ptr, &data.wall_texture.bbp, &data.wall_texture.row_len, &data.wall_texture.endian);
	data.textures.NO.img_ptr = mlx_xpm_file_to_image(data.mlx, "textures/1.xpm", &data.textures.NO.width, &data.textures.NO.height);
	data.textures.NO.data = mlx_get_data_addr(data.textures.NO.img_ptr, &data.textures.NO.bbp, &data.textures.NO.row_len, &data.textures.NO.endian);
	data.textures.SO.img_ptr = mlx_xpm_file_to_image(data.mlx, "textures/2.xpm", &data.textures.SO.width, &data.textures.SO.height);
	data.textures.SO.data = mlx_get_data_addr(data.textures.SO.img_ptr, &data.textures.SO.bbp, &data.textures.SO.row_len, &data.textures.SO.endian);
	data.textures.EA.img_ptr = mlx_xpm_file_to_image(data.mlx, "textures/3.xpm", &data.textures.EA.width, &data.textures.EA.height);
	data.textures.EA.data = mlx_get_data_addr(data.textures.EA.img_ptr, &data.textures.EA.bbp, &data.textures.EA.row_len, &data.textures.EA.endian);
	data.textures.WE.img_ptr = mlx_xpm_file_to_image(data.mlx, "textures/4.xpm", &data.textures.WE.width, &data.textures.WE.height);
	data.textures.WE.data = mlx_get_data_addr(data.textures.WE.img_ptr, &data.textures.WE.bbp, &data.textures.WE.row_len, &data.textures.WE.endian);
	init(&data);
	mlx_mouse_hide();
	mlx_hook(data.win, 2, 0, key_press, &data);
	mlx_hook(data.win, 3, 0, key_release, &data);
	mlx_hook(data.win, 17, 0, destroy, &data);
	mlx_hook(data.win, 6, 0, mouse_move, &data);//for bonus!!!
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
}
