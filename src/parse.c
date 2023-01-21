/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 04:06:34 by adinari           #+#    #+#             */
/*   Updated: 2023/01/21 15:42:51 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(t_objects *obj_list, t_data *data, int i)
{
	t_camera	*obj;
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
	obj->flen = atan(obj->fov / 360 * PI) * 0.5;
	point = ft_split(data->infos[1], ',');
	obj->point.x= ft_atof(point[0]);
	obj->point.y = ft_atof(point[1]);
	obj->point.z = ft_atof(point[2]);
	free_split(point);
	normal = ft_split(data->infos[2], ',');
	obj->normal.x= ft_atof(normal[0]);
	obj->normal.y = ft_atof(normal[1]);
	obj->normal.z = ft_atof(normal[2]);
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
	void		*obj;
	char		**colors;
	char		**point;


	obj = malloc(sizeof(t_cylindre)); 
	obj_list[i].object = obj;
	((t_cylindre *)obj)->height = ft_atof(data->infos[4]);
	((t_cylindre *)obj)->diameter = ft_atof(data->infos[3]);
	point = ft_split(data->infos[1], ',');
		((t_cylindre *)obj)->point.x= ft_atof(point[0]);
		((t_cylindre *)obj)->point.y = ft_atof(point[1]);
		((t_cylindre *)obj)->point.z = ft_atof(point[2]);
	free_split(point);
	point = ft_split(data->infos[2], ',');
	((t_cylindre *)obj)->normal.x= ft_atof(point[0]);
	((t_cylindre *)obj)->normal.y = ft_atof(point[1]);
	((t_cylindre *)obj)->normal.z = ft_atof(point[2]);
	free_split(point);
	colors = ft_split(data->infos[5], ',');
	obj_list[i].color = create_color(ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_cylindre *)obj)->color.red = ft_atoi(colors[0]);
		((t_cylindre *)obj)->color.green = ft_atoi(colors[1]);
		((t_cylindre *)obj)->color.blue = ft_atoi(colors[2]);
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