/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_idle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:47:42 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/07 19:20:12 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_keypress_xtransform(t_mod *mod, int keyhold);
static void	handle_keypress_ytransform(t_mod *mod, int keyhold);
static void	handle_keypress_ztransform(t_mod *mod, int keyhold);

int	handle_idle(t_data *data)
{
	handle_keypress_xtransform(&data->mod, data->mod.keyhold);
	handle_keypress_ytransform(&data->mod, data->mod.keyhold);
	handle_keypress_ztransform(&data->mod, data->mod.keyhold);
	if (data->window)
	{
		if (data->mod.idle == false)
		{
			transform_map(&data->map, &data->mod);
			parse_edges(&data->map);
			data->mod.idle = true;
		}
		render_img(data);
	}
	return (SUCCESS);
}

static void	handle_keypress_xtransform(t_mod *mod, int keyhold)
{
	if (keyhold & KEY_DOWN)
	{
		mod->idle = false;
		mod->rotate.x -= 1.0f;
	}
	if (keyhold & KEY_UP)
	{
		mod->idle = false;
		mod->rotate.x += 1.0f;
	}
	return ;
}

static void	handle_keypress_ytransform(t_mod *mod, int keyhold)
{
	if (keyhold & KEY_LEFT)
	{
		mod->idle = false;
		mod->rotate.y += 1.0f;
	}
	if (keyhold & KEY_RIGHT)
	{
		mod->idle = false;
		mod->rotate.y -= 1.0f;
	}
	return ;
}

static void	handle_keypress_ztransform(t_mod *mod, int keyhold)
{
	if (keyhold & KEY_PERIOD)
	{
		mod->idle = false;
		mod->rotate.z -= 1.0f;
	}
	if (keyhold & KEY_COMMA)
	{
		mod->idle = false;
		mod->rotate.z += 1.0f;
	}
	return ;
}
