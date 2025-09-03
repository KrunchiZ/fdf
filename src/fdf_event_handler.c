/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:10:55 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 15:38:44 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//static void	set_topview_mod(t_mod *mod, t_map *map);

int	handle_idle(t_data *data)
{
	if (data->window)
	{
		setup3d(&data->map, &data->mod);
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
//	if (keysym == XK_t)
//		set_topview_mod(&data->mod, &data->map);
	return (SUCCESS);
}
/*
static void	set_topview_mod(t_mod *mod, t_map *map)
{
	mod->x_offset = FRAME_WIDTH / 2 - (map->width - 1) * mod->multiplier / 2;
	mod->y_offset = FRAME_HEIGHT / 2 - (map->width - 1) * mod->multiplier / 2;
	return ;
}
*/
