NAME		= fdf
LIBFT		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
IFLAGS		= -Ilibft/include -Iinclude
MLX_FLAGS	= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRC		= \
		  fdf_main.c				fdf_error.c				\
		  fdf_parse_map.c			fdf_parse_vertices.c	\
		  fdf_event_handler.c		fdf_color_handler.c		\
		  fdf_set_render_point.c	fdf_render_img.c		\
		  fdf_draw_map.c			fdf_draw_line.c

LIBFT_DIR	= libft/
SRC_DIR		= src/

vpath %.c $(SRC_DIR)

GREEN	= \e[32m
CYAN	= \e[36m
WHITE	= \e[0m

.PHONY: all fclean clean re
.SILENT:

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) $^ $(MLX_FLAGS) -o $@
	echo "Compiling $(GREEN)$(NAME)$(WHITE)..."

$(LIBFT):
	echo "Making $(GREEN)$(LIBFT)$(WHITE)..."
	make -C $(LIBFT_DIR)
	cp $(addprefix $(LIBFT_DIR), $(LIBFT)) $(LIBFT)

fclean: clean
	rm -f $(NAME)
	echo "Removing $(GREEN)$(NAME)$(WHITE)..."

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(LIBFT) $(LIBFT_DIR)/$(LIBFT)
	echo "Removing $(GREEN)$(LIBFT)$(WHITE)..."

re: fclean all
