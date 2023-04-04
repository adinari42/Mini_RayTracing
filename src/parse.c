/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 04:06:34 by adinari           #+#    #+#             */
/*   Updated: 2023/04/04 07:51:07 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(t_objects *obj_list, t_data *data, int i)
{
	t_camera		*obj;
	t_parse_vectors	vectors;

	obj = malloc(sizeof(t_camera));
	obj_list[i].object = obj;
	if (!ft_isfloat(data->infos[3])
		&& ft_atof(data->infos[3]) <= 180 && ft_atof(data->infos[3]) >= 0)
		obj->fov = ft_atof(data->infos[3]);
	else
	{
		printf("CAMERA FOV error\n");
		exit(3);
	}
	cam_w_h_flen(obj, data);
	cam_point_and_normal(obj, data);
	vectors = cam_up_and_dir(obj);
	cam_transform(obj, vectors);
	data->camera = obj;
}

void	parse_light(t_objects *obj_list, t_data *data, int i)
{
	t_light		*obj;

	obj = malloc(sizeof(t_light));
	obj_list[i].object = obj;
	if (!ft_isfloat(data->infos[2])
		&& ft_atof(data->infos[2]) <= 1 && ft_atof(data->infos[2]) >= 0)
			((t_light *)obj)->ratio = ft_atof(data->infos[2]);
	else
	{
		printf("isfloat error light intensity\n");
		exit(22);
	}
	set_light_point(obj, data);
	create_light_color(data, obj, i, obj_list);
	data->light = obj;
}

void	parse_amb_light(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;

	obj = malloc(sizeof(t_amb_light));
	obj_list[i].object = obj;
	if (!ft_isfloat(data->infos[1])
		&& ft_atof(data->infos[1]) <= 1 && ft_atof(data->infos[1]) >= 0)
			((t_amb_light *)obj)->ratio = ft_atof(data->infos[1]);
	else
	{
		printf("isfloat error amb light intensity\n");
		exit(22);
	}
	create_amblight_color(data, obj, i, obj_list);
	data->amb_light = obj;
}

void	parse_cylindre(t_objects *obj_list, t_data *data, int i)
{
	t_cylindre		*obj;
	t_parse_vectors	vectors;

	obj = malloc(sizeof(t_cylindre));
	cyl_dim_point_normal(data, obj_list, obj, i);
	vectors = cyl_up_and_dir(obj);
	cyl_transform(obj, vectors);
	create_cylinder_color(data, obj, i, obj_list);
	// printf("***************\n");
	// kc_matrix_print(obj->trans);
	// printf("***************\n\n");
	// printf("***************\n");
	// kc_matrix_print(obj->trans_inv);
	// printf("***************\n\n");
	data->obj_size++;
}

void	parse_sphere(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**point;
	t_vector	p;

	obj = malloc(sizeof(t_sphere));
	obj_list[i].object = obj;
	if (!ft_isfloat(data->infos[2]))
		((t_sphere *)obj)->diameter = ft_atof(data->infos[2]) / 2.0f;
	point = ft_split(data->infos[1], ',');
	p = create_vector(ft_atof(point[0]), ft_atof(point[1]), ft_atof(point[2]));
	if (!ft_isfloat(point[0]) && !ft_isfloat(point[1]) && !ft_isfloat(point[2]))
		((t_sphere *)obj)->point = p;
	else
	{
		printf("SPHERE POINT ERROR!\n");
		free_split(point);
		exit(22);
	}
	free_split(point);
	create_sphere_color(data, obj, i, obj_list);
	data->obj_size++;
}
