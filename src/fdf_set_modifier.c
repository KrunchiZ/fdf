/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_modifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:32:57 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/06 05:02:48 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_rotate_matrix(t_mtrx *matrix);

void	set_modifier(t_mod *mod, t_map *map)
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
	mod->scale = (t_vect){.x = 1.0f, .y = 1.0f, .z = 1.0f};
	mod->viewangle.x = 35.264f;
	mod->viewangle.y = 44.775f;
	mod->viewmode = ISOMETRIC;
	init_rotate_matrix(&mod->rotate_matrix);
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
		matrix->ab[i][i] = 1.0f;
		matrix->abc[i][i] = 1.0f;
		i++;
	}
	return ;
}
