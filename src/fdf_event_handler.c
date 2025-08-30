/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_event_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:10:55 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/30 17:30:03 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fn_handle_idle(t_data *data)
{
	if (data->window)
	{
		fn_set_render_point(&data->map, &data->mod);
		fn_render_img(data);
	}
	return (FN_SUCCESS);
}

int	fn_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->window);
		data->window = NULL;
	}
	return (FN_SUCCESS);
}
