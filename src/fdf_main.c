/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:56:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/05 01:43:15 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_modifier(t_mod *mod, t_map *map);
static void	init_rotate_matrix(t_mtrx *matrix);
static int	init_mlx(t_data *data);
static void	setup_mlx_loop(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_exit("Wrong arguments\n<format = ./fdf [FILE]>");
	data = (t_data){0};
	parse_map(&data.map, argv[1]);
	set_modifier(&data.mod, &data.map);
	if (init_mlx(&data) == FAILURE)
		error_exit("mlx/window/image creation failure");
	setup_mlx_loop(&data);
	mlx_destroy_image(data.mlx, data.img.img_ptr);
	mlx_destroy_display(data.mlx);
	return (free(data.mlx), delete_map(&data.map), EXIT_SUCCESS);
}

static void	set_modifier(t_mod *mod, t_map *map)
{
	int	w_multiplier;
	int	d_multiplier;
	int	h_multiplier;

	w_multiplier = FRAME_HEIGHT / 2 / map->width;
	d_multiplier = FRAME_HEIGHT / 2 / map->depth;
	h_multiplier = FRAME_HEIGHT / 2 / map->height;
	mod->scale_multiplier = h_multiplier;
	if (w_multiplier < d_multiplier && w_multiplier < h_multiplier)
		mod->scale_multiplier = w_multiplier;
	else if (d_multiplier < h_multiplier)
		mod->scale_multiplier = d_multiplier;
	if (mod->scale_multiplier == 0)
		mod->scale_multiplier = 1;
	mod->x_offset = FRAME_WIDTH / 2 - 1;
	mod->y_offset = FRAME_HEIGHT / 2 - 1;
	mod->viewangle.x = 35.264f;
	mod->viewangle.y = 45.0f;
	mod->scale = (t_vect){.x = 1.0f, .y = 1.0f, .z = 1.0f};
	init_rotate_matrix(&mod->rotate_matrix);
	ft_putendl_fd("Transform mode: Rotate", STDOUT_FILENO);
	return ;
}

static void	init_rotate_matrix(t_mtrx *matrix)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		matrix->x[i][i] = 1.0f;
		matrix->y[i][i] = 1.0f;
		matrix->z[i][i] = 1.0f;
		matrix->zy[i][i] = 1.0f;
		matrix->zyx[i][i] = 1.0f;
		i++;
	}
	return ;
}

static int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (delete_map(&data->map), FAILURE);
	data->window = mlx_new_window(data->mlx, FRAME_WIDTH, FRAME_HEIGHT, "fdf");
	if (!data->window)
		return (delete_map(&data->map),
			mlx_destroy_display(data->mlx), free(data->mlx), FAILURE);
	data->img.img_ptr = mlx_new_image(data->mlx, FRAME_WIDTH, FRAME_HEIGHT);
	if (!data->img.img_ptr)
	{
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		return (free(data->mlx), delete_map(&data->map), FAILURE);
	}
	data->img.px = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.px)
	{
		mlx_destroy_image(data->mlx, data->img.img_ptr);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		(void)(free(data->mlx), delete_map(&data->map));
		error_exit("mlx_get_data_addr failure");
	}
	return (SUCCESS);
}

static void	setup_mlx_loop(t_data *data)
{
	mlx_loop_hook(data->mlx, &handle_idle, data);
	mlx_expose_hook(data->window, &handle_idle, data);
	mlx_hook(data->window, KeyPress, KeyPressMask,
		&handle_keypress, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask,
		&handle_keyrelease, data);
	mlx_hook(data->window, ButtonPress, ButtonPressMask,
		&handle_mousepress, data);
	mlx_hook(data->window, ButtonRelease, ButtonReleaseMask,
		&handle_mouserelease, data);
	mlx_hook(data->window, MotionNotify, Button1MotionMask,
		&handle_mouse1drag, data);
	mlx_loop(data->mlx);
	return ;
}
