/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:04:37 by adinari           #+#    #+#             */
/*   Updated: 2023/03/06 16:35:46 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_data(t_data *data, char **argv)
{
	char	*str1;

	data->list_size = 0;
	data->obj_size = 0;
	data->w = WIDTH;
	data->h = HEIGHT;
	data->fd = open(argv[1], O_RDONLY);
	data->img = ft_calloc(data->h * data->w, sizeof(t_color));
	str1 = "";
	while (str1)
	{
		str1 = get_next_line(data->fd);
		if (str1 && first_occur(str1))
			data->list_size++;
		free(str1);
	}
	close(data->fd);
}

t_vector	create_vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
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
			break ;
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

void	free_obj_list(t_objects *obj_list, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->list_size)
	{
		free(obj_list[i].str);
		i++;
	}
}
