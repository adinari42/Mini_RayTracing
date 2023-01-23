/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:37:11 by miahmadi          #+#    #+#             */
/*   Updated: 2023/01/21 16:33:15 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_s(t_ray ray, t_sphere sphere)
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

int	intersect_c(t_ray ray, t_cylindre cylinder)
{
	t_vector d = ray.v;
	t_vector e = ray.p;
	t_vector c = cylinder.point;
	t_vector m = vectorSubtract(e, c);
	double r = cylinder.diameter;
	double h = cylinder.height;

	printf("HERE\n");
	double dd = vectorDotProduct(d, d);
	double mm = vectorDotProduct(m, m);
	double md = vectorDotProduct(m, d);

	double a = dd - md * md / mm;
	double b = 2 * (md * vectorDotProduct(m, d) / mm - vectorDotProduct(d, e) + vectorDotProduct(d, c));
	double cc = mm - r * r - vectorDotProduct(m, c) * vectorDotProduct(m, c);

	double dis = b * b - 4 * a * cc;
	if (dis < 0) {
		return -1;
	}

	double t1 = (-b - sqrt(dis)) / (2 * a);
	double t2 = (-b + sqrt(dis)) / (2 * a);
	double t = -1;
	if (t1 > EPSILON && t2 > EPSILON) {
		t = fmin(t1, t2);
	} else if (t1 > EPSILON) {
		t = t1;
	} else if (t2 > EPSILON) {
		t = t2;
	}
	if (t < 0) {
		return (-1);
	}

	t_vector p = vectorAdd(e, vectorScale(d, t));
	double y = vectorDotProduct(vectorSubtract(p, c), cylinder.normal);
	if (y < 0 || y > h) {
		return (-1);
	}

	return (t);
}

int	intersect_p(t_ray ray, t_plane plane)
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