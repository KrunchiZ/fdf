/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:56:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/23 16:33:01 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (EXIT_FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			FRAME_WIDTH, FRAME_HEIGHT, "fdf");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), EXIT_FAILURE);

	/* Event Handler setup when render loop starts */
	mlx_loop_hook(data.mlx_ptr, &fn_handle_idle, &data);
	mlx_expose_hook(data.win_ptr, &fn_handle_idle, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask,
			&fn_handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask,
			&fn_handle_keyrelease, &data);

	/* Main render loop that renders every frame */
	mlx_loop(data.mlx_ptr);

	/* Free mlx_ptr struct before exiting */
	mlx_destroy_display(data.mlx_ptr);
	return (free(data.mlx_ptr), EXIT_SUCCESS);
}
