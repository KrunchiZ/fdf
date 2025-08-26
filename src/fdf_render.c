/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:35:59 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/26 13:30:55 by kchiang          ###   ########.fr       */
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

static int	fn_render_rect(t_img *img, int color)
{
	int	x;
	int	y;

	y = 200;
	while (y < 500)
	{
		x = 300;
		while (x < 900)
			fn_img_px_put(img, x++, y, color);
		y++;
	}
	return (FN_SUCCESS);
}

static void	fn_render_bg(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
			fn_img_px_put(img, x++, y, color);
		y++;
	}
	return ;
}

int	fn_render_img(t_data *data)
{
	fn_render_bg(&data->img, PIXEL_WHITE);
	fn_render_rect(&data->img, PIXEL_RED);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img_ptr, 0, 0);
	return (FN_SUCCESS);
}
