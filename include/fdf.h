/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:26 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/07 18:06:37 by kchiang          ###   ########.fr       */
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
# include <math.h>

# define TITLE			"FDF by kchiang"
# define FRAME_WIDTH	1080
# define FRAME_HEIGHT	1080

# define SUCCESS		0
# define FAILURE		1

# define ISOMETRIC		0
# define FRONT			1
# define SIDE			2
# define TOP			3

# define PIXEL_WHITE	0xFFFFFF
# define PIXEL_GREY		0x555555
# define PIXEL_LTGREY	0xA0A0A0
# define PIXEL_BLACK	0x0
# define PIXEL_RED		0xFF0000
# define PIXEL_GREEN	0xFF00
# define PIXEL_BLUE		0xFF

# define BASE16_LOWER	"0123456789abcdef"

# define KEY_UP			0b1
# define KEY_DOWN		0b10
# define KEY_LEFT		0b100
# define KEY_RIGHT		0b1000
# define KEY_COMMA		0b10000
# define KEY_PERIOD		0b100000

typedef struct s_mtrx
{
	float	x[3][3];
	float	y[3][3];
	float	z[3][3];
	float	ab[3][3];
	float	abc[3][3];
}			t_mtrx;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
	float	red;
	float	green;
	float	blue;
	int		color;
}			t_vect;

typedef struct s_edge
{
	t_vect	start;
	t_vect	end;
}			t_edge;

typedef struct s_line
{
	t_vect	pt;
	float	dx;
	float	dy;
	float	xstep;
	float	ystep;
	float	rstep;
	float	gstep;
	float	bstep;
}			t_line;

typedef struct s_mouse
{
	int		drag;
	int		x0;
	int		y0;
}			t_mouse;

typedef struct s_mod
{
	t_mtrx	rotate_matrix;
	t_vect	viewangle[4];
	t_vect	scale;
	t_vect	rotate;
	t_vect	translate_cam2d;
	t_mouse	mouse;
	int		scale_multiplier;
	int		keyhold;
	int		viewmode;
	int		x_offset;
	int		y_offset;
	int		bg;
	int		idle;
}			t_mod;

typedef struct s_map
{
	t_vect	*vertices;
	t_vect	*render_pt;
	t_edge	*edges;
	int		vertex_count;
	int		edge_count;
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

typedef struct s_data
{
	t_map	map;
	t_img	img;
	t_mod	mod;
	void	*mlx;
	void	*window;
}			t_data;

void	error_exit(char *str);
void	perror_exit(char *str);
void	delete_map(t_map *map);
void	parse_map(t_map *map, char *file);
void	parse_vertices(t_map *map, char *file);
void	set_modifier(t_mod *mod, t_map *map);

int		handle_idle(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		handle_keyrelease(int keysym, t_data *data);
int		handle_mousepress(int button, int x, int y, t_data *data);
int		handle_mouserelease(int button, int x, int y, t_data *data);
int		handle_mouse1drag(int x, int y, t_data *data);

void	transform_map(t_map *map, t_mod *mod);
void	calc_rotate_matrix(t_mod *mod);
void	parse_edges(t_map *map);

int		render_img(t_data *data);
void	draw_line(t_img *img, t_vect p0, t_vect p1);
void	img_px_put(t_img *img, int x, int y, int color);

int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
uint8_t	get_red(int rgb);
uint8_t	get_green(int rgb);
uint8_t	get_blue(int rgb);

#endif
