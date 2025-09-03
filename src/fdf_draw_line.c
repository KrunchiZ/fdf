/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:52:45 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 16:15:22 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_rgbstep(t_line *line, t_vect *p0, t_vect *p1, int delta);
static void	draw(t_img *img, t_line *line, int delta, t_vect *p0);
static void	calc_color(t_line *line);

void	draw_line(t_img *img, t_vect p0, t_vect p1)
{
	t_line	line;
	t_vect	delta;

	line = (t_line){.pt = p0, .xstep = 1, .ystep = 1};
	if (p0.x > p1.x)
		line.xstep = -1;
	if (p0.y > p1.y)
		line.ystep = -1;
	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	if (ft_abs(delta.x) >= ft_abs(delta.y))
	{
		line.ystep = (delta.y / delta.x) * line.xstep;
		get_rgbstep(&line, &p0, &p1, delta.x);
		draw(img, &line, ft_abs(delta.x), &p0);
	}
	else
	{
		line.xstep = (delta.x / delta.y) * line.ystep;
		get_rgbstep(&line, &p0, &p1, delta.y);
		draw(img, &line, ft_abs(delta.y), &p0);
	}
	return ;
}

static void	get_rgbstep(t_line *line, t_vect *p0, t_vect *p1, int delta)
{
	if (delta)
	{
		line->rstep = (float)(p1->red - p0->red) / (float)delta;
		line->gstep = (float)(p1->green - p0->green) / (float)delta;
		line->bstep = (float)(p1->blue - p0->blue) / (float)delta;
	}
	return ;
}

static void	draw(t_img *img, t_line *line, int delta, t_vect *p0)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	x = p0->x;
	y = p0->y;
	while (i <= delta && (line->pt.x < 0 || line->pt.x >= FRAME_WIDTH
		|| line->pt.y < 0 || line->pt.y >= FRAME_HEIGHT))
	{
		calc_color(line);
		img_px_put(img, line->pt.x, line->pt.y, line->pt.color);
		x += line->xstep;
		y += line->ystep;
		line->pt.x = round(x);
		line->pt.y = round(y);
		i++;
	}
	return ;
}

static void	calc_color(t_line *line)
{
	line->pt.red += line->rstep;
	line->pt.green += line->gstep;
	line->pt.blue += line->bstep;
	line->pt.color = encode_rgb(roundf(line->pt.red),
			roundf(line->pt.green), roundf(line->pt.blue));
	return ;
}
