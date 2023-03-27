/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:56:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/03/27 17:43:59 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

double	kc_matrix_det_3(t_matrix m)
{
	double	res;

	if (m.cols != 3)
	{
		printf("Error: Matrice size should be 3\n");
		return (NAN);
	}
	res = g_e(0, 0, m) * g_e(1, 1, m) * g_e(2, 2, m) \
		+ g_e(0, 1, m) * g_e(1, 2, m) * g_e(2, 0, m) \
		+ g_e(0, 2, m) * g_e(1, 0, m) * g_e(2, 1, m) \
		- g_e(0, 2, m) * g_e(1, 1, m) * g_e(2, 0, m) \
		- g_e(0, 1, m) * g_e(1, 0, m) * g_e(2, 2, m) \
		- g_e(0, 0, m) * g_e(1, 2, m) * g_e(2, 1, m);
	return (res);
}

double	kc_matrix_det_4(t_matrix m)
{
	double		res;
	t_matrix	det;

	if (m.cols != 4)
	{
		printf("Error: Matrice size should be 3\n");
		return (NAN);
	}
	det = kc_matrix_get_det(0, 0, m);
	res = g_e(0, 0, m) * kc_matrix_det_3(det);
	free(det.elements);
	det = kc_matrix_get_det(1, 0, m);
	res -= g_e(1, 0, m) * kc_matrix_det_3(det);
	free(det.elements);
	det = kc_matrix_get_det(2, 0, m);
	res += g_e(2, 0, m) * kc_matrix_det_3(det);
	free(det.elements);
	det = kc_matrix_get_det(3, 0, m);
	res -= g_e(3, 0, m) * kc_matrix_det_3(det);
	free(det.elements);
	return (res);
}

t_matrix	kc_matrix_get_det(int u, int v, t_matrix m)
{
	t_count		count;
	t_matrix	matrix;

	matrix = kc_matrix_init(3, 3);
	count.i = -1;
	count.x = 0;
	while (++count.i < 4)
	{
		if (count.i != u)
		{
			count.j = -1;
			count.y = 0;
			while (++count.j < 4)
			{
				if (count.j != v)
				{
					kc_matrix_set_elm
						(count.x, count.y, g_e(count.i, count.j, m), &matrix);
					count.y++;
				}
			}
			count.x++;
		}
	}
	return (matrix);
}

t_matrix	kc_matrix_inverse_4(t_matrix m)
{
	t_matrix	matrix;
	t_matrix	det;
	t_count		count;
	double		elm;
	double		t;

	matrix = kc_matrix_init(4, 4);
	count.i = -1;
	while (++count.i < 4)
	{
		count.j = -1;
		while (++count.j < 4)
		{
			det = kc_matrix_get_det(count.j, count.i, m);
			elm = pow(-1, count.i + count.j) * kc_matrix_det_3(det);
			free(det.elements);
			kc_matrix_set_elm(count.i, count.j, elm, &matrix);
		}
	}
	t = kc_matrix_det_4(m);
	kc_matrix_scale((double)1 / kc_matrix_det_4(m), &matrix);
	return (matrix);
}

t_matrix	kc_matrix_inverse(t_matrix m)
{
	t_matrix	matrix;

	if (m.cols != m.rows)
	{
		printf("Error: matrice dimensions are not equal\n");
		matrix = kc_matrix_init(1, 1);
		return (matrix);
	}
	if (m.cols > 4)
	{
		printf("Error: matrice dimensions are bigger than 4\n");
		matrix = kc_matrix_init(1, 1);
		return (matrix);
	}
	if (m.cols == 4)
		matrix = kc_matrix_inverse_4(m);
	else
		matrix = kc_matrix_init(1, 1);
	return (matrix);
}
