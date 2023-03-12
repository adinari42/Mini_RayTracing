/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:22:52 by miahmadi          #+#    #+#             */
/*   Updated: 2023/03/08 18:36:53 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	compute_lighting(t_ray light, t_hitpoint hit, double intense, t_ray ray)
{
	t_color			res;
	t_light_vectors	vectors;
	double			i;
	double			teta;

	i = 0;
	teta = 0;
	if (hit.object.type == PLANE)
		teta = set_plane_vectors(&vectors, hit, ray, light);
	else if (hit.object.type == SPHERE)
		teta = set_sphere_vectors(&vectors, hit, ray, light);
	else if (hit.object.type == CYLINDRE)
		teta = set_cylindre_vectors(&vectors, hit, light);
	if (teta > PI / 2)
		i = 0;
	else
		i = (1 - 2 * teta / PI) * intense;
	res = hit.object.color;
	res.red *= i;
	res.green *= i;
	res.blue *= i;
	return (res);
}

int	is_shadow(t_ray light, t_data *data, t_hitpoint hit, int idx)
{
	t_objects	obj;
	t_hitpoint	tmp_hit;
	double		this_hit;
	int			j;

	j = -1;
	this_hit = init_this_hit(hit, light);
	tmp_hit.dist = -1;
	while (++j < data->list_size)
	{
		if (j != idx)
		{
			obj = data->objs[j];
			if (obj.type == PLANE)
				tmp_hit = intersect_p(light, (t_plane *)obj.object);
			else if (obj.type == SPHERE)
				tmp_hit = intersect_s(light, (t_sphere *)obj.object);
			else if (obj.type == CYLINDRE)
				tmp_hit = intersect_c(light, (t_cylindre *)obj.object);
			if (tmp_hit.dist > 0.000001
				&& tmp_hit.dist < this_hit && tmp_hit.object.type)
				return (1);
		}
	}
	return (0);
}

t_color	add_ambient(t_color color, t_amb_light *light)
{
	color.green += (light->color.green * light->ratio);
	color.blue += (light->color.blue * light->ratio);
	color.red += (light->color.red * light->ratio);
	if (color.green > 255)
		color.green = 255;
	if (color.blue > 255)
		color.blue = 255;
	if (color.red > 255)
		color.red = 255;
	return (color);
}
