/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:35:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 17:19:34 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define IS_ROW	true
#define IS_COL	false

static int	draw_bg(t_img *img, t_mod *mod);
static int	draw_map(t_img *img, t_map *map);
static void	connect_points(t_img *img, t_map *map, int i, int is_row);

void	img_px_put(t_img *img, int x, int y, int color)
{
	char	*pxbyte;
	int		i;

	i = img->bpp - 8;
	pxbyte = img->px + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pxbyte++ = (color >> i) & 0xFF;
		else
			*pxbyte++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
	return ;
}

int	render_img(t_data *data)
{
	draw_bg(&data->img, &data->mod);
	draw_map(&data->img, &data->map);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	return (SUCCESS);
}

static int	draw_bg(t_img *img, t_mod *mod)
{
	int	x;
	int	y;
	int	bg_color[4];

	bg_color[0] = PIXEL_GREY;
	bg_color[1] = PIXEL_LTGREY;
	bg_color[2] = PIXEL_WHITE;
	bg_color[3] = PIXEL_BLACK;
	y = 0;
	while (y < FRAME_HEIGHT)
	{
		x = 0;
		while (x < FRAME_WIDTH)
			img_px_put(img, x++, y, bg_color[mod->bg]);
		y++;
	}
	return (SUCCESS);
}

static int	draw_map(t_img *img, t_map *map)
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
