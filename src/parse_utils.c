/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 01:21:14 by adinari           #+#    #+#             */
/*   Updated: 2023/01/10 05:46:39 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double ft_atodoubl(const char *str, char **endptr)
{
    double value = 0;
    int sign = 1;
    int exponent = 0;
    int exponent_sign = 1;
    int base = 10;
    int has_decimal_point = 0;

    errno = 0;

    // skip leading white space
    while (isspace(*str)) str++;

    // check for sign
    if (*str == '+') {
        str++;
    } else if (*str == '-') {
        sign = -1;
        str++;
    }

    // check for base prefix
    if (*str == '0') {
        str++;
        if (*str == 'x' || *str == 'X') {
            base = 16;
            str++;
        } else {
            base = 8;
        }
    }

    // parse number
    while (*str) {
        if (isdigit(*str)) {
            value = value * base + (*str - '0');
        } else if (*str == '.') {
            if (has_decimal_point) {
                // second decimal point
                break;
            }
            has_decimal_point = 1;
        } else if (*str == 'e' || *str == 'E') {
            // parse exponent
            str++;
            if (*str == '+') {
                str++;
            } else if (*str == '-') {
                exponent_sign = -1;
                str++;
            }
            while (isdigit(*str)) {
                exponent = exponent * 10 + (*str - '0');
                str++;
            }
            break;
        } else {
            // invalid character
            break;
        }
        str++;
    }

    // apply sign and exponent
    value = sign * value * pow(base, exponent_sign * exponent);

    // set endptr
    if (endptr) {
        *endptr = (char *)str;
    }

    return value;
}


bool	ft_isfloat(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
		return (false);
	// i++;
	while (str[i] != '0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
			return (false);
		if (str[i] == '.')
			dot_count++;
		i++;
	}
	if (str[i - 1] == '.')
		return (false);
	if (dot_count != 0 && dot_count != 1)
		return (false);
	return (true);
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