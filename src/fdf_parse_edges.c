/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_edges.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:00:24 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/07 00:27:05 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_edges(t_mod *mod)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mod->vertex_count - 1)
	{
		mod->edge[j].start = mod->render_pt[i];
		mod->edge[j++].end = mod->render_pt[i++ + 1];
		if (i + 1 == mod->width)
			i++;
	}
	i = 0;
	while (i < mod->vertex_count - mod->width)
	{
		mod->edge[j].start = mod->render_pt[i];
		mod->edge[j++].end = mod->render_pt[i++ + mod->width];
	}
	sort_edges(mod->edges, mod->edge_count);
	return ;
}

static void	sort_edges(t_edge *edges, int edge_count)
{
}

static int	zcompare(t_edge *e0, t_edge *e1)
{
	float	e0_z;
	float	e1_z;

	e0_z = (e0->start.z + e0->end.z) / 2.0f;
	e1_z = (e1->start.z + e1->end.z) / 2.0f;
	if (e0_z < e1_z)
		return (-1);
	if (e1_z < e0_z)
		return (1);
	return (0);
}
