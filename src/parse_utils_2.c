/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:13:13 by adinari           #+#    #+#             */
/*   Updated: 2023/03/25 23:03:17 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_sign(const char *str)
{
	int	sign;

	sign = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	return (sign);
}

int	base_prefix(const char *str)
{
	int	base;

	base = 10;
	if (*str == '0')
	{
		str++;
		if (*str == 'x' || *str == 'X')
		{
			base = 16;
			str++;
		}
		else
			base = 8;
	}
	return (base);
}

int	parse_exponent(const char *str)
{
	int	exponent_sign;

	exponent_sign = 1;
	str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		exponent_sign = -1;
		str++;
	}
	return (exponent_sign);
}

int	update_exponent(const char *str)
{
	int	exponent;

	exponent = 0;
	while (isdigit(*str))
	{
		exponent = exponent * 10 + (*str - '0');
		str++;
	}
	return (exponent);
}

void	parse_plane(t_objects *obj_list, t_data *data, int i)
{
	t_plane		*obj;
	char		**colors;
	t_color		c;

	obj = malloc(sizeof(t_plane));
	obj_list[i].object = obj;
	plane_point_and_normal(obj, data);
	colors = ft_split(data->infos[3], ',');
	c = create_color(ft_atof(colors[0]), ft_atof(colors[1]), ft_atof(colors[2]));
	if (!ft_isfloat(colors[0]) && !ft_isfloat(colors[1]) && !ft_isfloat(colors[2])
		&& c.red <= 255 && c.blue <= 255 && c.green <= 255
		&& c.red >= 0 && c.blue >= 0 && c.green >= 0)
	{
		obj_list[i].color = create_color(ft_atoi(colors[0]),
				ft_atoi(colors[1]), ft_atoi(colors[2]));
		((t_plane *)obj)->color = c;
	}
	else
	{
		printf("PLANE COLORS ERROR!");
		free(obj);
		free_split(colors);
		free_obj_list(obj_list, data);
		exit(3);
	}
	free_split(colors);
	data->obj_size++;
}
