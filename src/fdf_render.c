/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:35:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/30 16:50:53 by kchiang          ###   ########.fr       */
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

static int	fn_render_map(t_img *img, t_map *map, t_mod *mod)
{
	int		i;
	t_vect	pt;

	i = 0;
	while (i < map->vertex_count)
	{
		pt = map->vertices[i++];
		/* fn_apply_modifier; */
		fn_img_px_put(img, pt.x, pt.z, pt.color);
	}
	return (FN_SUCCESS);
}

int	fn_render_img(t_data *data)
{
	fn_render_map(&data->img, &data->map, &data->mod);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	return (FN_SUCCESS);
}
