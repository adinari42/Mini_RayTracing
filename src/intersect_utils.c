/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:50:15 by adinari           #+#    #+#             */
/*   Updated: 2023/03/06 16:28:03 by adinari          ###   ########.fr       */
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

void	init_pl_hp(t_doubles dbl, t_hitpoints hp,
		t_plane plane, t_cylindre *cylinder)
{
	dbl.dist = hp.temp.dist;
	hp.hit.object.color = cylinder->color;
	hp.hit.object.object = &plane;
	hp.hit.object.type = PLANE;
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

t_doubles	calculate_dist(t_ray ray, t_cylindre *cylinder)
{
	t_vector	point1;
	t_ray		new_ray;
	t_doubles	dbl;

	new_ray.p = transform(cylinder->trans_inv, ray.p, 1);
	new_ray.v = transform(cylinder->trans_inv, ray.v, 0);
	dbl = init_doubles(new_ray, cylinder);
	if (dbl.d >= 0)
	{
		dbl.t2 = (-dbl.b - sqrt(dbl.d)) / (2 * dbl.a);
		point1 = vector_add(new_ray.p, vector_scale(new_ray.v, dbl.t2));
		if (point1.z <= cylinder->height / 2
			&& point1.z >= -cylinder->height / 2)
		{
			point1 = transform(cylinder->trans, point1, 1);
			dbl.tmp_t = sqrt(pow(point1.x - ray.p.x, 2)
					+ pow(point1.y - ray.p.y, 2)
					+ pow(point1.z - ray.p.z, 2));
			if (dbl.tmp_t > 0 && dbl.tmp_t < dbl.dist)
			{
				dbl.dist = dbl.tmp_t;
			}
		}
	}
	return (dbl);
}

void	update_hp(t_hitpoints hp, t_plane pl, t_doubles	dbl, t_cylindre *cyl)
{
		dbl.dist = hp.temp.dist;
		hp.hit.object.color = cyl->color;
		hp.hit.object.object = &pl;
		hp.hit.object.type = PLANE;
}
