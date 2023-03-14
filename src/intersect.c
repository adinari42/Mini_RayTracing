/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:37:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/03/14 18:21:17 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitpoint	intersect_s(t_ray ray, t_sphere *sphere)
{
	t_hitpoint			hit;
	t_intersect_vars	vars;

	hit.object.color = sphere->color;
	hit.object.object = sphere;
	hit.object.type = SPHERE;
	hit.dist = -1;
	vars.ls = vector_subtract(sphere->point, ray.p);
	vars.tca = vector_dot_product(vars.ls, ray.v);
	vars.d2 = vector_dot_product(vars.ls, vars.ls) - vars.tca * vars.tca;
	if (vars.d2 > sphere->diameter * sphere->diameter)
		return (hit);
	vars.thc = sqrt(sphere->diameter * sphere->diameter - vars.d2);
	vars.t0 = vars.tca - vars.thc;
	if (vars.t0 > 0)
		hit.dist = vars.t0;
	else
		hit.dist = vars.tca + vars.thc;
	if (hit.dist < 0)
		return (hit);
	hit.point = vector_add(ray.p, vector_scale(ray.v, hit.dist));
	return (hit);
}

int	update_hit_cond_2(t_cylindre *cylinder, t_plane *plane,
		t_intrsc_dbl *doubles, t_hitpoint *hit_1)
{
	if (hit_1->dist > 0)
	{
		if ((doubles->dist > 0
				&& hit_1->dist < doubles->dist) || doubles->dist == -1)
		{
			plane->normal = vector_scale(cylinder->normal, 1);
			return (1);
		}
	}
	return (0);
}

t_hitpoint	intersect_c(t_ray ray, t_cylindre *cylinder)
{
	t_hitpoint		hit[2];
	t_ray			new_ray;
	t_vector		point1;
	t_plane			plane;
	t_intrsc_dbl	doubles;

	init_hit(cylinder, &hit[0]);
	intersect_init(cylinder, &new_ray, &doubles, &ray);
	if (doubles.d >= 0)
	{
		update_point_doubles(&doubles, &new_ray, &point1);
		cond_1(cylinder, &point1, &doubles, &ray);
	}
	init_plane(&ray, cylinder, &hit[1], &plane);
	if (update_hit_cond(cylinder, &new_ray, &doubles, &hit[1]))
		hit[0] = create_cylndr_plane(cylinder->color, \
					&plane, &doubles, hit[1].dist);
	update_2(cylinder, &plane, &ray, &hit[1]);
	if (update_hit_cond_2(cylinder, &plane, &doubles, &hit[1]) \
				&& calculate_dist_from_cyl(new_ray, hit[1], cylinder->diameter))
			hit[0] = create_cylndr_plane(cylinder->color, \
						&plane, &doubles, hit[1].dist);
	hit[0].dist = doubles.dist;
	hit[0].point = vector_add(ray.p, vector_scale(ray.v, doubles.dist));
	return (hit[0]);
}

t_hitpoint	intersect_p(t_ray ray, t_plane *plane)
{
	t_hitpoint	hit;
	double		t;
	double		d;
	t_vector	p0l0;

	hit.object.object = plane;
	hit.object.type = PLANE;
	hit.object.color = plane->color;
	hit.dist = -1;
	t = -1;
	d = vector_dot_product(ray.v, plane->normal);
	if (fabs(d) > EPSILON)
	{
		p0l0 = vector_subtract(plane->point, ray.p);
		t = vector_dot_product(p0l0, plane->normal) / d;
		if (t < 0)
			t = -1;
	}
	hit.dist = t;
	hit.point = vector_add(ray.p, vector_scale(ray.v, t));
	return (hit);
}
