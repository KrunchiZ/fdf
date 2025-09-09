/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_transform_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:59:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/09 18:49:46 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vect	scale_geo(t_vect *pt, t_mod *mod);
static t_vect	translate_cam(t_vect *pt, t_mod *mod);
static t_vect	rotate_geo(t_vect *pt, t_mod *mod);
static void		handle_rotatekey(t_mod *mod, float rotate_step,
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

	new_pt = *pt;
	handle_rotatekey(mod, mod->rotate_step, &new_pt, pt);
	if (mod->viewmode == PERSPECTIVE)
	{
		new_pt.x *= mod->z_plane / (mod->z_plane - new_pt.z);
		new_pt.y *= mod->z_plane / (mod->z_plane - new_pt.z);
		new_pt.z *= mod->z_plane / (mod->z_plane - new_pt.z);
	}
	return (new_pt);
}

static void	handle_rotatekey(t_mod *mod, float rotate_step,
					t_vect *new_pt, t_vect *pt)
{
	if (mod->keyhold & (KEY_UP | KEY_DOWN))
		update_coordinates(mod, new_pt, pt, (float [3][3])
		{{1, 0, 0},
		{0, cos(rotate_step), -sin(rotate_step)},
		{0, sin(rotate_step), cos(rotate_step)}});
	if (mod->keyhold & (KEY_LEFT | KEY_RIGHT))
		update_coordinates(mod, new_pt, pt, (float [3][3])
		{{cos(rotate_step), 0, sin(rotate_step)},
		{0, 1, 0},
		{-sin(rotate_step), 0, cos(rotate_step)}});
	if (mod->keyhold & (KEY_COMMA | KEY_PERIOD))
		update_coordinates(mod, new_pt, pt, (float [3][3])
		{{cos(rotate_step), -sin(rotate_step), 0},
		{sin(rotate_step), cos(rotate_step), 0},
		{0, 0, 1}});
	return ;
}
