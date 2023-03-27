/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:13:13 by adinari           #+#    #+#             */
/*   Updated: 2023/03/27 03:55:07 by adinari          ###   ########.fr       */
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

	obj = malloc(sizeof(t_plane));
	obj_list[i].object = obj;
	plane_point_and_normal(obj, data);
	create_plane_color(data, obj, i, obj_list);
	data->obj_size++;
}
