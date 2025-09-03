/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 16:34:56 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	apply_modifier(t_vect *vertices, t_mod *mod);

void	setup3d(t_map *map, t_mod *mod)
{
	int	i;

	i = 0;
	while (i < map->vertex_count)
	{
		map->render_pt[i] = apply_modifier(&map->vertices[i], mod);
		i++;
	}
}

static t_vect	apply_modifier(t_vect *vertices, t_mod *mod)
{
	t_vect	pt;

	pt = *vertices;
	pt.z = 0.0f;
	pt.x = (vertices->x * mod->multiplier) + mod->x_offset;
	pt.y = (vertices->z * mod->multiplier) + mod->y_offset;
	/* To be updated with y value */
	return (pt);
}
