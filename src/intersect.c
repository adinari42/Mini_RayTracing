/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:37:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/03/13 17:13:43 by miahmadi         ###   ########.fr       */
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
	t_hitpoint	hit[2];
	t_ray	new_ray;
	t_vector	point1;
	t_plane		plane;
	double		a;
	double		b;
	double		c;
	double		d;
	double		t2;
	double		dist;
	double		tmp_t;

	hit[0].object.color = cylinder->color;
	hit[0].object.object = cylinder;
	hit[0].object.type = CYLINDRE;
	hit[0].dist = -1;
	new_ray.p = transform(cylinder->trans_inv, ray.p, 1);
	new_ray.v = transform(cylinder->trans_inv, ray.v, 0);
	a = pow(new_ray.v.x, 2) + pow(new_ray.v.y, 2);
	b = 2 * (new_ray.p.x * new_ray.v.x + new_ray.p.y * new_ray.v.y);
	c = pow(new_ray.p.x, 2) + pow(new_ray.p.y, 2) - pow(cylinder->diameter, 2);
	d = pow(b, 2) - 4 * a * c;
	dist = -1;
	if (d >= 0)
	{
		t2 = (-b - sqrt(d)) / (2 * a);
		point1 = vector_add(new_ray.p, vector_scale(new_ray.v, t2));
		if (point1.z <= cylinder->height / 2 && point1.z >= -cylinder->height / 2)
		{
			point1 = transform(cylinder->trans, point1, 1);
			tmp_t = sqrt(pow(point1.x - ray.p.x, 2) + pow(point1.y - ray.p.y, 2) + pow(point1.z - ray.p.z, 2));
			if ((tmp_t > 0 && tmp_t < dist) || dist == -1)
				dist = tmp_t;
		}
	}
	plane.normal = vector_scale(transform(cylinder->trans, create_vector(0,0,1), 0), -1);
	plane.point = transform(cylinder->trans, create_vector(0, 0, -cylinder->height / 2), 1);
	plane.color = create_color(200,105,100);
	hit[1] = intersect_p(ray, &plane);
	if (hit[1].dist > 0)
	{
		if ((dist > 0 && hit[1].dist < dist) || dist == -1)
		{
			if (pow(new_ray.p.x + hit[1].dist * new_ray.v.x, 2) + pow(new_ray.p.y + hit[1].dist * new_ray.v.y, 2) < pow(cylinder->diameter, 2))
			{
				dist = hit[1].dist;
				hit[0].object.color = cylinder->color;
				hit[0].object.object = &plane;
				hit[0].object.type = PLANE;
			}
		}
	}
	plane.point = transform(cylinder->trans, create_vector(0, 0, cylinder->height / 2), 1);
	plane.color = create_color(200,0,50);
	hit[1] = intersect_p(ray, &plane);
	if (hit[1].dist > 0)
	{
		if ((dist > 0 && hit[1].dist < dist) || dist == -1)
		{
			plane.normal = vector_scale(cylinder->normal, 1);
			if (pow(new_ray.p.x + hit[1].dist * new_ray.v.x, 2) + pow(new_ray.p.y + hit[1].dist * new_ray.v.y, 2) < pow(cylinder->diameter, 2))
			{
				dist = hit[1].dist;
				hit[0].object.color = cylinder->color;
				hit[0].object.object = &plane;
				hit[0].object.type = PLANE;
			}
		}
	}
	hit[0].dist = dist;
	hit[0].point = vector_add(ray.p, vector_scale(ray.v, dist));
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
