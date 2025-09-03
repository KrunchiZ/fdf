/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:36:29 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 16:40:03 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define IS_ROW	true
#define IS_COL	false

static void	connect_points(t_img *img, t_map *map, int i, int is_row);

int	draw_map(t_img *img, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->vertex_count)
	{
		connect_points(img, map, i, IS_ROW);
		i += map->width;
	}
	i = 0;
	while (i < map->width)
		connect_points(img, map, i++, IS_COL);
	return (SUCCESS);
}

static void	connect_points(t_img *img, t_map *map, int i, int is_row)
{
	int	j;
	int	count;

	if (is_row)
		count = map->width - 1;
	else
		count = map->vertex_count - map->width;
	j = 0;
	while (j < count)
	{
		if (is_row)
		{
			draw_line(img, map->render_pt[i + j], map->render_pt[i + j + 1]);
			j++;
		}
		else
		{
			draw_line(img, map->render_pt[i + j],
				map->render_pt[i + j + map->width]);
			j += map->width;
		}
	}
	return ;
}
