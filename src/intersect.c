/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:37:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/02/26 18:50:28 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitpoint	intersect_s(t_ray ray, t_sphere *sphere)
{
	t_hitpoint	hit;
	t_vector	ls;
	double		tca;
	double		d2;
	double		thc;
	double		t0;
	double		t1;
	double		temp;

	hit.object.color = sphere->color;
	hit.object.object = sphere;
	hit.object.type = SPHERE;
	hit.dist = -1;
	ls = vectorSubtract(sphere->point, ray.p);
	tca = vectorDotProduct(ls, ray.v);
	if (tca < 0) {
		hit.dist = -1;
		return (hit);
	}
	d2 = vectorDotProduct(ls, ls) - tca * tca;
	if (d2 > sphere->diameter * sphere->diameter) {
		hit.dist = -1;
		return (hit);
	}
	thc = sqrt(sphere->diameter * sphere->diameter - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	if (t0 > t1) {
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0)
		{
			hit.dist = -1;
			return (hit);
		}
	}
	// printf("t0 = %f\n", t0);
	hit.dist = t0;
	hit.point = vectorAdd(ray.p, vectorScale(ray.v, t0));
	return (hit);
}

t_hitpoint	intersect_c(t_ray ray, t_cylindre *cylinder)
{
	t_hitpoint	hit;
	t_hitpoint	temp;
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

	hit.object.color = cylinder->color;
	hit.object.object = cylinder;
	hit.object.type = CYLINDRE;
	hit.dist = -1;
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
		point1 = vectorAdd(new_ray.p, vectorScale(new_ray.v, t2));
		if (point1.z <= cylinder->height / 2 && point1.z >= -cylinder->height / 2)
		{
			point1 = transform(cylinder->trans, point1, 1);
			tmp_t = sqrt(pow(point1.x - ray.p.x, 2) + pow(point1.y - ray.p.y, 2) + pow(point1.z - ray.p.z, 2));
			if ((tmp_t > 0 && tmp_t < dist) || dist == -1)
				dist = tmp_t;
		}
	}
	plane.normal = vectorScale(transform(cylinder->trans, create_vector(0,0,1), 0), -1);
	plane.point = transform(cylinder->trans, create_vector(0, 0, -cylinder->height / 2), 1);
	plane.color = create_color(200,105,100);
	temp = intersect_p(ray, &plane);
	if (temp.dist > 0)
	{
		if ((dist > 0 && temp.dist < dist) || dist == -1)
		{
			if (pow(new_ray.p.x + temp.dist * new_ray.v.x, 2) + pow(new_ray.p.y + temp.dist * new_ray.v.y, 2) < pow(cylinder->diameter, 2))
			{
				dist = temp.dist;
				hit.object.color = cylinder->color;
				hit.object.object = &plane;
				hit.object.type = PLANE;
			}
		}
	}
	plane.point = transform(cylinder->trans, create_vector(0, 0, cylinder->height / 2), 1);
	plane.color = create_color(200,0,50);
	temp = intersect_p(ray, &plane);
	if (temp.dist > 0)
	{
		if ((dist > 0 && temp.dist < dist) || dist == -1)
		{
			plane.normal = vectorScale(cylinder->normal, 1);
			if (pow(new_ray.p.x + temp.dist * new_ray.v.x, 2) + pow(new_ray.p.y + temp.dist * new_ray.v.y, 2) < pow(cylinder->diameter, 2))
			{
				dist = temp.dist;
				hit.object.color = cylinder->color;
				hit.object.object = &plane;
				hit.object.type = PLANE;
			}
		}
	}
	hit.dist = dist;
	hit.point = vectorAdd(ray.p, vectorScale(ray.v, dist));
	return (hit);
}

t_hitpoint	intersect_p(t_ray ray, t_plane *plane)
{
	t_hitpoint	hit;
	double		t;
	double		d;

	hit.object.object = plane;
	hit.object.type = PLANE;
	hit.object.color = plane->color;
	hit.dist = -1;
	t = -1;
	d = vectorDotProduct(ray.v, plane->normal);
	if (fabs(d) > EPSILON) {
		t_vector p0l0 = vectorSubtract(plane->point, ray.p);
		t = vectorDotProduct(p0l0, plane->normal) / d;
		if (t < 0)
			t = -1;
	}
	hit.dist = t;
	hit.point = vectorAdd(ray.p, vectorScale(ray.v, t));
	return (hit);
}