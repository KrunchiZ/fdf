/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:10:55 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 14:47:32 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define FIRST_BG	0
#define LAST_BG		3

static void	handle_transfrom_keys(int keysym, t_data *data);

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_Up)
		data->mod.keyhold.up = false;
	if (keysym == XK_Down)
		data->mod.keyhold.down = false;
	if (keysym == XK_Left)
		data->mod.keyhold.left = false;
	if (keysym == XK_Right)
		data->mod.keyhold.right = false;
	if (keysym == XK_Comma)
		data->mod.keyhold.comma = false;
	if (keysym == XK_Period)
		data->mod.keyhold.period = false;
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
	if (keysym == XK_Return)
	{
		data->mod.scale = (t_vect){0};
		data->mod.rotate = (t_vect){0};
		data->mod.cam2d = (t_vect){0};
	}
	handle_transform_keys(keysym, data);
	return (SUCCESS);
}

static void	handle_transfrom_keys(int keysym, t_data *data)
{
	if (keysym == XK_e)
	{
		data->mod.scale_mode = false;
		ft_putendl_fd("Transform mode: Rotate", STDOUT_FILENO);
	}
	if (keysym == XK_r)
	{
		data->mod.scale_mode = true;
		ft_putendl_fd("Transform mode: Scale", STDOUT_FILENO);
	}
	if (keysym == XK_Up)
		data->mod.keyhold.up = true;
	if (keysym == XK_Down)
		data->mod.keyhold.down = true;
	if (keysym == XK_Left)
		data->mod.keyhold.left = true;
	if (keysym == XK_Right)
		data->mod.keyhold.right = true;
	if (keysym == XK_Comma)
		data->mod.keyhold.comma = true;
	if (keysym == XK_Period)
		data->mod.keyhold.period = true;
	return ;
}
