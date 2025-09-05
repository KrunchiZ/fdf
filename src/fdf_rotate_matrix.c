/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:32:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/06 00:04:56 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_sin_cos(t_mtrx *mx, t_vect *viewangle, t_vect *rotate);
static void	calc_zyx_matrix(t_mtrx *mx);

void	calc_rotate_matrix(t_mod *mod)
{
	update_sin_cos
		(&mod->rotate_matrix, &mod->viewangle[mod->viewmode], &mod->rotate);
	calc_zyx_matrix(&mod->rotate_matrix);
	return ;
}

static void	update_sin_cos(t_mtrx *mx, t_vect *viewangle, t_vect *rotate)
{
	mx->zcos = cos(viewangle->z + rotate->z);
	mx->zsin = sin(viewangle->z + rotate->z);
	mx->ycos = cos(viewangle->y + rotate->y);
	mx->ysin = sin(viewangle->y + rotate->y);
	mx->xcos = cos(viewangle->x + rotate->x);
	mx->xsin = sin(viewangle->x + rotate->x);
	return ;
}

static void	calc_zyx_matrix(t_mtrx *mx)
{
	mx->zyx[2][0] = -(mx->ysin);
	mx->zyx[2][1] = mx->ycos * mx->xsin;
	mx->zyx[2][2] = mx->ycos * mx->xcos;
	mx->zyx[0][0] = mx->zcos * mx->ycos;
	mx->zyx[1][0] = mx->zsin * mx->ycos;
	mx->zyx[0][1] = (mx->zcos * mx->ysin * mx->xsin) - (mx->zsin * mx->xcos);
	mx->zyx[0][2] = (mx->zcos * mx->ysin * mx->xcos) + (mx->zsin * mx->xsin);
	mx->zyx[1][1] = (mx->zsin * mx->ysin * mx->xsin) + (mx->zcos * mx->xcos);
	mx->zyx[1][2] = (mx->zsin * mx->ysin * mx->xcos) - (mx->zcos * mx->xsin);
	return ;
}
