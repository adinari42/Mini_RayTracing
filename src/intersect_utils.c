/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:50:15 by adinari           #+#    #+#             */
/*   Updated: 2023/03/14 18:21:28 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hitpoints	init_cyl_hp(t_cylindre *cylinder)
{
	t_hitpoints	hp;

	hp.hit.object.color = cylinder->color;
	hp.hit.object.object = cylinder;
	hp.hit.object.type = CYLINDRE;
	hp.hit.dist = -1;
	return (hp);
}

t_doubles	init_doubles(t_ray	new_ray, t_cylindre *cylinder)
{
	t_doubles	dbl;

	dbl.a = pow(new_ray.v.x, 2) + pow(new_ray.v.y, 2);
	dbl.b = 2 * (new_ray.p.x * new_ray.v.x + new_ray.p.y * new_ray.v.y);
	dbl.c = pow(new_ray.p.x, 2) + pow(new_ray.p.y, 2)
		- pow(cylinder->diameter, 2);
	dbl.d = pow(dbl.b, 2) - 4 * dbl.a * dbl.c;
	dbl.dist = -1;
	return (dbl);
}

t_hitpoint	update_hit(t_cylindre *cylinder, t_plane *plane)
{
	t_hitpoint	hit_0;

	hit_0.object.color = cylinder->color;
	hit_0.object.object = &plane;
	hit_0.object.type = PLANE;
	return (hit_0);
}

void	update_2(t_cylindre *cylinder, t_plane *plane,
		t_ray *ray, t_hitpoint *hit_1)
{
	plane->point = transform(cylinder->trans,
			create_vector(0, 0, cylinder->height / 2), 1);
	plane->color = create_color(200, 0, 50);
	*hit_1 = intersect_p(*ray, plane);
}

void	update_point_doubles(t_intrsc_dbl *doubles,
		t_ray *new_ray, t_vector *point1)
{
	doubles->t2 = (-doubles->b - sqrt(doubles->d)) / (2 * doubles->a);
	*point1 = vector_add(new_ray->p, vector_scale(new_ray->v, doubles->t2));
}
