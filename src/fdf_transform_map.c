/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/10 18:18:10 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	scale_geo(t_vect *pt, t_mod *mod);
static t_vect	transform_cam(t_vect *pt, t_mod *mod);
static t_vect	rotate_geo(t_vect *pt, t_mod *mod);
static void		update_coordinates(t_vect *new_pt, t_vect *pt,
					float mtrx[3][3]);

void	transform_map(t_map *map, t_mod *mod)
{
	int	i;

	i = 0;
	while (i < map->vertex_count)
	{
		map->render_pt[i] = scale_geo(&map->vertices[i], mod);
		map->render_pt[i] = rotate_geo(&map->render_pt[i], mod);
		map->render_pt[i] = transform_cam(&map->render_pt[i], mod);
		i++;
	}
}

static t_vect	scale_geo(t_vect *pt, t_mod *mod)
{
	t_vect	new_pt;

	new_pt = *pt;
	new_pt.x = pt->x * mod->scale.x * mod->scale_multiplier;
	new_pt.y = pt->y * mod->scale.y * mod->scale_multiplier;
	new_pt.z = pt->z * mod->scale.z * mod->scale_multiplier;
	return (new_pt);
}

static t_vect	transform_cam(t_vect *pt, t_mod *mod)
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
	t_vect	tmp;
	float	divisor;

	tmp = *pt;
	update_coordinates(&tmp, pt, mod->rotate_matrix);
	new_pt = tmp;
	calc_rotate_matrix(mod, ROTATE_MOD);
	update_coordinates(&new_pt, &tmp, mod->rotate_state);
	if (mod->viewmode == PERSPECTIVE)
	{
		divisor = mod->z_plane - new_pt.z;
		if (divisor <= 0.0f)
			divisor = 1.0f;
		new_pt.x *= mod->z_plane / divisor;
		new_pt.y *= mod->z_plane / divisor;
	}
	new_pt.y = -(new_pt.y);
	return (new_pt);
}

static void	update_coordinates(t_vect *new_pt, t_vect *pt, float mtrx[3][3])
{
	new_pt->x = mtrx[0][0] * pt->x + mtrx[0][1] * pt->y + mtrx[0][2] * pt->z;
	new_pt->y = mtrx[1][0] * pt->x + mtrx[1][1] * pt->y + mtrx[1][2] * pt->z;
	new_pt->z = mtrx[2][0] * pt->x + mtrx[2][1] * pt->y + mtrx[2][2] * pt->z;
	return ;
}
