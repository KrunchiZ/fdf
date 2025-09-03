/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 19:11:48 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	scale_geo(t_vect *vertex, t_mod *mod);
static t_vect	translate_geo(t_vect *vertex, t_mod *mod);
static t_vect	center_frame(t_vect *vertex, t_mod *mod);

void	setup3d(t_map *map, t_mod *mod)
{
	int	i;

	i = 0;
	while (i < map->vertex_count)
	{
		map->render_pt[i] = scale_geo(&map->vertices[i], mod);
		map->render_pt[i] = rotate_geo(&map->render_pt[i], mod);
		map->render_pt[i] = translate_geo(&map->render_pt[i], mod);
		map->render_pt[i] = center_frame(&map->render_pt[i], mod);
		i++;
	}
}

static t_vect	scale_geo(t_vect *vertex, t_mod *mod)
{
	t_vect	pt;

	pt = *vertex;
	pt.x = vertex->x * mod->scale.x * mod->scale_mult;
	pt.y = vertex->y * mod->scale.y * mod->scale_mult;
	pt.z = vertex->z * mod->scale.z * mod->scale_mult;
	return (pt);
}

static t_vect	translate_geo(t_vect *vertex, t_mod *mod)
{
	t_vect	pt;

	pt = *vertex;
	pt.x = vertex->x + mod->translate.x;
	pt.y = vertex->y + mod->translate.y;
	pt.z = vertex->z + mod->translate.z;
	return (pt);
}

static t_vect	center_frame(t_vect *vertex, t_mod *mod)
{
	t_vect	pt;

	pt = *vertex;
	pt.x = vertex->x + mod->x_offset;
	pt.y = vertex->y + mod->y_offset;
	return (pt);
}
