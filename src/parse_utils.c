/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 01:21:14 by adinari           #+#    #+#             */
/*   Updated: 2023/03/27 03:50:56 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	parse_number(const char *str, t_num_parse n_parse)
{
	double	value;

	value = 0;
	while (*str)
	{
		if (isdigit(*str))
			value = value * n_parse.base + (*str - '0');
		else if (*str == '.')
		{
			if (n_parse.has_decimal_point)
				break ;
			n_parse.has_decimal_point = 1;
		}
		else if (*str == 'e' || *str == 'E')
		{
			n_parse.exponent_sign = parse_exponent(str);
			n_parse.exponent = update_exponent(str);
			break ;
		}
		else
			break ;
		str++;
	}
	return (value);
}

double	ft_atodoubl(const char *str, char **endptr)
{
	double		value;
	t_num_parse	n_parse;

	n_parse = (t_num_parse){0};
	errno = 0;
	while (isspace(*str))
		str++;
	n_parse.sign = check_sign(str);
	n_parse.base = base_prefix(str);
	value = parse_number(str, n_parse);
	value = n_parse.sign * value
		* pow(n_parse.base, n_parse.exponent_sign * n_parse.exponent);
	if (endptr)
		*endptr = (char *)str;
	return (value);
}

int	ft_isfloat(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
		return (1);
	i++;
	while (str[i] && i < ft_strlen(str))
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
			return (1);
		if (str[i] == '.')
			dot_count++;
		i++;
	}
	if (str[i - 1] == '.')
		return (1);
	if (dot_count != 0 && dot_count != 1)
		return (1);
	return (0);
}

const char	*get_start(const char *str, int *sign)
{
	while ((*str >= 9 && *str <= 13 && *str != 0) || *str == ' ')
		str++;
	*sign = 1;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

double	ft_atof(const char *str)
{
	int		sign;
	int		afterdot;
	double	scale;
	double	number;

	str = get_start(str, &sign);
	afterdot = 0;
	scale = 1;
	number = 0;
	while ((*str >= '0' && *str <= '9' && *str != 0) || *str == '.')
	{
		if (afterdot)
		{
			scale = scale / 10.0;
			number += (*str - '0') * scale;
		}
		else if (*str == '.')
			afterdot = 1;
		else
			number = number * 10.0 + (*str - '0');
		str++;
	}
	number *= (double) sign;
	return (number);
}
