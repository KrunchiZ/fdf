/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:56:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/26 16:10:56 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(void)
{
	t_data	data;

	if (fn_init_mlx(&data) == FN_FAILURE)
		fn_error_exit(EXIT_FAILURE);
	mlx_loop_hook(data.mlx, &fn_handle_idle, &data);
	mlx_expose_hook(data.window, &fn_handle_idle, &data);
	mlx_hook(data.window, KeyPress, KeyPressMask,
		&fn_handle_keypress, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.img.img_ptr);
	mlx_destroy_display(data.mlx);
	return (free(data.mlx), EXIT_SUCCESS);
}
