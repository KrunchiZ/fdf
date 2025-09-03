/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:10:55 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 01:27:14 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define BG_GREY	0
#define LAST_BG	3

int	handle_idle(t_data *data)
{
	if (data->window)
	{
		transform_map(&data->map, &data->mod);
		render_img(data);
	}
	return (SUCCESS);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->window);
		data->window = NULL;
	}
	if (keysym == XK_b)
	{
		data->mod.bg++;
		if (data->mod.bg > LAST_BG)
			data->mod.bg = BG_GREY;
	}
	if (keysym == XK_q)
	{
		data->mod.scale = (t_vect){0};
		data->mod.rotate = (t_vect){.x = 35.264f, .y = 45.0f};
		data->mod.translate = (t_vect){0};
	}
	return (SUCCESS);
}
