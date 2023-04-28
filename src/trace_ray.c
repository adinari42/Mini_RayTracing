/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:19:47 by adinari           #+#    #+#             */
/*   Updated: 2023/04/18 19:53:40 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	create_color(int r, int g, int b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	color.alpha = 0;
	return (color);
}

t_vector	transform(t_matrix trans, t_vector ray, int translate)
{
	t_matrix	ray_mat;
	t_matrix	res_mat;
	t_vector	res;

	ray_mat = kc_matrix_init(4, 1);
	ray_mat.elements[0] = ray.x;
	ray_mat.elements[1] = ray.y;
	ray_mat.elements[2] = ray.z;
	ray_mat.elements[3] = translate;
	res_mat = kc_matrix_multi(trans, ray_mat);
	free(ray_mat.elements);
	res.x = res_mat.elements[0];
	res.y = res_mat.elements[1];
	res.z = res_mat.elements[2];
	free(res_mat.elements);
	return (res);
}

void	set_hp(t_ray ray, t_data *data, t_hitpoints	*hp)
{
	t_objects	*objs;
	int			i;

	i = -1;
	objs = data->objs;
	while (++i < data->list_size)
	{
		if (objs[i].type == SPHERE)
			hp->temp = intersect_s(ray, (t_sphere *)objs[i].object);
		else if (objs[i].type == CYLINDRE)
			hp->temp = intersect_c(ray, (t_cylindre *)objs[i].object);
		else if (objs[i].type == PLANE)
			hp->temp = intersect_p(ray, (t_plane *)objs[i].object);
		if (hp->temp.dist > 0.000001 && hp->temp.dist < hp->hit.dist)
		{
			hp->hit.dist = hp->temp.dist;
			hp->hit.object = hp->temp.object;
			hp->hit.point = hp->temp.point;
			hp->index = i;
		}
	}
}

t_color	trace_ray(t_ray ray, t_data *data, int depth)
{
	t_color		res;
	t_ray		light;
	t_hitpoints	hp;

	if (depth > 5)
		return (create_color(0, 0, 0));
	hp.hit.dist = INFINITY;
	set_hp(ray, data, &hp);
	if (hp.hit.dist <= 0 || hp.hit.dist == INFINITY)
		return (create_color(0, 0, 0));
	light = create_ray(data->light->point, vector_normalize
			(vector_subtract(hp.hit.point, data->light->point)));
	res = compute_lighting(light, hp.hit, data->light->ratio, ray);
	if (is_shadow(light, data, hp.hit, hp.index) == 1)
		res = create_color(0, 0, 0);
	res = add_ambient(res, data->amb_light);
	return (res);
}

void	trace(t_data *data)
{
	t_count		count;
	t_trace		trace;

	count.i = -1;
	while (++count.i < data->h)
	{
		count.j = -1;
		trace.u = (double)count.i / WIDTH - data->camera->h / 2;
		while (++count.j < data->w)
		{
			trace.v = (double)count.j / WIDTH - data->camera->w / 2;
			trace.d.x = trace.v;
			trace.d.y = trace.u;
			trace.d.z = data->camera->flen;
			trace.d = vector_normalize(trace.d);
			trace.ray = create_ray(create_vector(0, 0, 0), trace.d);
			trace.ray.v = transform(data->camera->trans, trace.ray.v, 0);
			trace.ray.p = transform(data->camera->trans, trace.ray.p, 1);
			trace.color = trace_ray(trace.ray, data, 2);
			data->img[count.i * WIDTH + count.j] = trace.color;
		}
	}
}
