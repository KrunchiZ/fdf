/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:35:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/01 14:49:48 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fn_draw_bg(t_img *img);

void	fn_img_px_put(t_img *img, int x, int y, int color)
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

int	fn_render_img(t_data *data)
{
	fn_draw_bg(&data->img);
	fn_draw_map(&data->img, &data->map);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	return (FN_SUCCESS);
}

static int	fn_draw_bg(t_img *img)
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
