/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:39:34 by adinari           #+#    #+#             */
/*   Updated: 2023/02/01 21:11:14 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "matrix.h"

int	is_obj(char *str)
{

	if (!ft_strncmp(str, "A", ft_strlen(str)))
		return (AMB_LIGHT);
	if (!ft_strncmp(str, "C", ft_strlen(str)))
		return (CAMERA);
	if (!ft_strncmp(str, "L", ft_strlen(str)))
		return (LIGHT);
	if (!ft_strncmp(str, "pl", ft_strlen(str)))
		return (PLANE);
	if (!ft_strncmp(str, "sp", ft_strlen(str)))
		return (SPHERE);
	if (!ft_strncmp(str, "cy", ft_strlen(str)))
		return (CYLINDRE);
	return (NONE);
}
int	check_info_size(t_objects *obj_list, int j, t_data *data)
{
	int	i;

	i = 0;
	while (data->infos[i])
		i++;
	// printf ("type = %d, i(credentials number) = %d\n", obj_list[j].type, i);
	if (obj_list[j].type == AMB_LIGHT && i == 3)
		return (1);
	if (obj_list[j].type == LIGHT && i == 4)
		return (1);
	if (obj_list[j].type == CAMERA && i == 4)
		return (1);
	if (obj_list[j].type == CYLINDRE && i == 6)
		return (1);
	if (obj_list[j].type == SPHERE && i == 4)
		return (1);
	if (obj_list[j].type == PLANE && i == 4)
		return (1);
	return (0);
}
void free_and_exit(t_objects *obj_list, t_data *data)
{
	(void)obj_list;
	free_obj_list(obj_list, data);
	free_split(data->infos);
	printf("Parse error: incorrect credentials");
	exit(4);
}
int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_info(t_objects *obj_list, t_data *data, int i)
{
	if (!check_info_size(obj_list, i, data))//check if size of info[n] is correct
		free_and_exit(obj_list, data);
	else if (obj_list[i].type == AMB_LIGHT)
		parse_amb_light(obj_list ,data, i);
	else if (obj_list[i].type == LIGHT)
		parse_light(obj_list ,data, i);
	else if (obj_list[i].type == CAMERA)
		parse_camera(obj_list, data, i);
	else if (obj_list[i].type == CYLINDRE)
		parse_cylindre(obj_list, data, i);
	else if (obj_list[i].type == SPHERE)
		parse_sphere(obj_list, data, i);
	else if (obj_list[i].type == PLANE)
		parse_plane(obj_list, data, i);
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
			if (i < data->list_size - 1)
				ft_strlcpy(obj_list[i].str, obj_list[i].str, ft_strlen(obj_list[i].str));
			data->infos = ft_split(obj_list[i].str, ' ');
			obj_list[i].type = is_obj(data->infos[0]);
			if (obj_list[i].type == NONE)
			{
				write(2, "Error: incorrect information\n", 30);
				free_split(data->infos);
				free(data);
				free_obj_list(obj_list, data);
				exit(1);
			}
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
	FILE* fp = fopen("image.ppm", "wb");
	fprintf(fp, "P6\n%d %d\n255\n", data.w, data.h);
	for (int i = 0; i < data.w * data.h; i++) {
		fputc((int)(data.img[i].red), fp);
		fputc((int)(data.img[i].green), fp);
		fputc((int)(data.img[i].blue), fp);
	}
	fclose(fp);
}

t_color	create_color(int	r, int g, int b)
{
	t_color color;

	color.red = r;
	color.green = g;
	color.blue = b;
	color.alpha = 255;
	return (color);
}

t_vector	transform(t_matrix trans, t_vector ray, int translate)
{
	t_matrix	ray_mat;
	t_matrix	res_mat;
	t_vector	res;

	ray_mat = kc_matrix_init(4, 1);
	ray_mat.elements[0] = ray.x;
	ray_mat.elements[1] = ray.y;
	ray_mat.elements[2] = ray.z;
	ray_mat.elements[3] = translate;
	res_mat = kc_matrix_multi(trans, ray_mat);
	res.x = res_mat.elements[0];
	res.y = res_mat.elements[1];
	res.z = res_mat.elements[2];
	return (res);
}

t_color traceRay(t_ray ray, t_data *data, int depth) {
	int			i;
	t_objects	*objs;
	double t0 = 0;

	if (depth > 5)
		return (create_color(0, 0, 0));
	i = -1;
	double t = INFINITY;
	int intersected = -1;
	objs = data->objs;
	while (++i < data->list_size)
	{
		if (objs[i].type == SPHERE)
			t0 = intersect_s(ray, *(t_sphere*)objs[i].object);
		else if ((char)objs[i].type == CYLINDRE)
			t0 = intersect_c(ray, *(t_cylindre*)objs[i].object);
		else if ((char)objs[i].type == PLANE)
			t0 = intersect_p(ray, *(t_plane*)objs[i].object);
		if (t0 > 0 && t0 < t) {
			t = t0;
			intersected = i;
		}
	}
	if (intersected == -1)
		return (create_color(0, 0, 0));
	return (objs[intersected].color);
}

t_ray	create_ray(t_vector p, t_vector v)
{
	t_ray ray;

	ray.p = p;
	ray.v = v;
	return (ray);	
}

void	trace(t_data *data)
{
	int			i;
	int			j;
	double		v;
	double		u;

	t_vector	d;
	t_ray		ray;
	t_color		color;

	printf("camera h = %f\n", data->camera->h);
	i = -1;
	while (++i < data->h)
	{
		j = -1;
		while (++j < data->w)
		{
			v = (double)j / WIDTH - data->camera->w / 2;
			u = (double)i / WIDTH - data->camera->h / 2;
			d.x = v;
			d.y = u;
			d.z = data->camera->flen;
			d = vectorNormalize(d);
			ray = create_ray(data->camera->point, d);
			ray.v = transform(data->camera->trans, ray.v, 0);
			color = traceRay(ray, data, 2);
			data->img[i * WIDTH + j] = color;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_objects	*obj_list;
	t_ray		ray;

	if (argc < 2)
	{
		write(2, "Error: no parameter found\nusage: ./MiniRT scene.rt\n", 52);
		exit(1);
	}
	t_vector d;
	d.x = 1;
	d.y = 1;
	d.z = 1;
	data = malloc(sizeof(t_data));
	init_data(data, argv);
	obj_list = malloc((data->list_size) * sizeof(t_objects));
	save_info(obj_list, data);
	data->objs = obj_list;
	ray = create_ray(data->camera->point, d);
		printf("BEFORE == \nx = %f, y = %f, z = %f\n", ray.v.x, ray.v.y, ray.v.z);
	ray.v = transform(data->camera->trans, ray.v, 0);
			printf("AFTER == \nx = %f, y = %f, z = %f\n", ray.v.x, ray.v.y, ray.v.z);
	// print_obj_list(obj_list, data);
	// free_obj_list(obj_list, data);
	trace(data);
	make_pic(*data);
	free(obj_list);
	free(data);
}