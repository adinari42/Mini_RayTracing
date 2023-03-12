/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:19:52 by adinari           #+#    #+#             */
/*   Updated: 2023/03/06 11:21:34 by adinari          ###   ########.fr       */
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
			kc_matrix_set_elm
				(i, j, matrix->elements[i * matrix->cols + j] * s, matrix);
	}
}
