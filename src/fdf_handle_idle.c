/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_idle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:47:42 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/09 17:01:31 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_keypress_xtransform(t_mod *mod, int keyhold);
static void	handle_keypress_ytransform(t_mod *mod, int keyhold);
static void	handle_keypress_ztransform(t_mod *mod, int keyhold);
static void	print_message(t_data *data);

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
			parse_edges(&data->map, data->mod.viewmode);
			data->mod.idle = true;
		}
		render_img(data);
		print_message(data);
	}
	return (SUCCESS);
}

static void	print_message(t_data *data)
{
	mlx_string_put(data->mlx, data->window, 10, 30, PIXEL_BLUE,
		" +:+#+ FDF Controls +#+:+ ");
	mlx_string_put(data->mlx, data->window, 10, 60, PIXEL_BLUE,
		" [esc]    = Exit           [u] = Reset transform");
	mlx_string_put(data->mlx, data->window, 10, 80, PIXEL_BLUE,
		" [up]     = ++Rotate-X     [down] = --Rotate-X");
	mlx_string_put(data->mlx, data->window, 10, 100, PIXEL_BLUE,
		" [left]   = ++Rotate-Y     [right] = --Rotate-Y");
	mlx_string_put(data->mlx, data->window, 10, 120, PIXEL_BLUE,
		" [,]      = ++Rotate-Z     [.] = --Rotate-Z");
	mlx_string_put(data->mlx, data->window, 10, 140, PIXEL_BLUE,
		" [mouse1] = (Hold & Drag) 2D Camera-Pan");
	mlx_string_put(data->mlx, data->window, 10, 160, PIXEL_BLUE,
		" [scroll] = Uniform scaling");
	mlx_string_put(data->mlx, data->window, 10, 180, PIXEL_BLUE,
		" [b]      = Change background color");
	return ;
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
