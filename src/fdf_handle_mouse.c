/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:49:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/10/22 21:23:41 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <stdbool.h>
#include "fdf.h"

static void	handle_button4(t_mod *mod);
static void	handle_button5(t_mod *mod);

int	handle_mousepress(int button, int x, int y, t_data *data)
{
	if (button == Button1)
	{
		data->mod.mouse.drag = true;
		data->mod.mouse.x0 = x;
		data->mod.mouse.y0 = y;
	}
	if (button == Button4)
		handle_button4(&data->mod);
	if (button == Button5)
		handle_button5(&data->mod);
	return (SUCCESS);
}

static void	handle_button4(t_mod *mod)
{
	mod->idle = false;
	if (mod->keyhold & KEY_X)
		mod->scale.x *= 1.1f;
	if (mod->keyhold & KEY_Y)
		mod->scale.y *= 1.1f;
	if (mod->keyhold & KEY_Z)
		mod->scale.z *= 1.1f;
	if (!(mod->keyhold & (KEY_X | KEY_Y | KEY_Z)))
	{
		mod->scale.x *= 1.1f;
		mod->scale.y *= 1.1f;
		mod->scale.z *= 1.1f;
	}
	return ;
}

static void	handle_button5(t_mod *mod)
{
	mod->idle = false;
	if (mod->keyhold & KEY_X)
		mod->scale.x *= 0.9f;
	if (mod->keyhold & KEY_Y)
		mod->scale.y *= 0.9f;
	if (mod->keyhold & KEY_Z)
		mod->scale.z *= 0.9f;
	if (!(mod->keyhold & (KEY_X | KEY_Y | KEY_Z)))
	{
		mod->scale.x *= 0.9f;
		mod->scale.y *= 0.9f;
		mod->scale.z *= 0.9f;
	}
	return ;
}

int	handle_mouserelease(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == Button1)
		data->mod.mouse.drag = false;
	return (SUCCESS);
}

int	handle_mouse1drag(int x, int y, t_data *data)
{
	if (data->mod.mouse.drag && !data->mod.mouse.rotate)
	{
		data->mod.idle = false;
		data->mod.translate_cam2d.x += x - data->mod.mouse.x0;
		data->mod.translate_cam2d.y += y - data->mod.mouse.y0;
		data->mod.mouse.x0 = x;
		data->mod.mouse.y0 = y;
	}
	else if (data->mod.mouse.drag && data->mod.mouse.rotate
		&& data->mod.viewmode != TOP)
	{
		data->mod.idle = false;
		data->mod.rotate.y += (x - data->mod.mouse.x0) * 0.5f;
		data->mod.mouse.x0 = x;
		data->mod.mouse.y0 = y;
	}
	return (SUCCESS);
}
