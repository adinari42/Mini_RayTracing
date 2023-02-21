/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:22:52 by miahmadi          #+#    #+#             */
/*   Updated: 2023/02/19 21:45:49 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	compute_lighting(t_ray light, t_hitpoint hit)
{
	t_color	res;
	t_plane	p;
	double	i;
	double	teta;

	p = *(t_plane*)hit.object.object;
	i = 0;
	if (hit.object.type == PLANE)
	{
		// vectorPrint("Light ->", light.v);
		// vectorPrint("plane ->", p.normal);
		// printf("dot = %f\n", vectorDotProduct(light.v, p.normal));
		teta = acos(vectorDotProduct(light.v, p.normal));
		if (teta > PI / 2)
			i = 0;
		else
			i = 1 - 2 * teta / PI;
		printf("i = %f, Teta = %f\n", i, teta);
	}
	else
	{
		i = 1;
	}
	res = hit.object.color;
	res.red *= i;
	res.green *= i;
	res.blue *= i;
	return (res);
}