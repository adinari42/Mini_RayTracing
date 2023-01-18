/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:39:34 by adinari           #+#    #+#             */
/*   Updated: 2023/01/10 05:39:41 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float get_significand(float significand, const char *str, int index, int power) {
//     while (isdigit(str[index])) {
//         significand = significand * 10 + (str[index] - '0');
//         power--;
//         index++;
//     }
//     return significand * pow(10, power);
// }

// float	ft_atof(char *str)
// {
// 	float	exponent;
// 	float	significand;
// 	float	sign;
// 	int		power;
// 	int		i;

// 	exponent = 0.0;
// 	significand = 0.0;
// 	sign = 1.0;
// 	power = -1;
// 	i = 0;
// 	if (str[i] == '-') 
// 	{
// 		sign *= -1.0;
// 		i++;
// 	}
// 	while (ft_isdigit(str[i]))
// 	{
// 		exponent = exponent * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	significand = get_significand(significand, str, i, power);
// 	return (sign * (exponent + significand));
// }

int	is_obj(char *str, t_data *data)
{

	if (!ft_strncmp(str, "A", ft_strlen(str)))
	{
		if (data->amb_light == 0)
		{
			data->amb_light = 1;
			return (AMB_LIGHT);
		}
		else
			return (NONE);
	}
	if (!ft_strncmp(str, "C", ft_strlen(str)))
	{
		if (data->camera == 0)
		{
			data->camera = 1;
			return (CAMERA);
		}
		else
			return (NONE);
	}
	if (!ft_strncmp(str, "L", ft_strlen(str)))
	{
		if (data->light == 0)
		{
			data->light = 1;
			return (LIGHT);
		}
		else
			return (NONE);
	}
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
// int	str_isfloat(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_isfloat(str[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }





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
	data->scene = open("scene.rt", O_RDONLY);
	while (i < data->list_size)
	{
		obj_list[i].str = get_next_line(data->scene);
		if (obj_list[i].str && first_occur(obj_list[i].str))
		{
			if (i < data->list_size - 1)
				ft_strlcpy(obj_list[i].str, obj_list[i].str, ft_strlen(obj_list[i].str));
			data->infos = ft_split(obj_list[i].str, ' ');
			obj_list[i].type = is_obj(data->infos[0], data);
			if (obj_list[i].type == NONE)
			{
				write(2, "Error: incorrect information\n", 30);
				free_split(data->infos);
				free(data);
				free_obj_list(obj_list, data);
				// system("leaks MiniRT");//
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

int	main(int argc, char **argv)
{
	t_data		*data;
	t_objects	*obj_list;

	if (argc < 2)
	{
		write(2, "Error: no parameter found\nusage: ./MiniRT scene.rt\n", 52);
		exit(1);
	}
	data = malloc(sizeof(t_data));
	init_data(data, argv);
	obj_list = malloc((data->list_size) * sizeof(t_objects));
	save_info(obj_list, data);
	print_obj_list(obj_list, data);
	free_obj_list(obj_list, data);
	free(obj_list);
	free(data);
	system("leaks MiniRT");
}