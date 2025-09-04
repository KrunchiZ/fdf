/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:52:45 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/04 10:46:06 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_line(t_line *line, t_vect *p0, t_vect *p1);
static void	get_rgbstep(t_line *line, t_vect *p0, t_vect *p1, int delta);
static void	draw(t_img *img, t_line *line, int delta);
static void	calc_color(t_line *line);

void	draw_line(t_img *img, t_vect p0, t_vect p1)
{
	t_line	line;

	init_line(&line, &p0, &p1);
	if (ft_abs(line.dx) >= ft_abs(line.dy))
	{
		line.ystep = 0.0f;
		if (line.dy)
			line.ystep = (line.dy / line.dx) * line.xstep;
		get_rgbstep(&line, &p0, &p1, line.dx);
		draw(img, &line, ft_abs(line.dx));
	}
	else
	{
		line.xstep = 0.0f;
		if (line.dx)
			line.xstep = (line.dx / line.dy) * line.ystep;
		get_rgbstep(&line, &p0, &p1, line.dy);
		draw(img, &line, ft_abs(line.dy));
	}
	return ;
}

static void	init_line(t_line *line, t_vect *p0, t_vect *p1)
{
	*line = (t_line){.pt = *p0, .xstep = 1.0f, .ystep = 1.0f};
	if (p0->x > p1->x)
		line->xstep = -1.0f;
	if (p0->y > p1->y)
		line->ystep = -1.0f;
	line->dx = p1->x - p0->x;
	line->dy = p1->y - p0->y;
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

static void	draw(t_img *img, t_line *line, int delta)
{
	int		i;

	i = 0;
	while (i <= delta)
	{
		if (!(line->pt.x < 0.0f || line->pt.x >= FRAME_WIDTH
				|| line->pt.y < 0.0f || line->pt.y >= FRAME_HEIGHT))
			img_px_put(img, roundf(line->pt.x),
				roundf(line->pt.y), line->pt.color);
		calc_color(line);
		line->pt.x += line->xstep;
		line->pt.y += line->ystep;
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
