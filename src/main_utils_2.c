/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 07:50:15 by adinari           #+#    #+#             */
/*   Updated: 2023/03/31 22:10:11 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cl_to_int(t_color cl)
{
	return (cl.alpha << 24 | cl.red << 16 | cl.green << 8 | cl.blue);
}

int	closing(t_data *data)
{
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	exit(0);
}

int	render(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
			my_mlx_pixel_put(data->mlx, i, j,
				cl_to_int(data->img[j * WIDTH + i]));
	}
	mlx_put_image_to_window(data->mlx->mlx,
		data->mlx->mlx_win, data->mlx->img, 0, 0);
	return (0);
}

int	print_key(int key, t_data *data)
{
	if (key == 53)
		closing(data);
	return (0);
}

int	exit_error(char *msg, int l)
{
	write(2, msg, l);
	return (errno);
}
