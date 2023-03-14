/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:55:16 by adinari           #+#    #+#             */
/*   Updated: 2023/03/14 18:11:36 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_hit(t_cylindre *cylinder, t_hitpoint *hit_0)
{
	hit_0->object.color = cylinder->color;
	hit_0->object.object = cylinder;
	hit_0->object.type = CYLINDRE;
	hit_0->dist = -1;
}

void	intersect_init(t_cylindre *cylinder,
	t_ray *new_ray, t_intrsc_dbl *doubles, t_ray *ray)
{
	new_ray->p = transform(cylinder->trans_inv, ray->p, 1);
	new_ray->v = transform(cylinder->trans_inv, ray->v, 0);
	doubles->a = pow(new_ray->v.x, 2) + pow(new_ray->v.y, 2);
	doubles->b = 2 * (new_ray->p.x * new_ray->v.x
			+ new_ray->p.y * new_ray->v.y);
	doubles->c = pow(new_ray->p.x, 2)
		+ pow(new_ray->p.y, 2) - pow(cylinder->diameter, 2);
	doubles->d = pow(doubles->b, 2) - 4 * doubles->a * doubles->c;
	doubles->dist = -1;
}

void	cond_1(t_cylindre *cylinder,
	t_vector *point1, t_intrsc_dbl *doubles, t_ray *ray)
{
	if (point1->z <= cylinder->height / 2 && point1->z >= -cylinder->height / 2)
	{
		*point1 = transform(cylinder->trans, *point1, 1);
		doubles->tmp_t = sqrt(pow(point1->x - ray->p.x, 2)
				+ pow(point1->y - ray->p.y, 2) + pow(point1->z - ray->p.z, 2));
		if ((doubles->tmp_t > 0
				&& doubles->tmp_t < doubles->dist) || doubles->dist == -1)
			doubles->dist = doubles->tmp_t;
	}
}

void	init_plane(t_ray *ray, t_cylindre *cylinder,
		t_hitpoint *hit_1, t_plane *plane)
{
	plane->normal = vector_scale(transform(cylinder->trans,
				create_vector(0, 0, 1), 0), -1);
	plane->point = transform(cylinder->trans,
			create_vector(0, 0, -cylinder->height / 2), 1);
	plane->color = create_color(200, 105, 100);
	*hit_1 = intersect_p(*ray, plane);
}

int	update_hit_cond(t_cylindre *cylinder,
	t_ray *new_ray, t_intrsc_dbl *doubles, t_hitpoint *hit_1)
{
	if (hit_1->dist > 0)
		if ((doubles->dist > 0
				&& hit_1->dist < doubles->dist) || doubles->dist == -1)
			if (pow(new_ray->p.x + hit_1->dist * new_ray->v.x, 2)
				+ pow(new_ray->p.y + hit_1->dist * new_ray->v.y, 2)
				< pow(cylinder->diameter, 2))
				return (1);
	return (0);
}
