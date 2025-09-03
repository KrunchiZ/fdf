/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:26 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 17:20:14 by kchiang          ###   ########.fr       */
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

# define SUCCESS		0
# define FAILURE		1
# define FRAME_WIDTH	1080
# define FRAME_HEIGHT	1080

# define PIXEL_WHITE	0xFFFFFF
# define PIXEL_GREY		0x555555
# define PIXEL_LTGREY	0xA0A0A0
# define PIXEL_BLACK	0x0
# define PIXEL_RED		0xFF0000
# define PIXEL_GREEN	0xFF00
# define PIXEL_BLUE		0xFF

# define BASE16_LOWER	"0123456789abcdef"

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
	int		color;
	float	red;
	float	green;
	float	blue;
}		t_vect;

typedef struct s_line
{
	t_vect	pt;
	float	xstep;
	float	ystep;
	float	rstep;
	float	gstep;
	float	bstep;
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
	int	bg;
}		t_mod;

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
int		handle_idle(t_data *data);
int		handle_keypress(int keysym, t_data *data);

void	setup3d(t_map *map, t_mod *mod);
void	img_px_put(t_img *img, int x, int y, int color);
int		render_img(t_data *data);
void	draw_line(t_img *img, t_vect p0, t_vect p1);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
uint8_t	get_red(int rgb);
uint8_t	get_green(int rgb);
uint8_t	get_blue(int rgb);

#endif
