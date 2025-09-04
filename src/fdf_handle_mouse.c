/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:49:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 18:44:53 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mousepress(int button, int x, int y, t_data *data)
{
	if (button == Button1)
	{
		data->mod.mouse.drag = true;
		data->mod.mouse.x0 = x;
		data->mod.mouse.y0 = y;
	}
	if (button == Button4 && data->mod.scale_mode == true)
	{
		data->mod.scale.x += 0.1f;
		data->mod.scale.y += 0.1f;
		data->mod.scale.z += 0.1f;
	}
	if (button == Button5 && data->mod.scale_mode == true)
	{
		data->mod.scale.x -= 0.1f;
		data->mod.scale.y -= 0.1f;
		data->mod.scale.z -= 0.1f;
	}
	return (SUCCESS);
}

int	handle_mouserelease(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == Button1)
		data->mod.mouse.drag = false;
	return (SUCCESS);
}

int handle_mouse1drag(int x, int y, t_data *data)
{
	if (data->mod.mouse.drag == true)
	{
		data->mod.translate_cam2d.x += x - data->mod.mouse.x0;
		data->mod.translate_cam2d.y += y - data->mod.mouse.y0;
		data->mod.mouse.x0 = x;
		data->mod.mouse.y0 = y;
	}
	return (SUCCESS);
}
