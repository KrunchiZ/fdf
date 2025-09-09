/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/09 17:35:04 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	scale_geo(t_vect *pt, t_mod *mod);
static t_vect	translate_cam(t_vect *pt, t_mod *mod);
static t_vect	rotate_geo(t_vect *pt, t_mod *mod);

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

static t_vect	scale_geo(t_vect *pt, t_mod *mod)
{
	t_vect	new_pt;

	new_pt = *pt;
	new_pt.x = pt->x * mod->scale.x;
	new_pt.y = pt->y * mod->scale.y;
	new_pt.z = pt->z * mod->scale.z;
	return (new_pt);
}

static t_vect	translate_cam(t_vect *pt, t_mod *mod)
{
	t_vect	new_pt;

	new_pt = *pt;
	new_pt.x = pt->x + mod->x_offset + mod->translate_cam2d.x;
	new_pt.y = pt->y + mod->y_offset + mod->translate_cam2d.y;
	return (new_pt);
}

static t_vect	rotate_geo(t_vect *pt, t_mod *mod)
{
	t_vect	new_pt;

	new_pt = *vertex;
	update_coordinates(mod, mod->rotate_matrix.abc, &new_pt, vertex);
	if (mod->viewmode == PERSPECTIVE)
	{
		new_pt.x *= mod->z_plane / (mod->z_plane - new_pt.z);
		new_pt.y *= mod->z_plane / (mod->z_plane - new_pt.z);
		new_pt.z *= mod->z_plane / (mod->z_plane - new_pt.z);
	}
	return (new_pt);
}
