/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:32:26 by adinari           #+#    #+#             */
/*   Updated: 2023/03/06 16:35:51 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vector_dot_product_print(t_vector v1, t_vector v2)
{
	vector_print("Light ->", v1);
	vector_print("plane ->", v2);
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	vector_cross_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = (v1.y * v2.z) - (v2.y * v1.z);
	res.y = (v1.z * v2.x) - (v2.z * v1.x);
	res.z = (v1.x * v2.y) - (v2.x * v1.y);
	return (res);
}

t_vector	vector_project(t_vector v1, t_vector v2)
{
	double	dot;
	double	square;

	dot = vector_dot_product(v1, v2);
	square = vector_dot_product(v2, v2);
	return (vector_scale(v2, dot / square));
}

void	vector_print(char *msg, t_vector v)
{
	printf("%s (%f, %f, %f)\n", msg, v.x, v.y, v.z);
}
