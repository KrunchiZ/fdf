/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:32:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/10/22 21:29:26 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void	set_matrix(t_mtrx *matrix, t_vect *angle);
static void	multiply_matrix(float mc[3][3], float ma[3][3], float mb[3][3]);

void	calc_rotate_matrix(t_mod *mod, int rotate_src)
{
	t_mtrx	matrix;
	int		i;

	matrix = (t_mtrx){0};
	i = 0;
	while (i < 3)
	{
		matrix.x[i][i] = 1.0f;
		matrix.y[i][i] = 1.0f;
		matrix.z[i][i] = 1.0f;
		i++;
	}
	if (rotate_src == VIEW_ANGLE)
	{
		set_matrix(&matrix, &mod->viewangle[mod->viewmode]);
		multiply_matrix(matrix.ab, matrix.x, matrix.y);
		multiply_matrix(mod->rotate_matrix, matrix.ab, matrix.z);
	}
	if (rotate_src == ROTATE_MOD)
	{
		set_matrix(&matrix, &mod->rotate);
		multiply_matrix(matrix.ab, matrix.y, matrix.x);
		multiply_matrix(mod->rotate_state, matrix.ab, matrix.z);
	}
	return ;
}

static void	set_matrix(t_mtrx *matrix, t_vect *angle)
{
	matrix->x[1][1] = cos(angle->x * M_PI / 180.0f);
	matrix->x[2][1] = sin(angle->x * M_PI / 180.0f);
	matrix->y[0][0] = cos(angle->y * M_PI / 180.0f);
	matrix->y[0][2] = sin(angle->y * M_PI / 180.0f);
	matrix->z[0][0] = cos(angle->z * M_PI / 180.0f);
	matrix->z[1][0] = sin(angle->z * M_PI / 180.0f);
	matrix->x[1][2] = -(matrix->x[2][1]);
	matrix->x[2][2] = matrix->x[1][1];
	matrix->y[2][0] = -(matrix->y[0][2]);
	matrix->y[2][2] = matrix->y[0][0];
	matrix->z[0][1] = -(matrix->z[1][0]);
	matrix->z[1][1] = matrix->z[0][0];
	return ;
}

static void	multiply_matrix(float mc[3][3], float ma[3][3], float mb[3][3])
{
	int		i;

	i = 0;
	while (i < 3)
	{
		mc[i][0]
			= ma[i][0] * mb[0][0] + ma[i][1] * mb[1][0] + ma[i][2] * mb[2][0];
		mc[i][1]
			= ma[i][0] * mb[0][1] + ma[i][1] * mb[1][1] + ma[i][2] * mb[2][1];
		mc[i][2]
			= ma[i][0] * mb[0][2] + ma[i][1] * mb[1][2] + ma[i][2] * mb[2][2];
		i++;
	}
	return ;
}
