SOURCES=\
	src/main.c \
	src/parsing.c \
	src/parsing_utils.c \
	src/parse_data.c \
	src/init_data.c \
	src/errors.c \
	src/extract_map_info.c \
	src/extract_map_2.c \
	src/manage_colors.c \
	src/creation_map.c \
	src/parse_map.c \
	src/parse_map_2.c \
	src/valid_char_in_map.c \
	src/find_player_pos.c \
	src/parse_textures.c \
	src/key_press.c \
	src/clean_exit.c \
	src/free_utils.c \
	src/init_player_dir.c \
	src/render.c \
	src/render_2.c \
	src/raycasting_utils.c \
	src/line_utils.c \

OBJECTS=$(SOURCES:.c=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)

NAME=cub3D
CC=clang

OPTS=-O2 -fno-builtin
DEBUG=-g3
CFLAGS=-Imlx -Ilibft -MMD $(OPTS) $(DEBUG) -Wall -Wextra #-Werror

all: $(NAME)

-include $(DEPENDENCIES)

libft/libft.a:
	make -C libft

mlx/libmlx.a:
	make -C mlx

$(NAME): $(OBJECTS) libft/libft.a mlx/libmlx.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) libft/libft.a mlx/libmlx.a -lm -lX11 -lXext $(LDFLAGS)

clean:
	rm -rf $(OBJECTS) $(DEPENDENCIES) 
	make -C mlx clean
	make -C libft fclean

fclean: clean
	rm -f cub3d

re: fclean all