/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:52:45 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/02 01:46:43 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fn_draw_along_x(t_img *img, t_vect *pt0, t_vect *pt1, t_line *line);
static void	fn_draw_along_y(t_img *img, t_vect *pt0, t_vect *pt1, t_line *line);
static void	fn_set_rgb_step(t_line *line, t_vect *pt0, t_vect *pt1, int steps);
static void	fn_apply_color_step(t_line *line, t_vect *pt0, t_vect *pt1);

void	fn_draw_line(t_img *img, t_vect pt0, t_vect pt1)
{
	t_line	line;

	line = (t_line){.pt = pt0, .x_step = 1, .y_step = 1};
	if (pt0.x > pt1.x)
		line.x_step = -1;
	if (pt0.y > pt1.y)
		line.y_step = -1;
	line.dx = ft_abs(pt1.x - pt0.x);
	line.dy = ft_abs(pt1.y - pt0.y);
	if (line.dx >= line.dy)
		fn_draw_along_x(img, &pt0, &pt1, &line);
	else
		fn_draw_along_y(img, &pt0, &pt1, &line);
	return ;
}

static void	fn_draw_along_x(t_img *img, t_vect *pt0, t_vect *pt1, t_line *line)
{
	int	i;
	int	deviation_error;

	fn_set_rgb_step(line, pt0, pt1, line->dx);
	deviation_error = line->dx / 2;
	i = 0;
	while (i <= line->dx && line->pt.x >= 0 && line->pt.x <= FRAME_WIDTH)
	{
		if (line->pt.y < 0 || line->pt.y > FRAME_HEIGHT)
			break ;
		fn_img_px_put(img, line->pt.x, line->pt.y, line->pt.color);
		line->pt.x += line->x_step;
		deviation_error += line->dy;
		if (deviation_error >= line->dx)
		{
			line->pt.y += line->y_step;
			deviation_error -= line->dx;
		}
		fn_apply_color_step(line, pt0, pt1);
		i++;
	}
	return ;
}

static void	fn_draw_along_y(t_img *img, t_vect *pt0, t_vect *pt1, t_line *line)
{
	int	i;
	int	deviation_error;

	fn_set_rgb_step(line, pt0, pt1, line->dy);
	deviation_error = line->dy / 2;
	i = 0;
	while (i <= line->dy && line->pt.y >= 0 && line->pt.y <= FRAME_HEIGHT)
	{
		if (line->pt.x < 0 || line->pt.x > FRAME_WIDTH)
			break ;
		fn_img_px_put(img, line->pt.x, line->pt.y, line->pt.color);
		line->pt.y += line->y_step;
		deviation_error += line->dx;
		if (deviation_error >= line->dy)
		{
			line->pt.x += line->x_step;
			deviation_error -= line->dy;
		}
		fn_apply_color_step(line, pt0, pt1);
		i++;
	}
	return ;
}

static void	fn_set_rgb_step(t_line *line, t_vect *pt0, t_vect *pt1, int steps)
{
	line->step.r = (pt1->red - pt0->red) / steps;
	line->step.g = (pt1->green - pt0->green) / steps;
	line->step.b = (pt1->blue - pt0->blue) / steps;
	line->modulo.r = (pt1->red - pt0->red) % steps;
	line->modulo.g = (pt1->green - pt0->green) % steps;
	line->modulo.b = (pt1->blue - pt0->blue) % steps;
	line->deviate.r = ft_abs(pt1->red - pt0->red) / 2;
	line->deviate.g = ft_abs(pt1->green - pt0->green) / 2;
	line->deviate.b = ft_abs(pt1->blue - pt0->blue) / 2;
	return ;
}

static void	fn_apply_color_step(t_line *line, t_vect *pt0, t_vect *pt1)
{
	line->pt.red += line->step.r;
	line->pt.green += line->step.g;
	line->pt.blue += line->step.b;
	line->deviate.r += ft_abs(line->modulo.r);
	line->deviate.g += ft_abs(line->modulo.g);
	line->deviate.b += ft_abs(line->modulo.b);
	if (line->deviate.r >= pt1->red - pt0->red)
	{
		line->pt.red += line->step.r;
		line->deviate.r -= pt1->red - pt0->red;
	}
	if (line->deviate.g >= pt1->green - pt0->green)
	{
		line->pt.green += line->step.g;
		line->deviate.g -= pt1->green - pt0->green;
	}
	if (line->deviate.b >= pt1->blue - pt0->blue)
	{
		line->pt.blue += line->step.b;
		line->deviate.b -= pt1->blue - pt0->blue;
	}
	line->pt.color = fn_encode_rgb(line->pt.red, line->pt.green, line->pt.blue);
	return ;
}
