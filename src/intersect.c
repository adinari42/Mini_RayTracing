/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:37:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/03/06 16:28:49 by adinari          ###   ########.fr       */
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

t_hitpoint	intersect_c(t_ray ray, t_cylindre *cylinder)
{
	t_hitpoints	hp;
	t_ray		new_ray;
	t_plane		plane;
	t_doubles	dbl;

	dbl = calculate_dist(ray, cylinder);
	init_structs(&plane, cylinder, &hp, ray);
	if (hp.temp.dist > 0)
		if ((dbl.dist > 0 && hp.temp.dist < dbl.dist) || dbl.dist == -1)
			if (cond_1(hp, &new_ray, cylinder))
				update_hp(hp, plane, dbl, cylinder);
	update_pl(&plane, cylinder);
	hp.temp = intersect_p(ray, &plane);
	if (hp.temp.dist > 0)
	{
		if ((dbl.dist > 0 && hp.temp.dist < dbl.dist) || dbl.dist == -1)
		{
			plane.normal = vector_scale(cylinder->normal, 1);
			if (cond_2(hp, &new_ray, cylinder))
				init_pl_hp(dbl, hp, plane, cylinder);
		}
	}
	hp.hit.dist = dbl.dist;
	hp.hit.point = vector_add(ray.p, vector_scale(ray.v, dbl.dist));
	return (hp.hit);
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
