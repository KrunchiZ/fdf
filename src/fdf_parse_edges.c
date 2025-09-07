/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_edges.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:00:24 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/07 20:04:54 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	qsort_edges(t_edge *edges, int start, int end);
static int	is_less_equal(t_edge *e0, t_edge *e1);
static void	swap_edges(t_edge *edge_i, t_edge *edge_j);

void	parse_edges(t_map *map, int viewmode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->vertex_count - 1)
	{
		map->edges[j].start = map->render_pt[i];
		map->edges[j++].end = map->render_pt[i++ + 1];
		if ((i + 1) % map->width == 0)
			i++;
	}
	i = 0;
	while (i < map->vertex_count - map->width)
	{
		map->edges[j].start = map->render_pt[i];
		map->edges[j++].end = map->render_pt[i++ + map->width];
	}
	if (viewmode != TOP)
		qsort_edges(map->edges, 0, map->edge_count - 1);
	return ;
}

static void	qsort_edges(t_edge *edges, int start, int end)
{
	int	pivot_index;
	int	j;

	if (start < end)
	{
		pivot_index = start;
		j = start;
		while (j < end)
		{
			if (is_less_equal(&edges[j], &edges[end]))
				swap_edges(&edges[pivot_index++], &edges[j]);
			j++;
		}
		swap_edges(&edges[pivot_index], &edges[end]);
		qsort_edges(edges, start, pivot_index - 1);
		qsort_edges(edges, pivot_index + 1, end);
	}
	return ;
}

static int	is_less_equal(t_edge *e0, t_edge *e1)
{
	float	e0_z;
	float	e1_z;

	e0_z = (e0->start.z + e0->end.z) / 2.0f;
	e1_z = (e1->start.z + e1->end.z) / 2.0f;
	if (e0_z <= e1_z)
		return (true);
	return (false);
}

static void	swap_edges(t_edge *edge_i, t_edge *edge_j)
{
	t_edge	tmp_j;

	tmp_j = *edge_j;
	*edge_j = *edge_i;
	*edge_i = tmp_j;
	return ;
}
