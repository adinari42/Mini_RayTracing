/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:54:39 by miahmadi          #+#    #+#             */
/*   Updated: 2023/01/26 18:02:18 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
#define MATRIX_H
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_matrix
{
	int		rows;
	int		cols;
	double	*elements;
}			t_matrix;

t_matrix	kc_matrix_init(int rows, int cols);
void		kc_matrix_print(t_matrix matrix);
void		kc_matrix_set_elm(int row, int col, double val, t_matrix *matrix);
void		kc_matrix_print_single_elm(int row, int col, t_matrix matrix);
void		kc_matrix_scale(double s, t_matrix *matrix);
t_matrix	kc_matrix_sum(t_matrix a, t_matrix b);
t_matrix	kc_matrix_multi(t_matrix a, t_matrix b);
double		g_e(int i, int j, t_matrix matrix);
double		kc_matrix_det_3(t_matrix m);
double		kc_matrix_det_4(t_matrix m);
t_matrix	kc_matrix_get_det(int u, int v, t_matrix m);
t_matrix	kc_matrix_inverse_4(t_matrix m);
t_matrix	kc_matrix_inverse(t_matrix m);

#endif