/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:26 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/26 16:10:27 by kchiang          ###   ########.fr       */
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
	void	*mlx;
	void	*window;
	t_img	img;
}			t_data;

void	fn_error_exit(int exit_code);
int		fn_init_mlx(t_data *data);
int		fn_handle_idle(t_data *data);
int		fn_handle_keypress(int keysym, t_data *data);
int		fn_render_img(t_data *data);
int		fn_encode_trgb(uint8_t transparency,
			uint8_t red, uint8_t green, uint8_t blue);

#endif
