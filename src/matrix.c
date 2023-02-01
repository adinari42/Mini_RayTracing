/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:56:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/02/01 21:54:55 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	kc_matrix_set_elm(int row, int col, double val, t_matrix *matrix)
{
	matrix->elements[row * (matrix->cols) + col] = val;
}

void	kc_matrix_print_single_elm(int row, int col, t_matrix matrix)
{
	printf("%-8.3f ", matrix.elements[row * matrix.cols + col]);
}

void	kc_matrix_print(t_matrix matrix)
{
	int	i;
	int	j;

	i = -1;
	while (++i < matrix.rows)
	{
		j = -1;
		while (++j < matrix.cols)
			kc_matrix_print_single_elm(i, j, matrix);
		printf("\n");
	}
}

t_matrix	kc_matrix_init(int rows, int cols)
{
	t_matrix	matrix;
	int			i;
	int			j;

	matrix.elements = malloc(rows * cols * sizeof(double));
	matrix.rows = rows;
	matrix.cols = cols;
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
			kc_matrix_set_elm(i, j, 0, &matrix);
	}
	return (matrix);
}

void	kc_matrix_scale(double s, t_matrix *matrix)
{
	int	i;
	int	j;

	i = -1;
	while (++i < matrix->rows)
	{
		j = -1;
		while (++j < matrix->cols)
			kc_matrix_set_elm(i, j, matrix->elements[i * matrix->cols + j] * s, matrix);
	}
}

t_matrix	kc_matrix_sum(t_matrix a, t_matrix b)
{
	t_matrix	matrix;
	int			i;
	int			j;

	matrix = kc_matrix_init(a.rows, a.cols);
	if (a.cols != b.cols || a.rows != b.rows)
	{
		printf("Error: matrices must be the same size\n");
		return (matrix);
	}
	i = -1;
	while (++i < a.rows)
	{
		j = -1;
		while (++j < a.cols)
			kc_matrix_set_elm(i, j, a.elements[i * a.cols + j] + b.elements[i * a.cols + j], &matrix);
	}
	return (matrix);
}

t_matrix	kc_matrix_multi(t_matrix a, t_matrix b)
{
	int			i;
	int			j;
	int			k;
	double		elm;
	t_matrix	matrix;

	matrix = kc_matrix_init(a.rows, b.cols);
	if (a.cols != b.rows)
	{
		printf("Error: Wrong matrix size\n");
		return (matrix);
	}
	i = -1;
	while (++i < a.rows)
	{
		j = -1;
		while (++j < b.cols)
		{
			elm = 0;
			k = -1;
			while (++k < a.cols)
				elm += a.elements[i * a.cols + k] * b.elements[(j + k) * b.cols + j];
			kc_matrix_set_elm(i, j, elm, &matrix);
		}
	}
	return (matrix);
}

double	g_e(int i, int j, t_matrix matrix)
{
	return (matrix.elements[i * matrix.cols + j]);
}

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
	det = kc_matrix_get_det(1, 0, m);
	res -= g_e(1, 0, m) * kc_matrix_det_3(det);
	det = kc_matrix_get_det(2, 0, m);
	res += g_e(2, 0, m) * kc_matrix_det_3(det);
	det = kc_matrix_get_det(3, 0, m);
	res -= g_e(3, 0, m) * kc_matrix_det_3(det);
	printf("Res = %f\n", res);
	return (res);
}

t_matrix	kc_matrix_get_det(int u, int v, t_matrix m)
{
	int			i;
	int			j;
	int			x;
	int			y;
	t_matrix	matrix;

	matrix = kc_matrix_init(3, 3);
	i = -1;
	x = 0;
	while (++i < 4)
	{
		if (i != u)
		{
			j = -1;
			y = 0;
			while (++j < 4)
			{
				if (j != v)
				{
					kc_matrix_set_elm(x, y, g_e(i, j, m), &matrix);
					y++;
				}
			}
			x++;
		}
	}
	return (matrix);
}

t_matrix	kc_matrix_inverse_4(t_matrix m)
{
	t_matrix	matrix;
	t_matrix	det;
	int			i;
	int			j;
	double		elm;
	double		t;

	matrix = kc_matrix_init(4, 4);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			det = kc_matrix_get_det(j, i, m);
			elm = pow(-1, i + j) * kc_matrix_det_3(det);
			kc_matrix_set_elm(i, j, elm, &matrix);
		}
	}
	t = kc_matrix_det_4(m);
	printf("T = %f\n", t);
	kc_matrix_scale((double)1 / kc_matrix_det_4(m), &matrix);
	return (matrix);
}

t_matrix	kc_matrix_inverse(t_matrix m)
{
	t_matrix matrix;

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