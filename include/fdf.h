/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:26 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/01 16:54:08 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define FN_SUCCESS		0
# define FN_FAILURE		1
# define FRAME_WIDTH	1080
# define FRAME_HEIGHT	1080

# define PIXEL_WHITE	0xFFFFFF
# define PIXEL_GREY		0x757575
# define PIXEL_BLACK	0x0
# define PIXEL_RED		0xFF0000
# define PIXEL_GREEN	0xFF00
# define PIXEL_BLUE		0xFF

# define BASE16_LOWER	"0123456789abcdef"

typedef struct s_vect
{
	int		x;
	int		y;
	int		z;
	int		color;
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
}		t_vect;

typedef struct s_line
{
	t_vect	pt;
	int		dx;
	int		dy;
	int		x_step;
	int		y_step;
	uint8_t	r_step;
	uint8_t	g_step;
	uint8_t	b_step;
	uint8_t	r_mod;
	uint8_t	g_mod;
	uint8_t	b_mod;
}			t_line;

typedef struct s_map
{
	t_vect	*vertices;
	t_vect	*render_pt;
	t_vect	center;
	int		vertex_count;
	int		width;
	int		depth;
	int		height;
	int		max_y;
	int		min_y;
}			t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*px;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_mod
{
	int	scale;
	int	multiplier;
	int	x_offset;
	int	y_offset;
}		t_mod;

typedef struct s_data
{
	t_map	map;
	t_img	img;
	t_mod	mod;
	void	*mlx;
	void	*window;
}			t_data;

void	fn_error_exit(char *str);
void	fn_perror_exit(char *str);
void	fn_delete_map(t_map *map);
void	fn_parse_map(t_map *map, char *file);
void	fn_parse_vertices(t_map *map, char *file);
int		fn_handle_idle(t_data *data);
int		fn_handle_keypress(int keysym, t_data *data);

void	fn_set_render_point(t_map *map, t_mod *mod);
void	fn_img_px_put(t_img *img, int x, int y, int color);
int		fn_render_img(t_data *data);
int		fn_draw_map(t_img *img, t_map *map);
void	fn_draw_line(t_img *img, t_vect pt0, t_vect pt1);
int		fn_encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
uint8_t	fn_get_red(int rgb);
uint8_t	fn_get_green(int rgb);
uint8_t	fn_get_blue(int rgb);

#endif
