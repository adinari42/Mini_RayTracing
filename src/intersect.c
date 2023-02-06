/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:37:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/02/02 19:16:44 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	intersect_s(t_ray ray, t_sphere sphere)
{
	t_vector	ls;
	double		tca;
	double		d2;
	double		thc;
	double		t0;
	double		t1;
	double		temp;
	
	ls = vectorSubtract(sphere.point, ray.p);
	tca = vectorDotProduct(ls, ray.v);
	if (tca < 0) {
		return (-1);
	}
	d2 = vectorDotProduct(ls, ls) - tca * tca;
	if (d2 > sphere.diameter * sphere.diameter) {
		return (-1);
	}
	thc = sqrt(sphere.diameter * sphere.diameter - d2);
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
			return (-1);
	}
	return (t0);
}

double	intersect_c(t_ray ray, t_cylindre cylinder)
{
	t_ray	new_ray;
	t_vector	point;
	double		a;
	double		b;
	double		c;
	double		d;
	double		t1;
	double		t2;

	new_ray.p = transform(cylinder.trans_inv, ray.p, 1);
	new_ray.v = transform(cylinder.trans_inv, ray.v, 0);
	printf("Ray before(%f,%f,%f)\n", ray.p.x, ray.p.y, ray.p.z);
	printf("Ray after(%f,%f,%f)\n", new_ray.p.x, new_ray.p.y, new_ray.p.z);
	a = pow(new_ray.v.x, 2) + pow(new_ray.v.y, 2);
	b = 2 * (new_ray.p.x * new_ray.v.x + new_ray.p.y * new_ray.v.y);
	c = pow(new_ray.p.x, 2) + pow(new_ray.p.x, 2) - pow(cylinder.diameter, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2 * a);
		t2 = (-b - sqrt(d)) / (2 * a);
		if (t1 > 0)
		{
			point.z = new_ray.p.z + new_ray.v.z * t1;
			printf("Point before(%f,%f,%f)\n", point.x, point.y, point.z);
			if (point.z < cylinder.height / 2 && point.z > -cylinder.height / 2)
			{
				point = transform(cylinder.trans, point, 1);
				printf("Point after(%f,%f,%f)\n", point.x, point.y, point.z);
				return (sqrt(pow(point.x - ray.p.x, 2) + pow(point.y - ray.p.y, 2) + pow(point.z - ray.p.z, 2)));
			}
		}
		if (t2 > 0)
		{
			point.z = new_ray.p.z + new_ray.v.z * t2;
			if (point.z < cylinder.height / 2 && point.z > -cylinder.height / 2)
			{
				point = transform(cylinder.trans, point, 1);
				return (sqrt(pow(point.x - ray.p.x, 2) + pow(point.y - ray.p.y, 2) + pow(point.z - ray.p.z, 2)));
			}
		}
	}
	return (0);
}

double	intersect_p(t_ray ray, t_plane plane)
{
	double t = -1;
	double d = vectorDotProduct(ray.v, plane.normal);
	if (fabs(d) > EPSILON) {
		t_vector p0l0 = vectorSubtract(plane.point, ray.p);
			t = vectorDotProduct(p0l0, plane.normal) / d;
		if (t < 0)
			t = -1;
	}
	return (t);
}