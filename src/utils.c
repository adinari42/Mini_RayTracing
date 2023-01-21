/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:04:37 by adinari           #+#    #+#             */
/*   Updated: 2023/01/21 15:56:31 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	init_data(t_data *data, char **argv)
{
	char 		*str1;

	data->list_size = 0;
	data->obj_size = 0;
	data->w = WIDTH;
	data->h = HEIGHT;
	data->fd = open(argv[1], O_RDONLY);
	data->img = ft_calloc(data->h * data->w, sizeof(t_color));
	str1 = "";
	while(str1){
		str1 = get_next_line(data->fd);
		if (str1 && first_occur(str1))
			data->list_size++;
		free(str1);
	}
	close(data->fd);
}

int	first_occur(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
	{
		if (ft_isalpha(str[i]))
			return (1);
		else if (ft_isalnum(str[i]))
			break ;
		else
			break;
		i++;
	}
	return (0);
}

void	free_split(char **splitret)
{
	int	i;

	if (!splitret)
		return ;
	i = 0;
	while (splitret[i] && ft_strncmp(splitret[i], "", 1))
	{
		free(splitret[i]);
		i++;
	}
	free(splitret[i]);
	free(splitret);
	return ;
}

void	print_obj_list(t_objects *obj_list, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->list_size)
	{

		printf("\033[1;31mobj_list[%d]->str = %s >type = %d\033[0m\n", i , obj_list[i].str, obj_list[i].type);
		if (obj_list[i].type == AMB_LIGHT)
		{
			printf("ratio = %f\ncolors = %d, %d, %d\n", ((t_amb_light *)obj_list[i].object)->ratio,
			((t_amb_light *)obj_list[i].object)->color.red, ((t_amb_light *)obj_list[i].object)->color.green,
			((t_amb_light *)obj_list[i].object)->color.blue);
		}
		if (obj_list[i].type == LIGHT)
		{
			printf("ratio = %f\ncolors = %d, %d, %d\n", ((t_light *)obj_list[i].object)->ratio,
			((t_light *)obj_list[i].object)->color.red, ((t_light *)obj_list[i].object)->color.green,
			((t_light *)obj_list[i].object)->color.blue);
			printf("point[x] = %f, [y] = %f, [z] = %f\n", ((t_light *)obj_list[i].object)->point.x
			, ((t_light *)obj_list[i].object)->point.y, ((t_light *)obj_list[i].object)->point.z);
		}
		if (obj_list[i].type == CAMERA)
		{
			printf("fov = %f\nnormal = %f, %f, %f\n", ((t_camera *)obj_list[i].object)->fov,
			((t_camera *)obj_list[i].object)->normal.x, ((t_camera *)obj_list[i].object)->normal.y,
			((t_camera *)obj_list[i].object)->normal.z);
			printf("point[x] = %f, [y] = %f, [z] = %f\n", ((t_camera *)obj_list[i].object)->point.x
			, ((t_camera *)obj_list[i].object)->point.y, ((t_camera *)obj_list[i].object)->point.z);
		}
		if (obj_list[i].type == CYLINDRE)
		{
			printf("height = %f, diameter = %f\nnormal = %f, %f, %f\n", ((t_cylindre *)obj_list[i].object)->height,
			((t_cylindre *)obj_list[i].object)->diameter,
			((t_cylindre *)obj_list[i].object)->normal.x, ((t_cylindre *)obj_list[i].object)->normal.y,
			((t_cylindre *)obj_list[i].object)->normal.z);
			printf("point[x] = %f, [y] = %f, [z] = %f\ncolors = %d, %d, %d\n", ((t_cylindre *)obj_list[i].object)->point.x
			, ((t_cylindre *)obj_list[i].object)->point.y, ((t_cylindre *)obj_list[i].object)->point.z,
			((t_cylindre *)obj_list[i].object)->color.red, ((t_cylindre *)obj_list[i].object)->color.green,
			((t_cylindre *)obj_list[i].object)->color.blue);
		}
		if (obj_list[i].type == SPHERE)
		{
			printf("diameter = %f\n",((t_sphere *)obj_list[i].object)->diameter);
			printf("point[x] = %f, [y] = %f, [z] = %f\ncolors = %d, %d, %d\n", ((t_sphere *)obj_list[i].object)->point.x
			, ((t_sphere *)obj_list[i].object)->point.y, ((t_sphere *)obj_list[i].object)->point.z,
			((t_sphere *)obj_list[i].object)->color.red, ((t_sphere *)obj_list[i].object)->color.green,
			((t_sphere *)obj_list[i].object)->color.blue);
		}
		if (obj_list[i].type == PLANE)
		{
			printf("normal = %f, %f, %f\n",
			((t_plane *)obj_list[i].object)->normal.x, ((t_plane *)obj_list[i].object)->normal.y,
			((t_plane *)obj_list[i].object)->normal.z);
			printf("point[x] = %f, [y] = %f, [z] = %f\ncolors = %d, %d, %d\n", ((t_plane *)obj_list[i].object)->point.x
			, ((t_plane *)obj_list[i].object)->point.y, ((t_plane *)obj_list[i].object)->point.z,
			((t_plane *)obj_list[i].object)->color.red, ((t_plane *)obj_list[i].object)->color.green,
			((t_plane *)obj_list[i].object)->color.blue);
		}
		i++;
	}
}
void	free_obj_list(t_objects *obj_list, t_data *data)
{
	int	i;
	// (void)obj_list;
	i = 0;
	while (i < data->list_size)
	{
		// printf("freeobj: i = %d, listsize = %d\n", i, data->list_size);
		free(obj_list[i].str);
		i++;
	}
}

