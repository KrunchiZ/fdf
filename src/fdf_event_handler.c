/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:10:55 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/23 16:56:33 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fn_render_rect(t_data *data)
{
	int	x;
	int	y;

	if (!data->win_ptr)
		return (FN_FAILURE);
	y = 200;
	while (y < 500)
	{
		x = 300;
		while (x < 900)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x++, y, PIXEL_WHITE);
		y++;
	}
	return (FN_SUCCESS);
}

int	fn_handle_idle(t_data *data)
{
	if (data->win_ptr)
		fn_render_rect(data);
	return (FN_SUCCESS);
}

int	fn_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (FN_SUCCESS);
}

int	fn_handle_keyrelease(int keysym, t_data *data)
{
	(void)data;
	(void)keysym;
	return (FN_SUCCESS);
}
