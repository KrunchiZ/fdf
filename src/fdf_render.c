/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:35:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/30 17:48:30 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fn_img_px_put(t_img *img, int x, int y, int color)
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

static int	fn_render_map(t_img *img, t_map *map)
{
	int		i;
	t_vect	pt;

	i = 0;
	while (i < map->vertex_count)
	{
		pt = map->vertices[i++];
		fn_img_px_put(img, pt.x * 20, pt.z * 20, pt.color);
	}
	return (FN_SUCCESS);
}

static int	fn_render_bg(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < FRAME_HEIGHT)
	{
		x = 0;
		while (x < FRAME_WIDTH)
			fn_img_px_put(img, x++, y, PIXEL_GREY);
		y++;
	}
	return (FN_SUCCESS);
}

int	fn_render_img(t_data *data)
{
	fn_render_bg(&data->img);
	fn_render_map(&data->img, &data->map);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	return (FN_SUCCESS);
}
