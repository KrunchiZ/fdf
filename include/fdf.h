/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:26 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/23 16:52:34 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define FN_SUCCESS		0
# define FN_FAILURE		1
# define FRAME_WIDTH	1280
# define FRAME_HEIGHT	720

# define PIXEL_WHITE	0xFFFFFF
# define PIXEL_GREY		0x808080
# define PIXEL_BLACK	0x0
# define PIXEL_RED		0xFF0000
# define PIXEL_GREEN	0xFF00
# define PIXEL_BLUE		0xFF

typedef struct s_geo
{
	int	scale_x;
	int	scale_y;
	int	scale_z;
}		t_geo;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*pixels;
	int		bits_per_px;
	int		line_len;
	int		endian;
}			t_data;

int	encode_trgb(uint8_t transparency, uint8_t red, uint8_t green, uint8_t blue);
int	fn_handle_idle(t_data *data);
int	fn_handle_keypress(int keysym, t_data *data);
int	fn_handle_keyrelease(int keysym, t_data *data);

#endif
