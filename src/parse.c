/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 04:06:34 by adinari           #+#    #+#             */
/*   Updated: 2023/03/13 22:00:24 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(t_objects *obj_list, t_data *data, int i)
{
	t_camera		*obj;
	t_parse_vectors	vectors;

	obj = malloc(sizeof(t_camera));
	obj_list[i].object = obj;
	if (ft_isfloat(data->infos[3]))
		obj->fov = ft_atof(data->infos[3]);
	else
	{
		printf("isfloat error\n");
		exit(1);
	}
	cam_w_h_flen(obj, data);
	cam_point_and_normal(obj, data);
	vectors = cam_up_and_dir(obj);
	cam_transform(obj, vectors);
	data->camera = obj;
}

void	parse_light(t_objects *obj_list, t_data *data, int i)
{
	t_light	*obj;
	char	**colors;

	obj = malloc(sizeof(t_light));
	obj_list[i].object = obj;
	printf("INFO => %s\n", data->infos[2]);
	if (ft_isfloat(data->infos[2]))
		((t_light *)obj)->ratio = ft_atof(data->infos[2]);
	else
	{
		printf("isfloat error light intensity\n");
		exit(1);
	}
	set_light_point(obj, data);
	colors = ft_split(data->infos[3], ',');
	((t_light *)obj)->color.red = ft_atoi(colors[0]);
	((t_light *)obj)->color.green = ft_atoi(colors[1]);
	((t_light *)obj)->color.blue = ft_atoi(colors[2]);
	data->light = obj;
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
	if (str_isdigit(colors[0])
		&& str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		((t_amb_light *)obj)->color.red = ft_atoi(colors[0]);
		((t_amb_light *)obj)->color.green = ft_atoi(colors[1]);
		((t_amb_light *)obj)->color.blue = ft_atoi(colors[2]);
	}
	data->amb_light = obj;
	free_split(colors);
}

void	parse_cylindre(t_objects *obj_list, t_data *data, int i)
{
	t_cylindre		*obj;
	char			**colors;
	t_parse_vectors	vectors;

	obj = malloc(sizeof(t_cylindre));
	cyl_dim_point_normal(data, obj_list, obj, i);
	vectors = cyl_up_and_dir(obj);
	cyl_transform(obj, vectors);
	printf("C TRANS\n");
	kc_matrix_print(obj->trans);
	printf("C TRANS INV\n");
	kc_matrix_print(obj->trans_inv);
	colors = ft_split(data->infos[5], ',');
	obj_list[i].color = create_color(ft_atoi(colors[0]),
			ft_atoi(colors[1]), ft_atoi(colors[2]));
	obj->color = create_color(ft_atoi(colors[0]), ft_atoi(colors[1]),
			ft_atoi(colors[2]));
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
	((t_sphere *)obj)->point.x = ft_atof(point[0]);
	((t_sphere *)obj)->point.y = ft_atof(point[1]);
	((t_sphere *)obj)->point.z = ft_atof(point[2]);
	free_split(point);
	colors = ft_split(data->infos[3], ',');
	obj_list[i].color = create_color(ft_atoi(colors[0]),
			ft_atoi(colors[1]), ft_atoi(colors[2]));
	((t_sphere *)obj)->color.red = ft_atoi(colors[0]);
	((t_sphere *)obj)->color.green = ft_atoi(colors[1]);
	((t_sphere *)obj)->color.blue = ft_atoi(colors[2]);
	free_split(colors);
	data->obj_size++;
}
