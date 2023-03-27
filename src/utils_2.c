/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:14:31 by adinari           #+#    #+#             */
/*   Updated: 2023/03/27 20:25:50 by miahmadi         ###   ########.fr       */
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

void	main_free(t_objects *obj_list, t_data *data)
{
	int			j;
	t_cylindre	*tmp;

	j = 0;
	while (j < data->list_size)
	{
		if (obj_list[j].type == CAMERA)
			free_camera(data);
		else if (obj_list[j].type == CYLINDRE)
		{
			tmp = obj_list[j].object;
			free(tmp->trans.elements);
			free(tmp->trans_inv.elements);
		}
		else
			else_free(obj_list, j);
		j++;
	}
	free_obj_str(obj_list, data->list_size);
	free(data->img);
	free(data);
}

void	make_pic(t_data data)
{
	FILE	*fp;
	int		i;

	i = 0;
	fp = fopen("image.ppm", "wb");
	fprintf(fp, "P6\n%d %d\n255\n", data.w, data.h);
	while (i < data.w * data.h)
	{
		fputc((int)(data.img[i].red), fp);
		fputc((int)(data.img[i].green), fp);
		fputc((int)(data.img[i].blue), fp);
		i++;
	}
	fclose(fp);
}

void	type_error(t_objects *obj_list, t_data *data, int i)
{
	int			j;
	t_cylindre	*tmp;

	if (obj_list[i].type == NONE)
	{
		j = 0;
		write(2, "Error: incorrect information\n", 30);
		while (j < i)
		{
			if (obj_list[j].type == CAMERA)
				free_camera(data);
			else if (obj_list[j].type == CYLINDRE)
			{
				tmp = obj_list[j].object;
				free(tmp->trans.elements);
				free(tmp->trans_inv.elements);
			}
			else
				else_free(obj_list, j);
			j++;
		}
		free_data(obj_list, data, i);
		exit(1);
	}
}

void	free_obj_str(t_objects *obj_list, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(obj_list[j].str);
		j++;
	}
	free(obj_list);
}

void	free_data(t_objects *obj_list, t_data *data, int i)
{
	free_split(data->infos);
	free(data->img);
	free_obj_str(obj_list, i);
	free(data);
}
