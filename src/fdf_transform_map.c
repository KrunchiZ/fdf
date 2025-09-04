/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 13:13:58 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	scale_geo(t_vect *vertex, t_mod *mod);
static t_vect	rotate_geo(t_vect *vertex, t_mod *mod);
static t_vect	translate_cam(t_vect *vertex, t_mod *mod);

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

static t_vect	rotate_geo(t_vect *vertex, t_mod *mod)
{
	t_vect	pt;

	(void)mod;
	pt = *vertex;
	return (pt);
}

static t_vect	scale_geo(t_vect *vertex, t_mod *mod)
{
	t_vect	pt;

	pt = *vertex;
	pt.x = vertex->x * mod->scale.x * mod->scale_multiplier;
	pt.y = vertex->y * mod->scale.y * mod->scale_multiplier;
	pt.z = vertex->z * mod->scale.z * mod->scale_multiplier;
	return (pt);
}

static t_vect	translate_cam(t_vect *vertex, t_mod *mod)
{
	t_vect	pt;

	pt = *vertex;
	pt.x = vertex->x + mod->x_offset + mod->translate_cam2d.x;
	pt.y = vertex->y + mod->y_offset + mod->translate_cam2d.y;
	return (pt);
}
