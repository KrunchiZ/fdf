/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/06 19:33:44 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	scale_geo(t_vect *vertex, t_mod *mod);
static t_vect	translate_cam(t_vect *vertex, t_mod *mod);
static t_vect	rotate_geo(t_vect *vertex, t_mod *mod);
static void		update_coordinates(t_mod *mod, float abc[3][3],
					t_vect *new_pt, t_vect *pt);

void	transform_map(t_map *map, t_mod *mod)
{
	int	i;

	i = 0;
	while (i < map->vertex_count)
	{
		map->render_pt[i] = scale_geo(&map->vertices[i], mod);
		map->render_pt[i] = rotate_geo(&map->render_pt[i], mod);
		map->render_pt[i] = translate_cam(&map->render_pt[i], mod);
		i++;
	}
}

static t_vect	scale_geo(t_vect *vertex, t_mod *mod)
{
	t_vect	new_pt;

	new_pt = *vertex;
	new_pt.x = vertex->x * mod->scale.x * mod->scale_multiplier;
	new_pt.y = vertex->y * mod->scale.y * mod->scale_multiplier;
	new_pt.z = vertex->z * mod->scale.z * mod->scale_multiplier;
	return (new_pt);
}

static t_vect	translate_cam(t_vect *vertex, t_mod *mod)
{
	t_vect	new_pt;

	new_pt = *vertex;
	new_pt.x = vertex->x + mod->x_offset + mod->translate_cam2d.x;
	new_pt.y = vertex->y + mod->y_offset + mod->translate_cam2d.y;
	return (new_pt);
}

static t_vect	rotate_geo(t_vect *vertex, t_mod *mod)
{
	t_vect	new_pt;

	new_pt = *vertex;
	calc_rotate_matrix(mod);
	update_coordinates(mod, mod->rotate_matrix.abc, &new_pt, vertex);
	return (new_pt);
}

static void	update_coordinates(t_mod *mod, float abc[3][3],
					t_vect *new_pt, t_vect *pt)
{
	new_pt->x = abc[0][0] * pt->x + abc[0][1] * pt->y + abc[0][2] * pt->z;
	new_pt->y = abc[1][0] * pt->x + abc[1][1] * pt->y + abc[1][2] * pt->z;
	new_pt->z = abc[2][0] * pt->x + abc[2][1] * pt->y + abc[2][2] * pt->z;
	if (mod->viewmode != ISOMETRIC)
		new_pt->y = -(new_pt->y);
	return ;
}
