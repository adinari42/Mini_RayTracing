/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:44:04 by adinari           #+#    #+#             */
/*   Updated: 2023/03/06 16:28:49 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	set_plane_vectors(t_light_vectors	*vectors, t_hitpoint hit,
			t_ray ray, t_ray light)
{
	double	teta;

	vectors->n = (*(t_plane *)hit.object.object).normal;
	if (vector_dot_product(vectors->n, ray.v) < 0)
		vectors->n = vector_scale(vectors->n, -1);
	teta = acos(vector_dot_product(light.v, vectors->n));
	return (teta);
}

double	set_sphere_vectors(t_light_vectors	*vectors, t_hitpoint hit,
			t_ray ray, t_ray light)
{
	double	teta;

	vectors->n = vector_normalize
		(vector_subtract((*(t_sphere*)hit.object.object).point,
				hit.point));
	if (vector_dot_product(vectors->n, ray.v) < 0)
		vectors->n = vector_scale(vectors->n, -1);
	teta = acos(vector_dot_product(light.v, vectors->n));
	return (teta);
}

double	set_cylindre_vectors(t_light_vectors *vectors,
		t_hitpoint hit, t_ray light)
{
	double	teta;

	vectors->p = transform((*(t_cylindre *)hit.object.object).trans_inv,
			hit.point, 1);
	vectors->cen = create_vector(0, 0, vectors->p.z);
	vectors->n = vector_subtract(vectors->cen, vectors->p);
	vectors->n = vector_normalize
		(transform((*(t_cylindre *)hit.object.object).trans,
				vectors->n, 0));
	teta = acos(vector_dot_product(light.v, vectors->n));
	return (teta);
}

double	init_this_hit(t_hitpoint hit, t_ray light)
{
	double	this_hit;

	this_hit = sqrt(pow(hit.point.x - light.p.x, 2)
			+ pow(hit.point.y - light.p.y, 2)
			+ pow(hit.point.z - light.p.z, 2)) - 0.000001;
	return (this_hit);
}
