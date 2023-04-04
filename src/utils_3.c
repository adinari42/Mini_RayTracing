/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:06:54 by adinari           #+#    #+#             */
/*   Updated: 2023/03/31 22:14:50 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_camera(t_data *data)
{
	free(data->camera->trans.elements);
	free(data->camera->trans_inv.elements);
	free(data->camera);
}

void	else_free(t_objects *obj_list, int j)
{
	if (obj_list[j].type == LIGHT || obj_list[j].type == AMB_LIGHT)
		free(obj_list[j].object);
	else if (obj_list[j].type != NONE)
		free(obj_list[j].object);
}

void	create_light_color(t_data *data,
		t_light *obj, int i, t_objects *obj_list)
{
	t_color		c;
	char		**colors;

	colors = ft_split(data->infos[3], ',');
	c = create_color(ft_atof(colors[0]),
			ft_atof(colors[1]), ft_atof(colors[2]));
	if (!ft_isfloat(colors[0])
		&& !ft_isfloat(colors[1]) && !ft_isfloat(colors[2])
		&& c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = create_color(ft_atoi(colors[0]),
				ft_atoi(colors[1]), ft_atoi(colors[2]));
		((t_light *)obj)->color = c;
	}
	else
	{
		printf("error: light colors incorrect!\n");
		free_split(colors);
		exit(22);
	}
	free_split(colors);
}

void	create_amblight_color(t_data *data,
		void *obj, int i, t_objects *obj_list)
{
	t_color		c;
	char		**colors;

	colors = ft_split(data->infos[2], ',');
	c = create_color(ft_atof(colors[0]),
			ft_atof(colors[1]), ft_atof(colors[2]));
	if (!ft_isfloat(colors[0])
		&& !ft_isfloat(colors[1]) && !ft_isfloat(colors[2])
		&& c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = create_color(ft_atoi(colors[0]),
				ft_atoi(colors[1]), ft_atoi(colors[2]));
		((t_amb_light *)obj)->color = c;
	}
	else
	{
		printf("error: amb light colors incorrect!\n");
		free_split(colors);
		exit(22);
	}
	free_split(colors);
}

void	create_cylinder_color(t_data *data,
		t_cylindre *obj, int i, t_objects *obj_list)
{
	t_color		c;
	char		**colors;

	colors = ft_split(data->infos[5], ',');
	c = create_color(ft_atof(colors[0]),
			ft_atof(colors[1]), ft_atof(colors[2]));
	if (!ft_isfloat(colors[0])
		&& !ft_isfloat(colors[1]) && !ft_isfloat(colors[2])
		&& c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = create_color(ft_atoi(colors[0]),
				ft_atoi(colors[1]), ft_atoi(colors[2]));
		((t_cylindre *)obj)->color = c;
	}
	else
	{
		printf("CYLINDER COLORS INCORRECT!\n");
		free_split(colors);
		exit(22);
	}
	free_split(colors);
}
