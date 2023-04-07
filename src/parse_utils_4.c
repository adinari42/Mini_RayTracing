/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:22:09 by adinari           #+#    #+#             */
/*   Updated: 2023/04/04 08:35:23 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_vectors	cyl_up_and_dir(t_cylindre *obj)
{
	t_parse_vectors	vectors;

	obj->normal = vector_normalize(obj->normal);
	obj->normal.y *= -1;
	if (obj->normal.x == 0 && obj->normal.z == 0)
	{
		vectors.dir_x = create_vector(1, 0, 0);
		vectors.dir_y = vector_cross_product(obj->normal, vectors.dir_x);
		vectors.dir_y = vector_scale(vector_normalize(vectors.dir_y), -1);
	}
	else
	{
		vectors.up = create_vector(0, 1, 0);
		vectors.dir_x = vector_cross_product(obj->normal, vectors.up);
		vectors.dir_x = vector_normalize(vectors.dir_x);
		vectors.dir_y = vector_cross_product(vectors.dir_x, obj->normal);
		vectors.dir_y = vector_scale(vector_normalize(vectors.dir_y), -1);
	}
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

void	create_plane_normal(t_plane *obj, t_data *data)
{
	char	**normal;

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
		obj->normal = vector_normalize(obj->normal);
	}
	else
	{
		printf("PLANE NORMAL ERROR!");
		free_split(normal);
		exit(2);
	}
	free_split(normal);
}

void	plane_point_and_normal(t_plane *obj, t_data *data)
{
	char	**point;

	point = ft_split(data->infos[1], ',');
	if (!ft_isfloat(point[0]) && !ft_isfloat(point[1]) && !ft_isfloat(point[2]))
	{
		obj->point.x = ft_atof(point[0]);
		obj->point.y = ft_atof(point[1]);
		obj->point.z = ft_atof(point[2]);
	}
	else
	{
		printf("PLANE POINT ERROR!\n");
		free_split(point);
		exit(22);
	}
	free_split(point);
	create_plane_normal(obj, data);
}
