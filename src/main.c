/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:39:34 by adinari           #+#    #+#             */
/*   Updated: 2023/04/29 00:13:36 by adinari          ###   ########.fr       */
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
	int			j;
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

	i = -1;
	data->fd = open(file, O_RDONLY);
	while (++i < data->list_size)
	{
		obj_list[i].str = get_next_line(data->fd);
		if (obj_list[i].str && first_occur(obj_list[i].str))
		{
			if (obj_list[i].str[ft_strlen(obj_list[i].str) - 1] == '\n')
				ft_strlcpy(obj_list[i].str,
					obj_list[i].str, ft_strlen(obj_list[i].str));
			data->infos = ft_split(obj_list[i].str, ' ');
			obj_list[i].type = is_obj(data->infos[0]);
			type_error(obj_list, data, i);
			parse_info(obj_list, data, i);
			free_split(data->infos);
		}
		else
			free(obj_list[i].str);
	}
	close(data->fd);
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

int	main(int argc, char **argv)
{
	t_data		*data;
	t_objects	*obj_list;

	if (argc != 2)
		exit(exit_error("Error: no parameter found\nusage: ./MiniRT scene.rt\n",
				52));
	if (open(argv[1], O_RDONLY) == -1)
		exit(exit_error("Error: file does not exists or is corrupted\n", 44));
	data = malloc(sizeof(t_data));
	init_data(data, argv);
	obj_list = malloc((data->list_size) * sizeof(t_objects));
	save_info(obj_list, data, argv[1]);
	data->objs = obj_list;
	trace(data);
	init_mlx_related(data);
	return (0);
}
