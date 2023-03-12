/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:22:09 by adinari           #+#    #+#             */
/*   Updated: 2023/03/08 18:25:28 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cyl_dim_point_normal(t_data *data,
	t_objects *obj_list, t_cylindre *obj, int i)
{
	char			**point;

	obj_list[i].object = obj;
	obj->height = ft_atof(data->infos[4]);
	obj->diameter = ft_atof(data->infos[3]);
	point = ft_split(data->infos[1], ',');
	obj->point.x = ft_atof(point[0]);
	obj->point.y = ft_atof(point[1]);
	obj->point.z = ft_atof(point[2]);
	free_split(point);
	point = ft_split(data->infos[2], ',');
	obj->normal.x = ft_atof(point[0]);
	obj->normal.y = ft_atof(point[1]);
	obj->normal.z = ft_atof(point[2]);
	free_split(point);
}

t_parse_vectors	cyl_up_and_dir(t_cylindre *obj)
{
	t_parse_vectors	vectors;

	if (obj->normal.x == 0 && obj->normal.y == 1 && obj->normal.z == 0)
	{
		vectors.up.x = 0;
		vectors.up.y = 0;
		vectors.up.z = -1;
	}
	else
	{
		vectors.up.x = 0;
		vectors.up.y = 1;
		vectors.up.z = 0;
	}
	obj->normal = vector_normalize(obj->normal);
	vectors.dir_x = vector_cross_product(vectors.up, obj->normal);
	vectors.dir_x = vector_normalize(vectors.dir_x);
	vectors.dir_y = vector_cross_product(obj->normal, vectors.dir_x);
	vectors.dir_y = vector_normalize(vectors.dir_y);
	return (vectors);
}

void	cyl_transform(t_cylindre *obj, t_parse_vectors vectors)
{
	obj->trans = kc_matrix_init(4, 4);
	obj->trans.elements[0] = vectors.dir_x.x;
	obj->trans.elements[1] = vectors.dir_x.y;
	obj->trans.elements[2] = vectors.dir_x.z;
	obj->trans.elements[3] = obj->point.x;
	obj->trans.elements[4] = vectors.dir_y.x;
	obj->trans.elements[5] = vectors.dir_y.y;
	obj->trans.elements[6] = vectors.dir_y.z;
	obj->trans.elements[7] = obj->point.y;
	obj->trans.elements[8] = obj->normal.x;
	obj->trans.elements[9] = obj->normal.y;
	obj->trans.elements[10] = obj->normal.z;
	obj->trans.elements[11] = obj->point.z;
	obj->trans.elements[12] = 0;
	obj->trans.elements[13] = 0;
	obj->trans.elements[14] = 0;
	obj->trans.elements[15] = 1;
	obj->trans_inv = kc_matrix_inverse(obj->trans);
}

void	plane_point_and_normal(t_plane *obj, t_data *data)
{
	char	**point;

	point = ft_split(data->infos[1], ',');
	obj->point.x = ft_atof(point[0]);
	obj->point.y = ft_atof(point[1]);
	obj->point.z = ft_atof(point[2]);
	free_split(point);
	point = ft_split(data->infos[2], ',');
	obj->normal.x = ft_atof(point[0]);
	obj->normal.y = ft_atof(point[1]);
	obj->normal.z = ft_atof(point[2]);
	obj->normal = vector_normalize(obj->normal);
	vector_print("MY PLANE => ", obj->normal);
	free_split(point);
}
