/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_idle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:47:42 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 16:41:19 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_keypress_xtransform(t_mod *mod, t_key *keyhold);
static void	handle_keypress_ytransform(t_mod *mod, t_key *keyhold);
static void	handle_keypress_ztransform(t_mod *mod, t_key *keyhold);

int	handle_idle(t_data *data)
{
	handle_keypress_xtransform(&data->mod, &data->mod.keyhold);
	handle_keypress_ytransform(&data->mod, &data->mod.keyhold);
	handle_keypress_ztransform(&data->mod, &data->mod.keyhold);
	if (data->window)
	{
		transform_map(&data->map, &data->mod);
		render_img(data);
	}
	return (SUCCESS);
}

static void	handle_keypress_xtransform(t_mod *mod, t_key *keyhold)
{
	if (keyhold->left == true)
	{
		if (mod->scale_mode == true)
			mod->scale.x -= 0.1f;
		else
			mod->rotate.x -= 1.0f;
	}
	if (keyhold->right == true)
	{
		if (mod->scale_mode == true)
			mod->scale.x += 0.1f;
		else
			mod->rotate.x += 1.0f;
	}
	return ;
}

static void	handle_keypress_ytransform(t_mod *mod, t_key *keyhold)
{
	if (keyhold->up == true)
	{
		if (mod->scale_mode == true)
			mod->scale.y += 0.1f;
		else
			mod->rotate.y += 1.0f;
	}
	if (keyhold->down == true)
	{
		if (mod->scale_mode == true)
			mod->scale.y -= 0.1f;
		else
			mod->rotate.y -= 1.0f;
	}
	return ;
}

static void	handle_keypress_ztransform(t_mod *mod, t_key *keyhold)
{
	if (keyhold->comma == true)
	{
		if (mod->scale_mode == true)
			mod->scale.z -= 0.1f;
		else
			mod->rotate.z -= 1.0f;
	}
	if (keyhold->period == true)
	{
		if (mod->scale_mode == true)
			mod->scale.z += 0.1f;
		else
			mod->rotate.z += 1.0f;
	}
	return ;
}
