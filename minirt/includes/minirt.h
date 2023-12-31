/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:02:11 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/09 23:24:11 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "error.h"
# include "libft.h"
# include "MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define EPSILON 0.00001
# define HEIGHT 1000
# define WIDTH 1000
# define WALL_SIZE 8.0
# define WALL_Z 7.0
# define VECTOR 0
# define POINT 1
# define X_AXIS 1
# define Y_AXIS 2
# define Z_AXIS 0
# define SP 1
# define CY 2
# define PL 3
# define OUTSIDE 0
# define INSIDE 1

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_coordinates;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_amb_light
{
	int		amb_light;
	double	ratio;
	t_color	color;
}	t_amb_light;

typedef struct s_camera
{
	int				camera;
	t_coordinates	point;
	t_coordinates	vector;
	double			fov;
}	t_camera;

typedef struct s_light
{
	int				light;
	t_coordinates	point;
	double			brightness;
	t_color			color;
}	t_light;

typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_sphere
{
	t_coordinates	point;
	double			diameter;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	t_coordinates	point;
	t_coordinates	vector;
	t_color			color;
}	t_plane;

typedef struct s_cylinder
{
	t_coordinates	point;
	t_coordinates	vector;
	double			diameter;
	double			height;
	t_color			color;
}	t_cylinder;

typedef struct s_ray
{
	t_coordinates	point;
	t_coordinates	vector;
}	t_ray;

typedef struct s_discriminant
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	t_coordinates	vector;
}	t_discriminant;

typedef struct s_intersection
{
	int				type;
	int				count;
	double			t[100];
	t_coordinates	hit_point[100];
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
}	t_intersection;

typedef struct s_intersections
{
	int						type;
	double					t;
	t_coordinates			hit_point;
	t_sphere				*sphere;
	t_plane					*plane;
	t_cylinder				*cylinder;
	t_ray					ray;
	t_color					color;
	int						position_camera;
	struct s_intersections	*next;
}	t_intersections;

typedef struct s_render
{
	t_mlx			*mlx;
	t_mlx_image		*image;
	double			half_wall;
	double			half_width;
	double			half_height;
	double			pixel_size;
	double			**transformation;
	double			**inverse;
}	t_render;

typedef struct s_rt
{
	t_render		render;
	char			**elements;
	char			**element;
	char			**coordinates;
	char			**color;
	t_amb_light		amb_light;
	t_camera		camera;
	t_light			light;
	int				num_sp;
	int				num_pl;
	int				num_cy;
	t_material		material;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	double			**matrix;
	double			**identity;
	t_intersections	*intersections;
	t_intersections	*hit;
}	t_rt;

// matrices folder
// comparison_matrices.c functions
int				matrix_length(double **matrix);
int				are_equals_matrices(double **A, double **B);

// create_matrix.c functions
double			**create_matrix(int size);
double			**create_identity_matrix(int size);
double			**transpose_matrix(double **matrix);
double			**invert_matrix(double **matrix);

// determinant.c function
double			**copy_submatrix(double **matrix, int size, int i, int j);
double			calculate_determinant(double **matrix);
double			**calculate_cofactor_matrix(double **matrix);

// operations_matrices.c functions
double			**multiply_matrices(double **A, double **B);
t_coordinates	multiply_matrix_tuple(double **A, t_coordinates t);
double			**multiply_matrix_by_scalar(double scalar, double **matrix);

// transformations_matrices.c functions
double			**create_translation_matrix(t_coordinates tuple);
double			**create_scaling_matrix(t_coordinates tuple);
double			**create_rotation_matrix(int axis, double angle);
double			**create_shearing_matrix(double proportions[6]);

// parser folder
// parser.c function
void			parser(t_rt *rt);

// set_data.c functions
void			set_coordinates(t_coordinates *dest, char **src, double w);
void			set_color(t_color *dest, char **src);

// validate_data.c functions
int				validate_color(char **color);
int				validate_coordinates(char **coordinates);
int				validate_normalized_vector(t_coordinates coordinates);
int				validate_angle(char *angle);

// validate_elements.c functions
void			validate_amb_light(t_rt *rt);
void			validate_camera(t_rt *rt);
void			validate_light(t_rt *rt);

// validate_numbers.c functions
int				validate_double(char *number);
int				validate_int(char *number);

// validate_objects.c functions
void			validate_sphere(t_rt *rt, int sp);
void			validate_plane(t_rt *rt, int pl);
void			validate_cylinder(t_rt *rt, int cy);

// ray_casting folder
// intersection_ray_object.c functions
t_intersection	calculate_ray_sphere_intersections(t_ray ray, t_sphere *sphere);

// intersections.c functions
void			add_intersection(t_intersections **intersections, \
					t_intersection new);
void			intersections(t_rt *rt, t_ray ray);
t_intersections	*get_hit(t_intersections *intersections);

// list_utils.c functions
t_intersections	*new_intersection(t_intersection new, \
					int i, int position_camera);
void			intersections_list_add(t_intersections **intersections, \
					t_intersections *new);
void			free_intersections(t_intersections **intersections);

// normal_reflecting.c functions
t_coordinates	calculate_sphere_normal(t_intersections *hit);
t_coordinates	calculate_reflecting_vector(t_coordinates light, \
					t_coordinates normal);

// ray_utils.c functions
t_ray			create_ray(t_rt *rt, double x, double y);
t_coordinates	calculate_ray_position(t_ray ray, double t);
t_discriminant	calculate_discriminant_ray_sphere(t_ray ray, t_sphere *sphere);
t_ray			transform_ray(t_ray ray, double **matrix);

// render folder
// lightning.c functions
t_color			lightning(t_rt *rt);

// render.c functions
double			**transform_view(t_rt *rt, t_coordinates up);
void			render(t_rt *rt);

// tuples folder
// color_operations.c functions
t_color			add_colors(t_color a, t_color b);
t_color			subtract_colors(t_color a, t_color b);
t_color			multiply_color_by_scalar(double scalar, t_color a);
t_color			multiply_colors(t_color a, t_color b);

// comparison.c functions
int				are_equals(double a, double b);
int				are_equals_tuples(t_coordinates a, t_coordinates b);

// create.c functions
t_coordinates	create_point(double x, double y, double z);
t_coordinates	create_vector(double x, double y, double z);

// operations.c functions
t_coordinates	add_tuples(t_coordinates a, t_coordinates b);
t_coordinates	subtract_tuples(t_coordinates a, t_coordinates b);
t_coordinates	negate_tuple(t_coordinates a);
t_coordinates	multiply_tuple(double scalar, t_coordinates a);
t_coordinates	divide_tuple(double scalar, t_coordinates a);

// vector_operations.c functions
double			calculate_vector_magnitude(t_coordinates v);
t_coordinates	normalize_vector(t_coordinates v);
double			calculate_dot_product(t_coordinates v, t_coordinates u);
t_coordinates	calculate_cross_product(t_coordinates v, t_coordinates u);

// utils folder
// error.c functions
void			print_error(char *error, t_rt *rt);

// free.c functions
void			free_ptrptr(char ***ptrptr);
void			free_matrix(double ***matrix);

#endif