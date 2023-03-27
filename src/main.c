/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:39:34 by adinari           #+#    #+#             */
/*   Updated: 2023/03/27 21:20:27 by miahmadi         ###   ########.fr       */
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

void	free_objs(t_objects *obj_list, t_data *data, int i)
{
	int 		j;
	t_cylindre	*tmp;

	j = 0;
	while (j < i)
	{
		if (obj_list[j].type == CAMERA)
		{
			free(data->camera->trans.elements);
			free(data->camera->trans_inv.elements);
			free(data->camera);
		}
		else if (obj_list[j].type == CYLINDRE)
		{
			tmp = obj_list[j].object;
			free(tmp->trans.elements);
			free(tmp->trans_inv.elements);
		}
		else if (obj_list[j].type == LIGHT || obj_list[j].type == AMB_LIGHT)
			free(obj_list[j].object);
		else if (obj_list[j].type != NONE)
			free(obj_list[j].object);
		j++;
	}
}

void	save_info(t_objects *obj_list, t_data *data, char *file)
{
	int	i;

	i = 0;
	data->fd = open(file, O_RDONLY);
	while (i < data->list_size)
	{
		obj_list[i].str = get_next_line(data->fd);
		if (obj_list[i].str && first_occur(obj_list[i].str))
		{
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
	close(data->fd);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_img(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (++i < WIDTH)
	{
		j = 0;
		while (++j < HEIGHT)
			my_mlx_pixel_put(mlx, i, j, 0x00000000);
	}
}

int	cl_to_int(t_color cl)
{
	return (cl.alpha << 24 | cl.red << 16 | cl.green << 8 | cl.blue);
}

int	closing(t_data *data)
{
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	main_free(data->objs, data);
	system("leaks MiniRT");
	exit(0);
}

int	render(t_data *data)
{
	int	i;
	int	j;

	// clear_img(data->mlx);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			my_mlx_pixel_put(data->mlx, i, j, cl_to_int(data->img[j * WIDTH + i]));
		}
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->img, 0, 0);
	return (0);
}

int	print_key(int key, t_data *data)
{
	if (key == 53)
		closing(data);
	return (0);
}

int	exit_error(char *msg, int l)
{
	write(2, msg, l);
	return (errno);
}

//terminal : arch, makefile: add -lm flag
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --tool=memcheck -s ./MiniRT scene.rt
int	main(int argc, char **argv)
{
	t_data		*data;
	t_objects	*obj_list;
	t_ray		ray;
	t_vector	d;
	t_mlx		mlx;

	if (argc != 2)
		exit(exit_error("Error: no parameter found\nusage: ./MiniRT scene.rt\n", 52));
	if (open(argv[1], O_RDONLY) == -1)
		exit(exit_error("Error: file does not exists or is corrupted\n", 44));
	d.x = 1;
	d.y = 1;
	d.z = 1;
	data = malloc(sizeof(t_data));
	init_data(data, argv);
	obj_list = malloc((data->list_size) * sizeof(t_objects));
	save_info(obj_list, data, argv[1]);
	data->objs = obj_list;
	data->mlx = &mlx;
	ray = create_ray(data->camera->point, d);
	ray.v = transform(data->camera->trans, ray.v, 0);
	trace(data);
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Milad & Anas :: MiniRT");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	mlx_hook(mlx.mlx_win, 17, 0, closing, data);
	mlx_hook(mlx.mlx_win, 2, 0, print_key, data);
	mlx_loop_hook(mlx.mlx, render, data);
	mlx_loop(mlx.mlx);
	return (0);
}
