/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 04:06:34 by adinari           #+#    #+#             */
/*   Updated: 2023/01/18 13:33:50 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**point;
	char		**normal;
	// (void)data;

	obj = malloc(sizeof(t_camera)); 
	obj_list[i].object = obj;
	// /*********-fov-**********/
	if (ft_isfloat(data->infos[3]))
		((t_camera *)obj)->fov = ft_atof(data->infos[3]);
	else
	{
		printf("isfloat error\n");
		exit(1);
	}
	/*********-point: [0;180]-**********/
	point = ft_split(data->infos[1], ',');
	// if (ft_isfloat(point[0]) && ft_isfloat(point[1]) && ft_isfloat(point[2]))//need to test if the elements are floats
	// {
		((t_camera *)obj)->point.x= ft_atof(point[0]);
		((t_camera *)obj)->point.y = ft_atof(point[1]);
		((t_camera *)obj)->point.z = ft_atof(point[2]);
	// }
	//else
	//	error
	free_split(point);//<< is causing segfault , need another function for freeing char **
	/*********-normal[-1;1]-**********/
	normal = ft_split(data->infos[2], ',');
	// if (ft_isfloat(normal[0]) && ft_isfloat(normal[1]) && ft_isfloat(normal[2]))//need to test if the elements are floats
	// {
		((t_camera *)obj)->normal.x= ft_atof(normal[0]);
		((t_camera *)obj)->normal.y = ft_atof(normal[1]);
		((t_camera *)obj)->normal.z = ft_atof(normal[2]);
	// }
	//else
	//	error
	free_split(normal);//<< is causing segfault , need another function for freeing char **
}

void	parse_light(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;


	obj = malloc(sizeof(t_light)); 
	obj_list[i].object = obj;
	/*********-ratio-**********/
	if (ft_isfloat(data->infos[2]))
		((t_light *)obj)->ratio = ft_atof(data->infos[2]);
	else
	{
		printf("isfloat error\n");
		exit(1);
	}
	/*********-point-**********/
	point = ft_split(data->infos[1], ',');
	// if (ft_isfloat(point[0]) && ft_isfloat(point[1]) && ft_isfloat(point[2]))//need to test if the elements are floats
	// {
		((t_light *)obj)->point.x= ft_atof(point[0]);
		((t_light *)obj)->point.y = ft_atof(point[1]);
		((t_light *)obj)->point.z = ft_atof(point[2]);
	// }
	//else
	//	error
	free_split(point);//<< is causing segfault , need another function for freeing char **
	/***********-color-***********/
	colors = ft_split(data->infos[3], ',');
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_light *)obj)->color.red = ft_atoi(colors[0]);
		((t_light *)obj)->color.green = ft_atoi(colors[1]);
		((t_light *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);//<< is causing segfault , need another function for freeing char **
}

void	parse_amb_light(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;

	obj = malloc(sizeof(t_amb_light)); 
	obj_list[i].object = obj;
	// if (ft_isfloat(data->infos[1]))
		((t_amb_light *)obj)->ratio = ft_atof(data->infos[1]);
	// else
	// {
	// 	printf("isfloat error\n");
	// 	exit(1);
	// }
	colors = ft_split(data->infos[2], ',');
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_amb_light *)obj)->color.red = ft_atoi(colors[0]);
		((t_amb_light *)obj)->color.green = ft_atoi(colors[1]);
		((t_amb_light *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);//<< is causing segfault , need another function for freeing char **
}

void	parse_cylindre(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;


	obj = malloc(sizeof(t_cylindre)); 
	obj_list[i].object = obj;
	/*********-height-**********/
	// if (ft_isfloat(data->infos[4]))
		((t_cylindre *)obj)->height = ft_atof(data->infos[4]);
	// else
	// {
	// 	printf("isfloat error1\n");
	// 	exit(1);
	// }
	/*********-diameter-**********/
	// if (ft_isfloat(data->infos[3]))
		((t_cylindre *)obj)->diameter = ft_atof(data->infos[3]);
	// else
	// {
	// 	printf("isfloat error2\n");
	// 	exit(1);
	// }
	/*********-point-**********/
	point = ft_split(data->infos[1], ',');
	// if (ft_isfloat(point[0]) && ft_isfloat(point[1]) && ft_isfloat(point[2]))//need to test if the elements are floats
	// {
		((t_cylindre *)obj)->point.x= ft_atof(point[0]);
		((t_cylindre *)obj)->point.y = ft_atof(point[1]);
		((t_cylindre *)obj)->point.z = ft_atof(point[2]);
	// }
	//else
	//	error
	free_split(point);//<< is causing segfault , need another function for freeing char **
	/*********-normal-**********/
	point = ft_split(data->infos[2], ',');
	// if (ft_isfloat(point[0]) && ft_isfloat(point[1]) && ft_isfloat(point[2]))//need to test if the elements are floats
	// {
		((t_cylindre *)obj)->normal.x= ft_atof(point[0]);
		((t_cylindre *)obj)->normal.y = ft_atof(point[1]);
		((t_cylindre *)obj)->normal.z = ft_atof(point[2]);
	// }
	//else
	//	error
	free_split(point);//<< is causing segfault , need another function for freeing char **
	/***********-color-***********/
	colors = ft_split(data->infos[5], ',');
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_cylindre *)obj)->color.red = ft_atoi(colors[0]);
		((t_cylindre *)obj)->color.green = ft_atoi(colors[1]);
		((t_cylindre *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);//<< is causing segfault , need another function for freeing char **
}

void	parse_sphere(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;


	obj = malloc(sizeof(t_sphere)); 
	obj_list[i].object = obj;
	/*********-diameter-**********/
	// if (ft_isfloat(data->infos[3]))
		((t_sphere *)obj)->diameter = ft_atof(data->infos[2]);
	// else
	// {
	// 	printf("isfloat error2\n");
	// 	exit(1);
	// }
	/*********-point-**********/
	point = ft_split(data->infos[1], ',');
	// if (ft_isfloat(point[0]) && ft_isfloat(point[1]) && ft_isfloat(point[2]))//need to test if the elements are floats
	// {
		((t_sphere *)obj)->point.x= ft_atof(point[0]);
		((t_sphere *)obj)->point.y = ft_atof(point[1]);
		((t_sphere *)obj)->point.z = ft_atof(point[2]);
	// }
	//else
	//	error
	free_split(point);//<< is causing segfault , need another function for freeing char **
	/***********-color-***********/
	colors = ft_split(data->infos[3], ',');
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_sphere *)obj)->color.red = ft_atoi(colors[0]);
		((t_sphere *)obj)->color.green = ft_atoi(colors[1]);
		((t_sphere *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);//<< is causing segfault , need another function for freeing char **
}
void	parse_plane(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;

	obj = malloc(sizeof(t_plane));
	obj_list[i].object = obj;
	/*********-point-**********/
	point = ft_split(data->infos[1], ',');
	// if (ft_isfloat(point[0]) && ft_isfloat(point[1]) && ft_isfloat(point[2]))//need to test if the elements are floats
	// {
		((t_plane *)obj)->point.x= ft_atof(point[0]);
		((t_plane *)obj)->point.y = ft_atof(point[1]);
		((t_plane *)obj)->point.z = ft_atof(point[2]);
	// }
	//else
	//	error
	free_split(point);//<< is causing segfault , need another function for freeing char **
	/*********-normal-**********/
	point = ft_split(data->infos[2], ',');
	// if (ft_isfloat(point[0]) && ft_isfloat(point[1]) && ft_isfloat(point[2]))//need to test if the elements are floats
	// {
		((t_plane *)obj)->normal.x= ft_atof(point[0]);
		((t_plane *)obj)->normal.y = ft_atof(point[1]);
		((t_plane *)obj)->normal.z = ft_atof(point[2]);
	// }
	//else
	//	error
	free_split(point);//<< is causing segfault , need another function for freeing char **
	/***********-color-***********/
	colors = ft_split(data->infos[3], ',');
	if (str_isdigit(colors[0]) && str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_plane *)obj)->color.red = ft_atoi(colors[0]);
		((t_plane *)obj)->color.green = ft_atoi(colors[1]);
		((t_plane *)obj)->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);//<< is causing segfault , need another function for freeing char **
}