/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:27:03 by adinari           #+#    #+#             */
/*   Updated: 2023/03/08 18:37:30 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

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
			kc_matrix_set_elm(i, j, a.elements[i * a.cols + j]
				+ b.elements[i * a.cols + j], &matrix);
	}
	return (matrix);
}

t_matrix	kc_matrix_multi(t_matrix a, t_matrix b)
{
	t_count		count;
	double		elm;
	t_matrix	matrix;

	matrix = kc_matrix_init(a.rows, b.cols);
	if (a.cols != b.rows)
	{
		printf("Error: Wrong matrix size\n");
		return (matrix);
	}
	count.i = -1;
	while (++count.i < a.rows)
	{
		count.j = -1;
		while (++count.j < b.cols)
		{
			elm = 0;
			count.k = -1;
			while (++count.k < a.cols)
				elm += a.elements[count.i * a.cols + count.k]
					* b.elements[(count.j + count.k) * b.cols + count.j];
			kc_matrix_set_elm(count.i, count.j, elm, &matrix);
		}
	}
	return (matrix);
}

double	g_e(int i, int j, t_matrix matrix)
{
	return (matrix.elements[i * matrix.cols + j]);
}
