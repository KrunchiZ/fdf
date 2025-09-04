/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:10:55 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 13:32:17 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define FIRST_BG	0
#define LAST_BG		3
#define LCLICK		1

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
			data->mod.bg = FIRST_BG;
	}
	if (keysym == XK_q)
	{
		data->mod.scale = (t_vect){0};
		data->mod.rotate = (t_vect){0};
		data->mod.cam2d = (t_vect){0};
	}
	return (SUCCESS);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	return (SUCCESS);
}

int	handle_mousepress(int button, int x, int y, t_data *data)
{
	int	x0;
	int	y0;

	if (button == LCLICK)
	{
		data->mod.mouse.drag = true;
		data->mod.mouse.x0 = x;
		data->mod.mouse.y0 = y;
	}
}

int	handle_mouserelease(int button, int x, int y, t_data *data)
{
	if (button == LCLICK)
		data->mod.mouse.drag = false;
}
