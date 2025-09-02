/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:52:45 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/02 14:45:09 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fn_draw_along_x(t_img *img, t_vect *p0, t_vect *p1, t_line *line);
static void	fn_draw_along_y(t_img *img, t_vect *p0, t_vect *p1, t_line *line);
static void	fn_calc_color(t_line *line, t_vect *p0, t_vect *p1, float current);

void	fn_draw_line(t_img *img, t_vect p0, t_vect p1)
{
	t_line	line;

	line = (t_line){.pt = p0, .x_step = 1, .y_step = 1};
	if (p0.x > p1.x)
		line.x_step = -1;
	if (p0.y > p1.y)
		line.y_step = -1;
	line.dx = ft_abs(p1.x - p0.x);
	line.dy = ft_abs(p1.y - p0.y);
	if (line.dx >= line.dy)
		fn_draw_along_x(img, &p0, &p1, &line);
	else
		fn_draw_along_y(img, &p0, &p1, &line);
	return ;
}

static void	fn_draw_along_x(t_img *img, t_vect *p0, t_vect *p1, t_line *line)
{
	float	current;
	int		i;
	int		deviation_error;

	deviation_error = line->dx / 2;
	i = 0;
	while (i <= line->dx && line->pt.x >= 0 && line->pt.x <= FRAME_WIDTH)
	{
		if (line->pt.y < 0 || line->pt.y > FRAME_HEIGHT)
			break ;
		if (line->dx > 0)
			current = (float)i / (float)line->dx;
		else
			current = 0.0f;
		fn_calc_color(line, p0, p1, current);
		fn_img_px_put(img, line->pt.x, line->pt.y, line->pt.color);
		line->pt.x += line->x_step;
		deviation_error += line->dy;
		if (deviation_error >= line->dx)
		{
			line->pt.y += line->y_step;
			deviation_error -= line->dx;
		}
		i++;
	}
}

static void	fn_draw_along_y(t_img *img, t_vect *p0, t_vect *p1, t_line *line)
{
	float	current;
	int		i;
	int		deviation_error;

	deviation_error = line->dy / 2;
	i = 0;
	while (i <= line->dy && line->pt.y >= 0 && line->pt.y <= FRAME_HEIGHT)
	{
		if (line->pt.x < 0 || line->pt.x > FRAME_WIDTH)
			break ;
		if (line->dy > 0)
			current = (float)i / (float)line->dy;
		else
			current = 0.0f;
		fn_calc_color(line, p0, p1, current);
		fn_img_px_put(img, line->pt.x, line->pt.y, line->pt.color);
		line->pt.y += line->y_step;
		deviation_error += line->dx;
		if (deviation_error >= line->dy)
		{
			line->pt.x += line->x_step;
			deviation_error -= line->dy;
		}
		i++;
	}
}

static void	fn_calc_color(t_line *line, t_vect *p0, t_vect *p1, float current)
{
	if (current < 0)
		current = 0.0f;
	if (current > 1)
		current = 1.0f;
	line->pt.red = p0->red + roundf(current * (p1->red - p0->red));
	line->pt.green = p0->green + roundf(current * (p1->green - p0->green));
	line->pt.blue = p0->blue + roundf(current * (p1->blue - p0->blue));
	line->pt.color = fn_encode_rgb(line->pt.red, line->pt.green, line->pt.blue);
	return ;
}
