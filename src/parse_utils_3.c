/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:17:23 by adinari           #+#    #+#             */
/*   Updated: 2023/03/08 18:37:07 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cam_w_h_flen(t_camera *obj, t_data *data)
{
	obj->w = 1;
	obj->h = (double)data->h / (double)data->w;
	obj->flen = 0.5 / tan(obj->fov / 360 * PI);
}

void	cam_point_and_normal(t_camera *obj, t_data *data)
{
	char			**normal;
	char			**point;

	point = ft_split(data->infos[1], ',');
	obj->point.x = ft_atof(point[0]);
	obj->point.y = ft_atof(point[1]);
	obj->point.z = ft_atof(point[2]);
	free_split(point);
	normal = ft_split(data->infos[2], ',');
	obj->normal.x = ft_atof(normal[0]);
	obj->normal.y = ft_atof(normal[1]);
	obj->normal.z = ft_atof(normal[2]);
	obj->normal = vector_normalize(obj->normal);
	free_split(normal);
}

t_parse_vectors	cam_up_and_dir(t_camera *obj)
{
	t_parse_vectors	vectors;

	vectors.up.x = 0;
	vectors.up.y = 1;
	vectors.up.z = 0;
	vectors.dir_x = vector_cross_product(vectors.up, obj->normal);
	vectors.dir_x = vector_normalize(vectors.dir_x);
	vectors.dir_y = vector_cross_product(obj->normal, vectors.dir_x);
	vectors.dir_y = vector_normalize(vectors.dir_y);
	return (vectors);
}

void	cam_transform(t_camera *obj, t_parse_vectors vectors)
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

void	set_light_point(t_light *obj, t_data *data)
{
	char	**point;

	point = ft_split(data->infos[1], ',');
	((t_light *)obj)->point.x = ft_atof(point[0]);
	((t_light *)obj)->point.y = ft_atof(point[1]);
	((t_light *)obj)->point.z = ft_atof(point[2]);
	free_split(point);
}
