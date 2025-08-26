/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:56:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/26 13:35:53 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_data	data;

	data = (t_data){0};
	data.mlx = mlx_init();
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.window = mlx_new_window(data.mlx, FRAME_WIDTH, FRAME_HEIGHT, "fdf");
	if (!data.window)
		return (free(data.mlx), EXIT_FAILURE);

	/* Create image for rendering */
	data.img.img_ptr = mlx_new_image(data.mlx, FRAME_WIDTH, FRAME_HEIGHT);
	if (!data.img.img_ptr)
		return (free(data.window), free(data.mlx), EXIT_FAILURE);
	data.img.px = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	if (!data.img.px)
		return (free(data.window), free(data.mlx), free(data.img.img_ptr),
			EXIT_FAILURE);

	/* Event Handler setup when render loop starts */
	mlx_loop_hook(data.mlx, &fn_handle_idle, &data);
	mlx_expose_hook(data.window, &fn_handle_idle, &data);
	mlx_hook(data.window, KeyPress, KeyPressMask,
		&fn_handle_keypress, &data);

	/* Main render loop that renders every frame */
	mlx_loop(data.mlx);

	/* Free mlx struct before exiting */
	mlx_destroy_image(data.mlx, data.img.img_ptr);
	mlx_destroy_display(data.mlx);
	return (free(data.mlx), EXIT_SUCCESS);
}
