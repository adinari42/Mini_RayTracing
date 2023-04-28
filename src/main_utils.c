/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:24:19 by adinari           #+#    #+#             */
/*   Updated: 2023/04/28 21:57:30 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_vector p, t_vector v)
{
	t_ray	ray;

	ray.p = p;
	ray.v = v;
	return (ray);
}

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

void	free_and_exit(t_objects *obj_list, t_data *data)
{
	(void)obj_list;
	free_split(data->infos);
	printf("Parse error: incorrect credentials");
	exit(22);
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
