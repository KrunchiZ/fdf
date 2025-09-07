/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_idle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:47:42 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/07 18:06:02 by kchiang          ###   ########.fr       */
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
		transform_map(&data->map, &data->mod);
		if (data->mod.idle == false)
		{
			parse_edges(&data->map);
			data->mod.idle = true;
		}
		render_img(data);
	}
	return (SUCCESS);
}

static void	handle_keypress_xtransform(t_mod *mod, int keyhold)
{
	if (keyhold & KEY_DOWN && mod->viewmode == ISOMETRIC)
		mod->rotate.x -= 1.0f;
	if (keyhold & KEY_UP && mod->viewmode == ISOMETRIC)
		mod->rotate.x += 1.0f;
	return ;
}

static void	handle_keypress_ytransform(t_mod *mod, int keyhold)
{
	if (keyhold & KEY_LEFT && mod->viewmode != TOP)
		mod->rotate.y += 1.0f;
	if (keyhold & KEY_RIGHT && mod->viewmode != TOP)
		mod->rotate.y -= 1.0f;
	return ;
}

static void	handle_keypress_ztransform(t_mod *mod, int keyhold)
{
	if (keyhold & KEY_PERIOD)
		mod->rotate.z -= 1.0f;
	if (keyhold & KEY_COMMA)
		mod->rotate.z += 1.0f;
	return ;
}
