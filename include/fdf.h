/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:51:26 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/23 15:15:26 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define FN_SUCCESS		0
# define FRAME_WIDTH	1280
# define FRAME_HEIGHT	720

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*pixels;
	int		bits_per_px;
	int		line_len;
	int		endian;
}			t_data;

int	fn_handle_idle(t_data *data);
int	fn_handle_keypress(int keysym, t_data *data);
int	fn_handle_keyrelease(int keysym, t_data *data);

#endif
