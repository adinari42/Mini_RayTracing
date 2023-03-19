/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:39:34 by adinari           #+#    #+#             */
/*   Updated: 2023/03/18 20:01:30 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "matrix.h"

void	parse_info(t_objects *obj_list, t_data *data, int i)
{
	if (!check_info_size(obj_list, i, data))
		free_and_exit(obj_list, data);
	else if (obj_list[i].type == AMB_LIGHT)
		parse_amb_light(obj_list, data, i);
	else if (obj_list[i].type == LIGHT)
		parse_light(obj_list, data, i);
	else if (obj_list[i].type == CAMERA)
		parse_camera(obj_list, data, i);
	else if (obj_list[i].type == CYLINDRE)
		parse_cylindre(obj_list, data, i);
	else if (obj_list[i].type == SPHERE)
		parse_sphere(obj_list, data, i);
	else if (obj_list[i].type == PLANE)
		parse_plane(obj_list, data, i);
}

void	type_error(t_objects *obj_list, t_data *data, int i)
{
	if (obj_list[i].type == NONE)
	{
		write(2, "Error: incorrect information\n", 30);
		int j = 0;
		while(j <= i)
		{
			printf("freeing objlist[%d]=%s\n", j, obj_list[j].str);
			printf("obj_list[%d] adress %p\n", j, &obj_list[j]);
			free(obj_list[j].str);
			j++;
		}
		free(obj_list);
		printf("freeing data.infos:%s\n", data->infos[0]);
		free_split(data->infos);
		free(data->img);
		free(data);
	
	
		// // free_split(data->infos);
		// free_obj_list(obj_list, data);
		// free(data->img);
		// free(data);
		// system("leaks MiniRT");
		exit(1);
	}
}

void	save_info(t_objects *obj_list, t_data *data)
{
	int	i;

	i = 0;
	data->fd = open("scene.rt", O_RDONLY);
	while (i < data->list_size)
	{
		obj_list[i].str = get_next_line(data->fd);
		if (obj_list[i].str && first_occur(obj_list[i].str))
		{
			printf("<<<< i = %d<<<<\n", i);
			system("leaks MiniRT");
			if (i < data->list_size - 1)
				ft_strlcpy(obj_list[i].str,
					obj_list[i].str, ft_strlen(obj_list[i].str));
			data->infos = ft_split(obj_list[i].str, ' ');
			obj_list[i].type = is_obj(data->infos[0]);
			type_error(obj_list, data, i);
			parse_info(obj_list, data, i);
			free_split(data->infos);
			i++;
		}
		else
			free(obj_list[i].str);
	}
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

int	main(int argc, char **argv)
{
	t_data		*data;
	t_objects	*obj_list;
	t_ray		ray;
	t_vector	d;

	if (argc < 2)
	{
		write(2, "Error: no parameter found\nusage: ./MiniRT scene.rt\n", 52);
		exit(1);
	}
	d.x = 1;
	d.y = 1;
	d.z = 1;
	data = malloc(sizeof(t_data));
	printf("data adress: %p\n", data);
	init_data(data, argv);
	obj_list = malloc((data->list_size) * sizeof(t_objects));
	//0 leaks here
	// system("leaks MiniRT");
	printf("obj_list adress: %p\n", obj_list);
	save_info(obj_list, data);
	data->objs = obj_list;
	ray = create_ray(data->camera->point, d);
	ray.v = transform(data->camera->trans, ray.v, 0);
	free_obj_list(obj_list, data);
	trace(data);
	make_pic(*data);
	free(obj_list);
	free(data);
}
/*
main
data = malloc(sizeof(t_data));
obj_list = malloc((data->list_size) * sizeof(t_objects));

init_data
data->img = ft_calloc(data->h * data->w, sizeof(t_color));

*/