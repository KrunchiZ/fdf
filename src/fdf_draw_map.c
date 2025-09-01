/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:36:29 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/01 14:48:57 by kchiang          ###   ########.fr       */
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
	int		i;

	i = 0;
	while (i < map->vertex_count)
	{
		fn_connect_(img, map, i, IS_ROW);
		i += map->width;
	}
}

static void	fn_connect_points(t_img *img, t_map *map, int i, int is_row)
{
	int	j;
	int	count;

	if (is_row)
		count = map->width - 1;
	else
		count = map->depth - 1;
	j = 0;
	while (j < count)
	{
		fn_draw_line(img, map->render_pt[i + j], map->render_pt[i + j + 1]);
		if (is_row)
			j++;
		else
			j += map->width;
	}
}

void	fn_draw_line(t_img *img, t_vect pt0, t_vect pt1)
{
	t_line	line;

	line = (t_line){x_step = 1, y_step = 1};
	if (pt0.x > pt1.x)
		line.x_step = -1;
	if (pt0.y > pt1.y)
		line.y_step = -1;
	line.dx = ft_abs(pt1.x - pt0.x);
	line.dy = ft_abs(pt1.y - pt0.y);
	if (line.dx >= line.dy)
		fn_draw_along_x(img, pt0, pt1, line);
	else
		fn_draw_along_y(img, pt0, pt1, line);
}
