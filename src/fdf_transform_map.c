/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/09 21:12:45 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	scale_geo(t_vect *pt, t_mod *mod);
static t_vect	translate_cam(t_vect *pt, t_mod *mod);
static t_vect	rotate_geo(t_vect *pt, t_mod *mod);
static void		update_rotatestate(t_mod *mod, t_vect *rotate, float tmp[3][3]);

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
	new_pt.x = pt->x * mod->scale.x * mod->scale_multiplier;
	new_pt.y = pt->y * mod->scale.y * mod->scale_multiplier;
	new_pt.z = pt->z * mod->scale.z * mod->scale_multiplier;
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
	t_vect	tmp;

	tmp = *pt;
	update_coordinates(&tmp, pt, mod->rotate_matrix);
	update_rotatestate(mod, &mod->rotate, mod->rotate_state);
	new_pt = tmp;
	update_coordinates(&new_pt, &tmp, mod->rotate_state);
	if (mod->viewmode == PERSPECTIVE)
	{
		new_pt.x *= mod->z_plane / (mod->z_plane - new_pt.z);
		new_pt.y *= mod->z_plane / (mod->z_plane - new_pt.z);
		new_pt.z *= mod->z_plane / (mod->z_plane - new_pt.z);
	}
	new_pt.y = -(new_pt.y);
	return (new_pt);
}

static void	update_rotatestate(t_mod *mod, t_vect *rotate, float tmp[3][3])
{
	rotate->x *= M_PI / 180.0f;
	rotate->y *= M_PI / 180.0f;
	rotate->z *= M_PI / 180.0f;
	multiply_matrix(mod->rotate_state, (float [3][3])
	{{1, 0, 0},
	{0, cos(rotate->x), -sin(rotate->x)},
	{0, sin(rotate->x), cos(rotate->x)}}, tmp);
	multiply_matrix(mod->rotate_state, (float [3][3])
	{{cos(rotate->y), 0, sin(rotate->y)},
	{0, 1, 0},
	{-sin(rotate->y), 0, cos(rotate->y)}}, tmp);
	multiply_matrix(mod->rotate_state, (float [3][3])
	{{cos(rotate->z), -sin(rotate->z), 0},
	{sin(rotate->z), cos(rotate->z), 0},
	{0, 0, 1}}, tmp);
	return ;
}
