/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:50:15 by adinari           #+#    #+#             */
/*   Updated: 2023/03/12 19:19:51 by miahmadi         ###   ########.fr       */
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

