/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 03:44:43 by adinari           #+#    #+#             */
/*   Updated: 2023/04/04 09:30:52 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_sphere_color(t_data *data,
		void *obj, int i, t_objects *obj_list)
{
	t_color		c;
	char		**colors;

	colors = ft_split(data->infos[3], ',');
	if (!ft_isfloat(colors[0])
		&& !ft_isfloat(colors[1]) && !ft_isfloat(colors[2]))
	{
		c = create_color(ft_atof(colors[0]),
			ft_atof(colors[1]), ft_atof(colors[2]));
		if (c.red <= 255 && c.blue <= 255 && c.green <= 255
			&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
		{
			obj_list[i].color = c;
			((t_sphere *)obj)->color = c;
			free_split(colors);
			return ;
		}
	}
	printf("SPHERE COLORS ERROR!\n");
	free_split(colors);
	exit(22);
}

void	create_plane_color(t_data *data,
		t_plane *obj, int i, t_objects *obj_list)
{
	t_color		c;
	char		**colors;

	colors = ft_split(data->infos[3], ',');
	if (!ft_isfloat(colors[0])
		&& !ft_isfloat(colors[1]) && !ft_isfloat(colors[2]))
	{
		c = create_color(ft_atof(colors[0]),
			ft_atof(colors[1]), ft_atof(colors[2]));
		if (c.red <= 255 && c.blue <= 255 && c.green <= 255
			&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
		{
			obj_list[i].color = c;
			((t_plane *)obj)->color = c;
			free_split(colors);
			return ;
		}
	}
	printf("PLANE COLORS ERROR!\n");
	free(obj);
	free_split(colors);
	exit(22);
}

void	set_light_point(t_light *obj, t_data *data)
{
	char		**point;
	t_vector	p;

	point = ft_split(data->infos[1], ',');
	p = create_vector(ft_atof(point[0]), ft_atof(point[1]), ft_atof(point[2]));
	if (!ft_isfloat(point[0]) && !ft_isfloat(point[1]) && !ft_isfloat(point[2]))
		((t_light *)obj)->point = p;
	else
	{
		printf("LIGHT POINT ERROR!\n");
		free_split(point);
		exit(22);
	}
	free_split(point);
}
