src_dir = Mandatory/
bonus_dir = Bonus/

SRC = $(src_dir)parse/aid/ft_bzero.c  $(src_dir)parse/aid/ft_isdigit.c  $(src_dir)parse/aid/ft_memcpy.c  $(src_dir)parse/aid/ft_putendl_fd.c  $(src_dir)parse/aid/ft_strcmp.c \
	$(src_dir)parse/aid/ft_strdup.c  $(src_dir)parse/aid/ft_strjoin.c  $(src_dir)parse/aid/ft_strlen.c  $(src_dir)parse/aid/get_next_line.c \
	$(src_dir)parse/ft_append_map.c  $(src_dir)parse/ft_append_rgb.c  $(src_dir)parse/ft_append_str.c  $(src_dir)parse/ft_error.c  $(src_dir)parse/ft_garbage_collector.c  $(src_dir)parse/ft_get_file.c  \
	$(src_dir)parse/ft_init_scene_data.c  $(src_dir)parse/ft_init_scene_data_utils.c  $(src_dir)parse/ft_parse_map.c  $(src_dir)parse/ft_parse_map_utils.c  $(src_dir)parse/ft_valid_file.c  $(src_dir)parse/parse.c  \
	$(src_dir)raycasting/init.c  $(src_dir)raycasting/main.c  $(src_dir)raycasting/move_controle.c  $(src_dir)raycasting/raycast.c  $(src_dir)raycasting/rendering.c \
	$(src_dir)raycasting/tools/calcule_distance.c  $(src_dir)raycasting/tools/clean_exit.c  $(src_dir)raycasting/tools/clear_image.c  $(src_dir)raycasting/tools/ft_memset.c  $(src_dir)raycasting/tools/is_wall.c  \
	$(src_dir)raycasting/tools/normalize_angle.c  $(src_dir)raycasting/tools/put_pixel_to_image.c  $(src_dir)raycasting/tools/putstr_fd.c  $(src_dir)raycasting/tools/rendreing_tools.c  $(src_dir)raycasting/tools/where_ray_face.c

BONUS = $(bonus_dir)parse/aid/ft_bzero_bonus.c  $(bonus_dir)parse/aid/ft_isdigit_bonus.c  $(bonus_dir)parse/aid/ft_memcpy_bonus.c  $(bonus_dir)parse/aid/ft_putendl_fd_bonus.c  $(bonus_dir)parse/aid/ft_strcmp_bonus.c \
	$(bonus_dir)parse/aid/ft_strdup_bonus.c  $(bonus_dir)parse/aid/ft_strjoin_bonus.c  $(bonus_dir)parse/aid/ft_strlen_bonus.c  $(bonus_dir)parse/aid/get_next_line_bonus.c \
	$(bonus_dir)parse/ft_append_map_bonus.c  $(bonus_dir)parse/ft_append_rgb_bonus.c  $(bonus_dir)parse/ft_append_str_bonus.c  $(bonus_dir)parse/ft_error_bonus.c  $(bonus_dir)parse/ft_garbage_collector_bonus.c  $(bonus_dir)parse/ft_get_file_bonus.c  \
	$(bonus_dir)parse/ft_init_scene_data_bonus.c  $(bonus_dir)parse/ft_init_scene_data_utils_bonus.c  $(bonus_dir)parse/ft_parse_map_bonus.c  $(bonus_dir)parse/ft_parse_map_utils_bonus.c  $(bonus_dir)parse/ft_valid_file_bonus.c  $(bonus_dir)parse/parse_bonus.c  \
	$(bonus_dir)raycasting/init_bonus.c  $(bonus_dir)raycasting/init2_bonus.c  $(bonus_dir)raycasting/main_bonus.c  $(bonus_dir)raycasting/move_controle_bonus.c  $(bonus_dir)raycasting/raycast_bonus.c  $(bonus_dir)raycasting/rendering_bonus.c \
	$(bonus_dir)raycasting/tools/calcule_distance_bonus.c  $(bonus_dir)raycasting/tools/clean_exit_bonus.c  $(bonus_dir)raycasting/tools/clear_image_bonus.c  $(bonus_dir)raycasting/tools/ft_memset_bonus.c  $(bonus_dir)raycasting/tools/is_wall_bonus.c  \
	$(bonus_dir)raycasting/tools/normalize_angle_bonus.c  $(bonus_dir)raycasting/tools/put_pixel_to_image_bonus.c  $(bonus_dir)raycasting/tools/putstr_fd_bonus.c  $(bonus_dir)raycasting/tools/rendreing_tools_bonus.c  $(bonus_dir)raycasting/tools/where_ray_face_bonus.c \
	$(bonus_dir)raycasting/sprites_bonus.c  $(bonus_dir)raycasting/minimap_bonus.c  $(bonus_dir)raycasting/mouse_rotation_bonus.c   $(bonus_dir)raycasting/tools/put_pixel_to_minimap_bonus.c



OBJS = $(SRC:.c=.o)

OBJB = $(BONUS:.c=.o)

NAME = cub3D
NAME_BONUS = cub3D_bonus
LIB = MLX/libmlx.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
LINK = -framework appkit -framework opengl
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(LINK) $(LIB) $(OBJS) -o $@

$(LIB):
	make -C MLX

$(src_dir)%.o: $(src_dir)%.c $(src_dir)cub.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJB) $(LIB)
	$(CC) $(CFLAGS) $(LINK) $(LIB) $(OBJB) -o $@

$(bonus_dir)%.o: $(bonus_dir)%.c $(bonus_dir)cub_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJB)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C MLX clean

re: fclean all
