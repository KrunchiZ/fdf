/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_modifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:32:57 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/09 21:17:00 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_viewangle(t_mod *mod);
static void	init_rotate_matrix(t_mod *mod);

void	set_modifier(t_mod *mod, t_map *map)
{
	int	w_multiplier;
	int	d_multiplier;
	int	h_multiplier;

	w_multiplier = FRAME_WIDTH / 2 / map->width;
	d_multiplier = FRAME_WIDTH / 2 / map->depth;
	h_multiplier = FRAME_HEIGHT / 2 / map->height;
	mod->scale_multiplier = h_multiplier;
	if (w_multiplier < d_multiplier && w_multiplier < h_multiplier)
		mod->scale_multiplier = w_multiplier;
	else if (d_multiplier < h_multiplier)
		mod->scale_multiplier = d_multiplier;
	mod->x_offset = FRAME_WIDTH / 2 - 1;
	mod->y_offset = FRAME_HEIGHT / 2 - 1;
	mod->scale = (t_vect){.x = 1.0f, .y = 1.0f, .z = 1.0f};
	mod->z_plane = map->depth * mod->scale_multiplier + 250.0f;
	mod->viewmode = ISOMETRIC;
	set_viewangle(mod);
	init_rotate_matrix(mod);
	return ;
}

static void	set_viewangle(t_mod *mod)
{
	mod->viewangle[ISOMETRIC].y = 45.0f;
	mod->viewangle[ISOMETRIC].x = 35.264f;
	mod->viewangle[PERSPECTIVE].y = 45.0f;
	mod->viewangle[PERSPECTIVE].x = 35.264f;
	mod->viewangle[FRONT].y = 45.0f;
	mod->viewangle[TOP].y = 45.0f;
	mod->viewangle[TOP].x = 90.0f;
	return ;
}

static void	init_rotate_matrix(t_mod *mod)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		mod->rotate_matrix[i][i] = 1.0f;
		mod->rotate_state[i][i] = 1.0f;
		i++;
	}
	return ;
}
