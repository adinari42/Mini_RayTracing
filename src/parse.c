/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 04:06:34 by adinari           #+#    #+#             */
/*   Updated: 2023/01/31 18:18:41 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(t_objects *obj_list, t_data *data, int i)
{
	t_camera	*obj;
	t_vector	up;
	t_vector	dirX;
	t_vector	dirY;
	char		**point;
	char		**normal;

	obj = malloc(sizeof(t_camera)); 
	obj_list[i].object = obj;
	if (ft_isfloat(data->infos[3]))
		obj->fov = ft_atof(data->infos[3]);
	else
	{
		printf("isfloat error\n");
		exit(1);
	}
	obj->w = 1;
	obj->h = (double)data->h / (double)data->w;
	obj->flen = 0.5 / tan(obj->fov / 360 * PI);
	point = ft_split(data->infos[1], ',');
	obj->point.x= ft_atof(point[0]);
	obj->point.y = ft_atof(point[1]);
	obj->point.z = ft_atof(point[2]);
	free_split(point);
	normal = ft_split(data->infos[2], ',');
	obj->normal.x= ft_atof(normal[0]);
	obj->normal.y = ft_atof(normal[1]);
	obj->normal.z = ft_atof(normal[2]);
	up.x = 0;
	up.y = 1;
	up.z = 0;
	obj->normal = vectorNormalize(obj->normal);
	dirX = vectorCrossProduct(up, obj->normal);
	dirX = vectorNormalize(dirX);
	dirY = vectorCrossProduct(obj->normal, dirX);
	dirY = vectorNormalize(dirY);
	obj->trans = kc_matrix_init(4, 4);
	obj->trans.elements[0] = dirX.x;
	obj->trans.elements[1] = dirX.y;
	obj->trans.elements[2] = dirX.z;
	obj->trans.elements[3] = obj->point.x;
	obj->trans.elements[4] = dirY.x;
	obj->trans.elements[5] = dirY.y;
	obj->trans.elements[6] = dirY.z;
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
	printf("\nTransform: \n");
	kc_matrix_print(obj->trans);
	printf("\nTransform Inverse: \n");
	kc_matrix_print(obj->trans_inv);
	data->camera = obj;
	free_split(normal);
}

void	parse_light(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;


	obj = malloc(sizeof(t_light)); 
	obj_list[i].object = obj;
	if (ft_isfloat(data->infos[2]))
		((t_light *)obj)->ratio = ft_atof(data->infos[2]);
	else
	{
		printf("isfloat error\n");
		exit(1);
	}
	point = ft_split(data->infos[1], ',');
	((t_light *)obj)->point.x= ft_atof(point[0]);
	((t_light *)obj)->point.y = ft_atof(point[1]);
	((t_light *)obj)->point.z = ft_atof(point[2]);
	free_split(point);
	colors = ft_split(data->infos[3], ',');
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_light *)obj)->color.red = ft_atoi(colors[0]);
		((t_light *)obj)->color.green = ft_atoi(colors[1]);
		((t_light *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);
}

void	parse_amb_light(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;

	obj = malloc(sizeof(t_amb_light)); 
	obj_list[i].object = obj;
	((t_amb_light *)obj)->ratio = ft_atof(data->infos[1]);
	colors = ft_split(data->infos[2], ',');
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_amb_light *)obj)->color.red = ft_atoi(colors[0]);
		((t_amb_light *)obj)->color.green = ft_atoi(colors[1]);
		((t_amb_light *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);
}

void	parse_cylindre(t_objects *obj_list, t_data *data, int i)
{
	t_cylindre	*obj;
	char		**colors;
	char		**point;
	t_vector	dirX;
	t_vector	dirY;
	t_vector	up;


	obj = malloc(sizeof(t_cylindre)); 
	obj_list[i].object = obj;
	obj->height = ft_atof(data->infos[4]);
	obj->diameter = ft_atof(data->infos[3]);
	point = ft_split(data->infos[1], ',');
	obj->point.x= ft_atof(point[0]);
	obj->point.y = ft_atof(point[1]);
	obj->point.z = ft_atof(point[2]);
	free_split(point);
	point = ft_split(data->infos[2], ',');
	obj->normal.x= ft_atof(point[0]);
	obj->normal.y = ft_atof(point[1]);
	obj->normal.z = ft_atof(point[2]);
	if (obj->normal.x == 0 && obj->normal.y == 1 && obj->normal.z == 0)
	{
		up.x = 1;
		up.y = 0;
		up.z = 0;
	}
	else
	{
		up.x = 0;
		up.y = 1;
		up.z = 0;
	}
	obj->normal = vectorNormalize(obj->normal);
	dirX = vectorCrossProduct(up, obj->normal);
	dirX = vectorNormalize(dirX);
	dirY = vectorCrossProduct(obj->normal, dirX);
	dirY = vectorNormalize(dirY);
	obj->trans = kc_matrix_init(4, 4);
	obj->trans.elements[0] = dirX.x;
	obj->trans.elements[1] = dirX.y;
	obj->trans.elements[2] = dirX.z;
	obj->trans.elements[3] = 0;
	obj->trans.elements[4] = dirY.x;
	obj->trans.elements[5] = dirY.y;
	obj->trans.elements[6] = dirY.z;
	obj->trans.elements[7] = 0;
	obj->trans.elements[8] = obj->normal.x;
	obj->trans.elements[9] = obj->normal.y;
	obj->trans.elements[10] = obj->normal.z;
	obj->trans.elements[11] = 0;
	obj->trans.elements[12] = obj->point.x;
	obj->trans.elements[13] = obj->point.y;
	obj->trans.elements[14] = obj->point.z;
	obj->trans.elements[15] = 1;
	obj->trans_inv = kc_matrix_inverse(obj->trans);
	printf("C TRANS\n");
	kc_matrix_print(obj->trans);
	printf("C TRANS INV\n");
	kc_matrix_print(obj->trans_inv);
	free_split(point);
	colors = ft_split(data->infos[5], ',');
	obj_list[i].color = create_color(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		obj->color.red = ft_atoi(colors[0]);
		obj->color.green = ft_atoi(colors[1]);
		obj->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);
	data->obj_size++;
}

void	parse_sphere(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;


	obj = malloc(sizeof(t_sphere)); 
	obj_list[i].object = obj;
	((t_sphere *)obj)->diameter = ft_atof(data->infos[2]);
	point = ft_split(data->infos[1], ',');
	((t_sphere *)obj)->point.x= ft_atof(point[0]);
	((t_sphere *)obj)->point.y = ft_atof(point[1]);
	((t_sphere *)obj)->point.z = ft_atof(point[2]);
	free_split(point);
	colors = ft_split(data->infos[3], ',');
	obj_list[i].color = create_color(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_sphere *)obj)->color.red = ft_atoi(colors[0]);
		((t_sphere *)obj)->color.green = ft_atoi(colors[1]);
		((t_sphere *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);
	data->obj_size++;
}
void	parse_plane(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;

	obj = malloc(sizeof(t_plane));
	obj_list[i].object = obj;
	point = ft_split(data->infos[1], ',');
	((t_plane *)obj)->point.x= ft_atof(point[0]);
	((t_plane *)obj)->point.y = ft_atof(point[1]);
	((t_plane *)obj)->point.z = ft_atof(point[2]);
	free_split(point);
	point = ft_split(data->infos[2], ',');
	((t_plane *)obj)->normal.x= ft_atof(point[0]);
	((t_plane *)obj)->normal.y = ft_atof(point[1]);
	((t_plane *)obj)->normal.z = ft_atof(point[2]);
	free_split(point);
	colors = ft_split(data->infos[3], ',');
	obj_list[i].color = create_color(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_plane *)obj)->color.red = ft_atoi(colors[0]);
		((t_plane *)obj)->color.green = ft_atoi(colors[1]);
		((t_plane *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);
	data->obj_size++;
}