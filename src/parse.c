/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 04:06:34 by adinari           #+#    #+#             */
/*   Updated: 2023/03/27 21:10:28 by miahmadi         ###   ########.fr       */
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
		system("leaks MiniRT");
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
	t_light	*obj;
	char	**colors;
	t_color		c;

	obj = malloc(sizeof(t_light));
	obj_list[i].object = obj;

	if (!ft_isfloat(data->infos[2])
		&& ft_atof(data->infos[2]) <= 1 && ft_atof(data->infos[2]) >= 0)
			((t_light *)obj)->ratio = ft_atof(data->infos[2]);
	else
	{
		printf("isfloat error light intensity\n");
		exit(2);
	}
	set_light_point(obj, data);
	colors = ft_split(data->infos[3], ',');
	c = create_color(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
	if (!ft_isfloat(colors[0]) && !ft_isfloat(colors[1]) && !ft_isfloat(colors[2])
		&& c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = create_color(ft_atoi(colors[0]),
				ft_atoi(colors[1]), ft_atoi(colors[2]));
		((t_light *)obj)->color = c;
	}
	else
	{
		printf("error: light colors incorrect!");
		free_split(colors);
		exit(3);
	}
	data->light = obj;
	free_split(colors);
}

void	parse_amb_light(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	t_color		c;

	obj = malloc(sizeof(t_amb_light));
	obj_list[i].object = obj;
	if (!ft_isfloat(data->infos[1])
		&& ft_atof(data->infos[1]) <= 1 && ft_atof(data->infos[1]) >= 0)
			((t_amb_light *)obj)->ratio = ft_atof(data->infos[1]);
	else
	{
		printf("isfloat error amb light intensity\n");
		exit(1);
	}
	colors = ft_split(data->infos[2], ',');
	c = create_color(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
	if (!ft_isfloat(colors[0]) && !ft_isfloat(colors[1]) && !ft_isfloat(colors[2])
		&& c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = create_color(ft_atoi(colors[0]),
				ft_atoi(colors[1]), ft_atoi(colors[2]));
		((t_amb_light *)obj)->color = c;
	}
	else
	{
		printf("error: amb light colors incorrect!");
		free_split(colors);
		exit(2);
	}
	data->amb_light = obj;
	free_split(colors);
}

void	parse_cylindre(t_objects *obj_list, t_data *data, int i)
{
	t_cylindre		*obj;
	char			**colors;
	t_parse_vectors	vectors;
	t_color 		c;

	obj = malloc(sizeof(t_cylindre));
	cyl_dim_point_normal(data, obj_list, obj, i);
	vectors = cyl_up_and_dir(obj);
	cyl_transform(obj, vectors);
	colors = ft_split(data->infos[5], ',');
	c = create_color(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
	if (!ft_isfloat(colors[0]) && !ft_isfloat(colors[1]) && !ft_isfloat(colors[2])
		&& c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = c;
		((t_cylindre *)obj)->color = c;
	}
	else
	{
		printf("CYLINDER COLORS INCORRECT!");
		free_split(colors);
		exit(5);
	}
	free_split(colors);
	data->obj_size++;
}

void	parse_sphere(t_objects *obj_list, t_data *data, int i)
{
	void		*obj;
	char		**colors;
	char		**point;
	t_vector 	p;

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
		printf("SPHERE POINT ERROR!");
		free_split(point);
		exit(2);
	}
	free_split(point);
	colors = ft_split(data->infos[3], ',');
	t_color c = create_color(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
	if (c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = c;
		((t_sphere *)obj)->color = c;
	}
	else
	{
		printf("SPHERE COLORS ERROR!");
		free_split(colors);
		exit(3);
	}
	free_split(colors);
	data->obj_size++;
}
