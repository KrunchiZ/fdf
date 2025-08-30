/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:56:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/30 17:19:27 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fn_init_mlx(t_data *data);
static void	fn_setup_mlx_loop(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		fn_error_exit("Wrong arguments\n<format = ./fdf [FILE]>");
	data = (t_data){0};
	fn_parse_map(&data.map, argv[1]);
	fn_set_modifier(&data.mod, &data.map);
	if (fn_init_mlx(&data) == FN_FAILURE)
		fn_error_exit("mlx/window/image creation failure");
	fn_setup_mlx_loop(&data);
	mlx_destroy_image(data.mlx, data.img.img_ptr);
	mlx_destroy_display(data.mlx);
	return (free(data.mlx), fn_delete_map(&data.map), EXIT_SUCCESS);
}

static void	fn_set_modifier(t_map *map, t_mod *mod)
{
	int	w_quotient;
	int	d_quotient;
	int	h_quotient;

	map->scale = 1;
	w_quotient = FRAME_WIDTH / 2 / map->width;
	d_quotient = FRAME_HEIGHT / 2 / map->depth;
	h_quotient = FRAME_HEIGHT / 3 / map->height;
	if (w_quotient < d_quotient && w_quotient < h_quotient)
		map->offset = w_quotient;
	else if (d_quotient < h_quotient)
		map->offset = d_quotient;
	else
		map->offset = h_quotient;
	return ;
}

static int	fn_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (fn_delete_map(&data->map), FN_FAILURE);
	data->window = mlx_new_window(data->mlx, FRAME_WIDTH, FRAME_HEIGHT, "fdf");
	if (!data->window)
		return (fn_delete_map(&data->map),
			mlx_destroy_display(data->mlx), free(data->mlx), FN_FAILURE);
	data->img.img_ptr = mlx_new_image(data->mlx, FRAME_WIDTH, FRAME_HEIGHT);
	if (!data->img.img_ptr)
	{
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		return (free(data->mlx), fn_delete_map(&data->map), FN_FAILURE);
	}
	data->img.px = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.px)
	{
		mlx_destroy_image(data->mlx, data->img.img_ptr);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		(void)(free(data->mlx), fn_delete_map(&data->map));
		fn_error_exit("mlx_get_data_addr failure");
	}
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
