/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:19:13 by adinari           #+#    #+#             */
/*   Updated: 2023/03/14 18:19:36 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calculate_dist_from_cyl(t_ray new_ray, t_hitpoint hit, double dia)
{
	if (pow(new_ray.p.x + hit.dist * new_ray.v.x, 2) + \
		pow(new_ray.p.y + hit.dist * new_ray.v.y, 2) < pow(dia, 2))
		return (1);
	return (0);
}

t_hitpoint	create_cylndr_plane(t_color color,
	t_plane *p, t_intrsc_dbl *dbs, double dist)
{
	t_hitpoint	hit;

	dbs->dist = dist;
	hit.object.color = color;
	hit.object.object = p;
	hit.object.type = PLANE;
	return (hit);
}
