/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 07:55:44 by adinari           #+#    #+#             */
/*   Updated: 2023/03/31 22:15:56 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx_related(t_data *data)
{
	t_mlx	mlx;

	data->mlx = &mlx;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx,
			WIDTH, HEIGHT, "Milad & Anas :: MiniRT");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	mlx_hook(mlx.mlx_win, 17, 0, closing, data);
	mlx_hook(mlx.mlx_win, 2, 0, print_key, data);
	mlx_loop_hook(mlx.mlx, render, data);
	mlx_loop(mlx.mlx);
}
