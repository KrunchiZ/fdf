/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_edges.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:00:24 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/06 23:30:22 by kchiang          ###   ########.fr       */
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
