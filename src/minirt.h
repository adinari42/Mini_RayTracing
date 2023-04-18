/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:47:18 by adinari           #+#    #+#             */
/*   Updated: 2023/04/16 10:16:14 by miahmadi         ###   ########.fr       */
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
# include "../mlx/mlx.h"
# include "matrix.h"
# include "libft/libft.h"

# define PI 3.14159
# define EPSILON 1e-6
# define WIDTH 960
# define HEIGHT 600

typedef struct s_mlx
{
	void	*mlx;
	void	*img;
	void	*mlx_win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

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
typedef struct s_objects
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

enum e_obj_type
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
	double		diameter;
	t_vector	point;
	t_color		color;
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
	t_mlx		*mlx;
	t_color		*img;
	t_camera	*camera;
	t_light		*light;
	t_amb_light	*amb_light;
	char		**infos;
}				t_data;

typedef struct s_hitpoint
{
	t_vector	point;
	t_objects	object;
	double		dist;
}				t_hitpoint;

typedef struct s_intersect_vars
{
	t_vector	ls;
	double		tca;
	double		d2;
	double		thc;
	double		t0;
}				t_intersect_vars;

typedef struct s_hitpoints
{
	t_hitpoint	hit;
	t_hitpoint	temp;
	int			index;
}				t_hitpoints;

typedef struct s_doubles
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		t2;
	double		dist;
	double		tmp_t;
}				t_doubles;

typedef struct s_light_vectors
{
	t_vector	n;
	t_vector	p;
	t_vector	cen;
}				t_light_vectors;

typedef struct s_num_parse
{
	int		sign;
	int		exponent;
	int		exponent_sign;
	int		base;
	int		has_decimal_point;
}				t_num_parse;

typedef struct s_parse_vectors
{
	t_vector	up;
	t_vector	dir_x;
	t_vector	dir_y;
}				t_parse_vectors;

typedef struct s_trace
{
	double		v;
	double		u;
	t_vector	d;
	t_ray		ray;
	t_color		color;
}				t_trace;

typedef struct s_intrsc_dbl
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		t2;
	double		dist;
	double		tmp_t;
}				t_intrsc_dbl;

int				main(int argc, char **argv);
int				str_isdigit(char *str);
/*utils.c*/
void			init_data(t_data *data, char **argv);
void			free_split(char **splitret);
void			print_obj_list(t_objects *obj_list, t_data *data);
void			free_obj_list(t_objects *obj_list, t_data *data);
int				first_occur(char *str);
int				ft_isfloat(char *str);
double			ft_atof(const char *str);
// double	ft_atodoubl(const char *str, char **endptr);

/**parse.c***/
void			parse_light(t_objects *obj_list, t_data *data, int i);
void			parse_amb_light(t_objects *obj_list, t_data *data, int i);
void			parse_camera(t_objects *obj_list, t_data *data, int i);
void			parse_cylindre(t_objects *obj_list, t_data *data, int i);
void			parse_sphere(t_objects *obj_list, t_data *data, int i);
void			parse_plane(t_objects *obj_list, t_data *data, int i);
t_vector		vector_subtract(t_vector v1, t_vector v2);
t_vector		vector_add(t_vector v1, t_vector v2);
t_vector		vector_scale(t_vector v, double s);
t_vector		vector_normalize(t_vector v);
double			vector_dot_product(t_vector v1, t_vector v2);
/*vector_op_2.c*/
t_vector		vector_cross_product(t_vector v1, t_vector v2);
double			vector_dot_product_print(t_vector v1, t_vector v2);
t_vector		vector_project(t_vector v1, t_vector v2);
/*intersect.c*/
t_hitpoint		intersect_s(t_ray ray, t_sphere *sphere);
t_hitpoint		intersect_c(t_ray ray, t_cylindre *c);
t_hitpoint		intersect_p(t_ray ray, t_plane *plane);
t_color			create_color(int r, int g, int b);
t_vector		transform(t_matrix trans, t_vector ray, int translate);
t_vector		create_vector(double x, double y, double z);
void			vector_print(char *msg, t_vector v);
t_color			compute_lighting(t_ray light, t_hitpoint hit,
					double intense, t_ray ray);
int				is_shadow(t_ray light, t_data *data, t_hitpoint hit, int idx);
t_color			add_ambient(t_color color, t_amb_light *light);
/*intersect_utils.c*/
t_hitpoints		init_cyl_hp(t_cylindre *cylinder);
t_doubles		init_doubles(t_ray	new_ray, t_cylindre *cylinder);
t_hitpoint		update_hit(t_cylindre *cylinder, t_plane *plane);
void			update_2(t_cylindre *cylinder, t_plane *plane,
					t_ray *ray, t_hitpoint *hit_1);
void			update_point_doubles(t_intrsc_dbl *doubles,
					t_ray *new_ray, t_vector *point1);
/*intersect_utils_2.c*/
void			init_hit(t_cylindre *cylinder, t_hitpoint *hit_0);
void			intersect_init(t_cylindre *cylinder,
					t_ray *new_ray, t_intrsc_dbl *doubles, t_ray *ray);
void			cond_1(t_cylindre *cylinder,
					t_vector *point1, t_intrsc_dbl *doubles, t_ray *ray);
void			init_plane(t_ray *ray, t_cylindre *cylinder,
					t_hitpoint *hit_1, t_plane *plane);
int				update_hit_cond(t_cylindre *cylinder,
					t_ray *new_ray, t_intrsc_dbl *doubles, t_hitpoint *hit_1);
/*intersect_utils_3.c*/
int				calculate_dist_from_cyl(t_ray new_ray,
					t_hitpoint hit, double dia);
t_hitpoint		create_cylndr_plane(t_color color,
					t_plane *p, t_intrsc_dbl *dbs, double dist);
/*lighting_utils.c*/
double			set_plane_vectors(t_light_vectors	*vectors, t_hitpoint hit,
					t_ray ray, t_ray light);
double			set_sphere_vectors(t_light_vectors	*vectors, t_hitpoint hit,
					t_ray ray, t_ray light);
double			set_cylindre_vectors(t_light_vectors *vectors,
					t_hitpoint hit, t_ray light);
double			init_this_hit(t_hitpoint hit, t_ray light);
/*parse_utils_t.c*/
int				check_sign(const char *str);
int				base_prefix(const char *str);
int				parse_exponent(const char *str);
int				update_exponent(const char *str);
/*parse_utils_3.c*/
void			cam_w_h_flen(t_camera *obj, t_data *data);
void			cam_point_and_normal(t_camera *obj, t_data *data);
t_parse_vectors	cam_up_and_dir(t_camera *obj);
void			cam_transform(t_camera *obj, t_parse_vectors vectors);
void			set_light_point(t_light *obj, t_data *data);
void			set_cam_point(t_camera *obj, t_data *data);

/*parse_utils_4.c*/
void			cyl_dim_point_normal(t_data *data,
					t_objects *obj_list, t_cylindre *obj, int i);
t_parse_vectors	cyl_up_and_dir(t_cylindre *obj);
void			cyl_transform(t_cylindre *obj, t_parse_vectors vectors);
void			plane_point_and_normal(t_plane *obj, t_data *data);
/*trace_ray.c*/
t_color			create_color(int r, int g, int b);
t_vector		transform(t_matrix trans, t_vector ray, int translate);
void			set_hp(t_ray ray, t_data *data, t_hitpoints	*hp);
t_color			trace_ray(t_ray ray, t_data *data, int depth);
void			trace(t_data *data);
/*main_utils.c*/
t_ray			create_ray(t_vector p, t_vector v);
int				is_obj(char *str);
int				check_info_size(t_objects *obj_list, int j, t_data *data);
void			free_and_exit(t_objects *obj_list, t_data *data);
int				str_isdigit(char *str);
/*utils_2.c*/
void			main_free(t_objects *obj_list, t_data *data);
void			make_pic(t_data data);
void			type_error(t_objects *obj_list, t_data *data, int i);
void			free_obj_str(t_objects *obj_list, int i);
void			free_data(t_objects *obj_list, t_data *data, int i);
/*utils_2.c*/
void			free_camera(t_data *data);
void			else_free(t_objects *obj_list, int j);
void			create_light_color(t_data *data,
					t_light *obj, int i, t_objects *obj_list);
void			create_amblight_color(t_data *data,
					void *obj, int i, t_objects *obj_list);
void			create_cylinder_color(t_data *data,
					t_cylindre *obj, int i, t_objects *obj_list);
/*utils_3.c*/
void			create_sphere_color(t_data *data,
					void *obj, int i, t_objects *obj_list);
void			create_plane_color(t_data *data,
					t_plane *obj, int i, t_objects *obj_list);
/*cyl_parse_utils.c*/
void			cyl_height_and_diameter(t_data *data, t_cylindre *obj);
void			cyl_normal(t_data *data, t_cylindre *obj);
void			cyl_dim_point_normal(t_data *data,
					t_objects *obj_list, t_cylindre *obj, int i);
/*main_utils_2.c*/
int				cl_to_int(t_color cl);
int				closing(t_data *data);
int				render(t_data *data);
int				print_key(int key, t_data *data);
int				exit_error(char *msg, int l);
/*main_utils_3.c*/
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			init_mlx_related(t_data *data);

#endif