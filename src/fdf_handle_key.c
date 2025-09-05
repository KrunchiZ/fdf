/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:10:55 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/05 17:58:32 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define FIRST_BG	0
#define LAST_BG		3
#define FIRST_MODE	0
#define LAST_MODE	3

static void	handle_viewmode_keys(int keysym, t_data *data);
static void	handle_transform_keys(int keysym, t_data *data);

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_Up)
		data->mod.keyhold &= ~KEY_UP;
	if (keysym == XK_Down)
		data->mod.keyhold &= ~KEY_DOWN;
	if (keysym == XK_Left)
		data->mod.keyhold &= ~KEY_LEFT;
	if (keysym == XK_Right)
		data->mod.keyhold &= ~KEY_RIGHT;
	if (keysym == XK_comma)
		data->mod.keyhold &= ~KEY_COMMA;
	if (keysym == XK_period)
		data->mod.keyhold &= ~KEY_PERIOD;
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
		data->mod.scale = (t_vect){.x = 1.0f, .y = 1.0f, .z = 1.0f};
		data->mod.rotate = (t_vect){0};
		data->mod.translate_cam2d = (t_vect){0};
	}
	handle_viewmode_keys(keysym, data);
	handle_transform_keys(keysym, data);
	return (SUCCESS);
}

static void	handle_viewmode_keys(int keysym, t_data *data)
{
	if (keysym == XK_v)
	{
		data->mod.viewmode++;
		if (data->mod.viewmode > LAST_MODE)
			data->mod.viewmode = FIRST_MODE;
		if (data->mod.viewmode == ISOMETRIC)
			ft_putendl_fd("Viewmode: Isometric", STDOUT_FILENO);
		if (data->mod.viewmode == FRONT)
			ft_putendl_fd("Viewmode: Front", STDOUT_FILENO);
		if (data->mod.viewmode == SIDE)
			ft_putendl_fd("Viewmode: Side", STDOUT_FILENO);
		if (data->mod.viewmode == TOP)
			ft_putendl_fd("Viewmode: Top", STDOUT_FILENO);
	}
	return ;
}

static void	handle_transform_keys(int keysym, t_data *data)
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
		data->mod.keyhold |= KEY_UP;
	if (keysym == XK_Down)
		data->mod.keyhold |= KEY_DOWN;
	if (keysym == XK_Left)
		data->mod.keyhold |= KEY_LEFT;
	if (keysym == XK_Right)
		data->mod.keyhold |= KEY_RIGHT;
	if (keysym == XK_comma)
		data->mod.keyhold |= KEY_COMMA;
	if (keysym == XK_period)
		data->mod.keyhold |= KEY_PERIOD;
	return ;
}
