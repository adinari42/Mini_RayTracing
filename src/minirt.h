/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:47:18 by adinari           #+#    #+#             */
/*   Updated: 2023/02/26 18:44:40 by miahmadi         ###   ########.fr       */
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
# include "gnl/get_next_line.h"
# include "matrix.h"
# include "libft/libft.h"

# define PI 3.14159
# define EPSILON 1e-6
# define WIDTH 2400
# define HEIGHT 1350

typedef struct s_normal
{
	double	x;
	double	y;
	double	z;
}				t_normal;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}				t_color;

typedef struct s_camera
{
	t_vector	point;
	t_vector	normal;
	t_matrix	trans;
	t_matrix	trans_inv;
	double		fov;
	double		flen;
	double		h;
	double		w;
}				t_camera;

typedef struct s_light
{
	t_vector	point;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_amb_light
{
	double	ratio;
	t_color	color;
}				t_amb_light;

//linked list of shapes/objects
typedef struct	s_objects
{
	char		*str;
	void		*object;
	int			type;
	t_color		color;
}				t_objects;

typedef struct s_ray
{
	t_vector	v;
	t_vector	p;
}				t_ray;

enum obj_type
{
	AMB_LIGHT,
	LIGHT,
	CAMERA,
	CYLINDRE,
	PLANE,
	SPHERE,
	CPLANE,
	NONE,
};

typedef struct s_cylindre
{
	t_vector	point;
	t_color		color;
	t_vector	normal;
	double		height;
	double		diameter;
	t_matrix	trans;
	t_matrix	trans_inv;
}				t_cylindre;

typedef struct s_sphere
{
	double	diameter;
	t_vector	point;
	t_color	color;
}				t_sphere;

typedef struct s_plane
{
	t_vector	normal;
	t_vector	point;
	t_color		color;
}				t_plane;

typedef struct s_data
{
	t_objects	*objs;
	int			w;
	int			h;
	int			list_size;
	int			obj_size;
	int			fd;
	t_color		*img;
	t_camera	*camera;
	t_light		*light;
	t_amb_light	*amb_light;
	char		**infos;
}				t_data;

typedef struct	s_hitpoint
{
	t_vector	point;
	t_objects	object;
	double		dist;
}				t_hitpoint;




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
void		parse_light(t_objects *obj_list, t_data *data, int i);
void		parse_amb_light(t_objects *obj_list, t_data *data, int i);
void		parse_camera(t_objects *obj_list, t_data *data, int i);
void		parse_cylindre(t_objects *obj_list, t_data *data, int i);
void		parse_sphere(t_objects *obj_list, t_data *data, int i);
void		parse_plane(t_objects *obj_list, t_data *data, int i);
t_vector	vectorSubtract(t_vector v1, t_vector v2);
t_vector	vectorAdd(t_vector v1, t_vector v2);
t_vector	vectorScale(t_vector v, double s);
t_vector	vectorNormalize(t_vector v);
t_vector	vectorCrossProduct(t_vector v1, t_vector v2);
double		vectorDotProduct(t_vector v1, t_vector v2);
double		vectorDotProductPrint(t_vector v1, t_vector v2);
t_vector 	vectorProject(t_vector v1, t_vector v2);
t_hitpoint	intersect_s(t_ray ray, t_sphere *sphere);
t_hitpoint	intersect_c(t_ray ray, t_cylindre *c);
t_hitpoint	intersect_p(t_ray ray, t_plane *plane);
t_color		create_color(int	r, int g, int b);
t_vector	transform(t_matrix trans, t_vector ray, int translate);
t_vector	create_vector(double x, double y, double z);
void		vectorPrint(char *msg, t_vector v);
t_color		compute_lighting(t_ray light, t_hitpoint hit, double intense, t_ray ray);
int			is_shadow(t_ray light, t_data *data, t_hitpoint hit, int idx);
t_color		add_ambient(t_color color, t_amb_light *light);

#endif