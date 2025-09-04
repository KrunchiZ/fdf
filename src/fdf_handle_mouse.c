/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handle_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:49:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 16:34:11 by kchiang          ###   ########.fr       */
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
