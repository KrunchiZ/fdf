/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:46:20 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/26 16:11:43 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fn_init_mlx(t_data *data)
{
	*data = (t_data){0};
	data->mlx = mlx_init();
	if (!data->mlx)
		return (FN_FAILURE);
	data->window = mlx_new_window(data->mlx, FRAME_WIDTH, FRAME_HEIGHT, "fdf");
	if (!data->window)
		return (free(data->mlx), FN_FAILURE);
	data->img.img_ptr = mlx_new_image(data->mlx, FRAME_WIDTH, FRAME_HEIGHT);
	if (!data->img.img_ptr)
		return (free(data->window), free(data->mlx), FN_FAILURE);
	data->img.px = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.px)
		return (free(data->window), free(data->mlx), free(data->img.img_ptr),
			FN_FAILURE);
	return (FN_SUCCESS);
}
