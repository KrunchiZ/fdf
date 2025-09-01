/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:52:45 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/01 15:08:56 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
