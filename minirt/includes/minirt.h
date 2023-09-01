/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:02:11 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/01 16:28:31 by lucade-s         ###   ########.fr       */
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
# define HEIGHT 400
# define WIDTH 400
# define VECTOR 0
# define POINT 1

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

typedef struct s_rt
{
	char		**elements;
	char		**element;
	char		**coordinates;
	char		**color;
	t_amb_light	amb_light;
	t_camera	camera;
	t_light		light;
	int			num_sp;
	int			num_pl;
	int			num_cy;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_rt;

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

// utils folder
// create.c functions
t_coordinates	create_point(double x, double y, double z);
t_coordinates	create_vector(double x, double y, double z);

// equal.c functions
int				are_equals(double a, double b);
int				are_equals_tuples(t_coordinates a, t_coordinates b);

// error.c functions
void			free_ptrptr(char ***ptrptr);
void			print_error(char *error, t_rt *rt);

// operations.c functions
t_coordinates	add_tuples(t_coordinates a, t_coordinates b);
t_coordinates	subtract_tuples(t_coordinates a, t_coordinates b);
t_coordinates	negate_tuple(t_coordinates a);
t_coordinates	multiply_tuple(double scalar, t_coordinates a);
t_coordinates	divide_tuple(double scalar, t_coordinates a);

// vector_operations.c functions
double			get_vector_magnitude(t_coordinates v);
t_coordinates	normalize_vector(t_coordinates v);
double			get_dot_product(t_coordinates v, t_coordinates u);
t_coordinates	get_cross_product(t_coordinates v, t_coordinates u);

#endif