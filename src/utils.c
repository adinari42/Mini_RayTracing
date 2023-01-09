/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:04:37 by adinari           #+#    #+#             */
/*   Updated: 2023/01/10 00:02:12 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

void	init_data(t_data *data, char **argv)
{
	char 		*str1;

	data->list_size = 0;
	data->camera = 0;
	data->light = 0;
	data->amb_light = 0;
	data->scene = open(argv[1], O_RDONLY);
	str1 = "";
	while(str1){
		str1 = get_next_line(data->scene);
		if (str1 && first_occur(str1))
			data->list_size++;
		free(str1);
	}
	printf("data->list_size = %d\n", data->list_size);
	close(data->scene);
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
	int	i;

	i = 0;
	while (i < data->list_size)
	{
		printf("obj_list[%d]->str = %s >type = %d\n", i , obj_list[i].str, obj_list[i].type);
		if (obj_list[i].type == AMB_LIGHT)
		{
			printf("ratio = %f\ncolors = %d, %d, %d\n", ((t_amb_light *)obj_list[i].object)->ratio,
			((t_amb_light *)obj_list[i].object)->color.red, ((t_amb_light *)obj_list[i].object)->color.green, ((t_amb_light *)obj_list[i].object)->color.blue);
		}
		if (obj_list[i].type == LIGHT)
		{
			printf("ratio = %f\ncolors = %d, %d, %d\n", ((t_light *)obj_list[i].object)->ratio,
			((t_light *)obj_list[i].object)->color.red, ((t_light *)obj_list[i].object)->color.green, ((t_light *)obj_list[i].object)->color.blue);
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

