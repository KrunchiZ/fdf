/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:32:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/05 18:23:48 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_matrix(t_mtrx *matrix, t_vect *viewangle, t_vect *rotate);

void	calc_rotate_matrix(t_mod *mod)
{
	update_matrix
		(&mod->rotate_matrix, &mod->viewangle[mod->viewmode], &mod->rotate);
	multiply_matrix
		(mod->rotate_matrix.zy, mod->rotate_matrix.z, mod->rotate_matrix.y);
	multiply_matrix
		(mod->rotate_matrix.zyx, mod->rotate_matrix.zy, mod->rotate_matrix.x);
	return ;
}

static void	update_matrix(t_mtrx *matrix, t_vect *viewangle, t_vect *rotate)
{
	matrix->z[0][0] = cos(viewangle->z + rotate->z);
	matrix->z[1][0] = sin(viewangle->z + rotate->z);
	matrix->z[0][1] = -(matrix->z[1][0]);
	matrix->z[1][1] = matrix->z[0][0];
	matrix->y[0][0] = cos(viewangle->y + rotate->y);
	matrix->y[0][2] = sin(viewangle->y + rotate->y);
	matrix->y[2][0] = -(matrix->y[0][2]);
	matrix->y[2][2] = matrix->y[0][0];
	matrix->x[1][1] = cos(viewangle->x + rotate->x);
	matrix->x[2][1] = sin(viewangle->x + rotate->x);
	matrix->x[1][2] = -(matrix->x[2][1]);
	matrix->x[2][2] = matrix->x[1][1];
	return ;
}

static void	multiply_matrix(float **mc, float **ma, float **mb)
{
	mc = ma * mb;
}
