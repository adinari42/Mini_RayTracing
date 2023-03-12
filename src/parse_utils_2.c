/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:13:13 by adinari           #+#    #+#             */
/*   Updated: 2023/03/08 18:26:25 by adinari          ###   ########.fr       */
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

	obj = malloc(sizeof(t_plane));
	obj_list[i].object = obj;
	plane_point_and_normal(obj, data);
	colors = ft_split(data->infos[3], ',');
	obj_list[i].color = create_color(ft_atoi(colors[0]),
			ft_atoi(colors[1]), ft_atoi(colors[2]));
	if (str_isdigit(colors[0])
		&& str_isdigit(colors[1]) && str_isdigit(colors[2]))
	{
		obj->color.red = ft_atoi(colors[0]);
		obj->color.green = ft_atoi(colors[1]);
		obj->color.blue = ft_atoi(colors[2]);
	}
	free_split(colors);
	data->obj_size++;
}
