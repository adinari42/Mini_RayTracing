/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:47:18 by adinari           #+#    #+#             */
/*   Updated: 2023/01/18 13:23:29 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include <math.h>
# include "../codam_MLX/include/MLX42/MLX42.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct s_normal
{
	double	x;
	double	y;
	double	z;
}				t_normal;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}				t_color;

typedef struct s_camera
{
	t_point		point;
	t_normal	normal;
	double		fov;
	double		fov_len;
	double		height;
	double		width;
}				t_camera;

typedef struct s_light
{
	t_point	point;
	double	ratio;
	t_color	color;
}				t_light;

typedef struct s_amb_light
{
	double	ratio;
	t_color	color;
}				t_amb_light;

//linked list of shapes/objects
typedef struct	s_objects
{
	char				*str;
	void				*object;
	int					type;
}				t_objects;

typedef struct	s_data
{
	int	list_size;
	int	amb_light;
	int	light;
	int	camera;
	int	scene;
	char 				**infos;
}				t_data;

enum obj_type
{
	AMB_LIGHT,
	LIGHT,
	CAMERA,
	CYLINDRE,
	PLANE,
	SPHERE,
	NONE,
};

typedef struct s_cylindre
{
	t_point	point;
	t_color	color;
	t_normal	normal;
	double		height;
	double		diameter;
}				t_cylindre;

typedef struct s_sphere
{
	double	diameter;
	t_point	point;
	t_color	color;
}				t_sphere;

typedef struct s_plane
{
	t_normal	normal;
	t_point		point;
	t_color		color;
}				t_plane;


int main(int argc, char **argv);
int	str_isdigit(char *str);
/*utils.c*/
void	init_data(t_data *data, char **argv);
void	free_split(char **splitret);
void	print_obj_list(t_objects *obj_list, t_data *data);
void	free_obj_list(t_objects *obj_list, t_data *data);
int		first_occur(char *str);
int		ft_isfloat(char *str);
double	ft_atof(const char *str);
// double	ft_atodoubl(const char *str, char **endptr);

/**parse.c***/
void	parse_light(t_objects *obj_list, t_data *data, int i);
void	parse_amb_light(t_objects *obj_list, t_data *data, int i);
void	parse_camera(t_objects *obj_list, t_data *data, int i);
void	parse_cylindre(t_objects *obj_list, t_data *data, int i);
void	parse_sphere(t_objects *obj_list, t_data *data, int i);
void	parse_plane(t_objects *obj_list, t_data *data, int i);
#endif