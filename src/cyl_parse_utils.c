/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 07:33:47 by adinari           #+#    #+#             */
/*   Updated: 2023/04/28 21:06:42 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cyl_height_and_diameter(t_data *data, t_cylindre *obj)
{
	if (!ft_isfloat(data->infos[4]))
		obj->height = ft_atof(data->infos[4]);
	else
	{
		printf("CYLINDER HEIGHT ERROR!\n");
		exit(22);
	}
	if (!ft_isfloat(data->infos[3]))
		obj->diameter = ft_atof(data->infos[3]) / 2.0f;
	else
	{
		printf("CYLINDER DIAMETER ERROR!\n");
		exit(22);
	}
}

void	cyl_normal(t_data *data, t_cylindre *obj)
{
	char		**normal;

	normal = ft_split(data->infos[2], ',');
	if (!ft_isfloat(normal[0]) && !ft_isfloat(normal[1])
		&& !ft_isfloat(normal[2]) && ft_atof(normal[0]) <= 1
		&& ft_atof(normal[1]) <= 1 && ft_atof(normal[2]) <= 1
		&& ft_atof(normal[0]) >= -1 && ft_atof(normal[1]) >= -1
		&& ft_atof(normal[2]) >= -1)
	{
		obj->normal.x = ft_atof(normal[0]);
		obj->normal.y = ft_atof(normal[1]);
		obj->normal.z = ft_atof(normal[2]);
	}
	else
	{
		printf("CYLINDER NORMAL ERROR!\n");
		free_split(normal);
		exit(22);
	}
	free_split(normal);
}

void	cyl_dim_point_normal(t_data *data,
			t_objects *obj_list, t_cylindre *obj, int i)
{
	char		**point;

	obj_list[i].object = obj;
	cyl_height_and_diameter(data, obj);
	point = ft_split(data->infos[1], ',');
	if (!ft_isfloat(point[0]) && !ft_isfloat(point[1]) && !ft_isfloat(point[2]))
		obj->point = create_vector(ft_atof(point[0]),
				ft_atof(point[1]), ft_atof(point[2]));
	else
	{
		printf("CYLINDER POINT ERROR!\n");
		free_split(point);
		exit(22);
	}
	free_split(point);
	cyl_normal(data, obj);
}
