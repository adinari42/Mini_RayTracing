/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:55:16 by adinari           #+#    #+#             */
/*   Updated: 2023/03/06 16:28:03 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cond_1(t_hitpoints hp, t_ray *new_ray, t_cylindre *cylinder)
{
	if (pow(new_ray->p.x + hp.temp.dist * new_ray->v.x, 2)
		+ pow(new_ray->p.y + hp.temp.dist * new_ray->v.y, 2)
		< pow(cylinder->diameter, 2))
		return (1);
	return (0);
}

int	cond_2(t_hitpoints hp, t_ray *new_ray, t_cylindre *cylinder)
{
	if (pow(new_ray->p.x + hp.temp.dist * new_ray->v.x, 2)
		+ pow(new_ray->p.y + hp.temp.dist * new_ray->v.y, 2)
		< pow(cylinder->diameter, 2))
		return (1);
	return (0);
}

void	init_structs(t_plane *plane, t_cylindre *cylinder,
		t_hitpoints *hp, t_ray ray)
{
	*hp = init_cyl_hp(cylinder);
	plane->normal = vector_scale(transform(cylinder->trans,
				create_vector(0, 0, 1), 0), -1);
	plane->point = transform(cylinder->trans,
			create_vector(0, 0, -cylinder->height / 2), 1);
	plane->color = create_color(200, 105, 100);
	hp->temp = intersect_p(ray, plane);
}

void	update_pl(t_plane	*plane, t_cylindre *cylinder)
{
	plane->point = transform(cylinder->trans,
			create_vector(0, 0, cylinder->height / 2), 1);
	plane->color = create_color(200, 0, 50);
}
