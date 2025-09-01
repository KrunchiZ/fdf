/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:36:29 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/01 15:04:43 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define IS_ROW	true;
#define IS_COL	false;

int	fn_draw_map(t_img *img, t_map *map)
{
	int		i;
	t_vect	pt;

	fn_draw_width(img, map);
	i = 0;
	while (i < map->vertex_count)
	{
		pt = map->render_pt[i++];
		if (pt.x >= 0 && pt.x <= FRAME_WIDTH
			&& pt.y >= 0 && pt.y <= FRAME_HEIGHT)
			fn_img_px_put(img, pt.x, pt.y, pt.color);
	}
	return (FN_SUCCESS);
}

static void	fn_draw_width(t_img *img, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->vertex_count)
	{
		fn_connect_(img, map, i, IS_ROW);
		i += map->width;
	}
}

static void	fn_draw_depth(t_img *img, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		fn_connect_(img, map, i, IS_COL);
		i++;;
	}
}

static void	fn_connect_points(t_img *img, t_map *map, int i, int is_row)
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
			fn_draw_line(img, map->render_pt[i + j], map->render_pt[i + j + 1]);
			j++;
		}
		else
		{
			fn_draw_line(img, map->render_pt[i + j],
				map->render_pt[i + j + map->width]);
			j += map->width;
		}
	}
	return ;
}
