/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:56:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/26 18:57:16 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fn_init_mlx(t_data *data);
static void	fn_setup_mlx_loop(t_data *data);

int	main(void)
{
	t_data	data;

	/* fn_parse_map */
	if (fn_init_mlx(&data) == FN_FAILURE)
		fn_error_exit(EXIT_FAILURE);
	fn_setup_mlx_loop(&data);
	mlx_destroy_image(data.mlx, data.img.img_ptr);
	mlx_destroy_display(data.mlx);
	return (free(data.mlx), EXIT_SUCCESS);
}

static int	fn_init_mlx(t_data *data)
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
		return (free(data->window),
			free(data->mlx), free(data->img.img_ptr), FN_FAILURE);
	return (FN_SUCCESS);
}

static void	fn_setup_mlx_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, &fn_handle_idle, data);
	mlx_expose_hook(data->window, &fn_handle_idle, data);
	mlx_hook(data->window, KeyPress, KeyPressMask,
		&fn_handle_keypress, data);
	mlx_loop(data->mlx);
	return ;
}
