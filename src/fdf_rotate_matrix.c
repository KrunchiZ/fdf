/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:32:17 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/09 19:12:16 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_matrix(t_mtrx *matrix, t_vect *viewangle);
static void	multiply_matrix(float mc[3][3], float ma[3][3], float mb[3][3]);

void	calc_rotate_matrix(t_mod *mod)
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
		matrix.ab[i][i] = 1.0f;
		i++;
	}
	set_matrix(&matrix, &mod->viewangle[mod->viewmode]);
	multiply_matrix(matrix.ab, matrix.z, matrix.x);
	multiply_matrix(mod->rotate_matrix, matrix.ab, matrix.y);
	return ;
}

static void	set_matrix(t_mtrx *matrix, t_vect *viewangle)
{
	matrix->x[1][1] = cos(viewangle->x * M_PI / 180.0f);
	matrix->x[2][1] = sin(viewangle->x * M_PI / 180.0f);
	matrix->y[0][0] = cos(viewangle->y * M_PI / 180.0f);
	matrix->y[0][2] = sin(viewangle->y * M_PI / 180.0f);
	matrix->z[0][0] = cos(viewangle->z * M_PI / 180.0f);
	matrix->z[1][0] = sin(viewangle->z * M_PI / 180.0f);
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

void	update_coordinates(t_vect *new_pt, t_vect *pt, float mtrx[3][3])
{
	new_pt->x = mtrx[0][0] * pt->x + mtrx[0][1] * pt->y + mtrx[0][2] * pt->z;
	new_pt->y = mtrx[1][0] * pt->x + mtrx[1][1] * pt->y + mtrx[1][2] * pt->z;
	new_pt->z = mtrx[2][0] * pt->x + mtrx[2][1] * pt->y + mtrx[2][2] * pt->z;
	new_pt->y = -(new_pt->y);
	return ;
}
