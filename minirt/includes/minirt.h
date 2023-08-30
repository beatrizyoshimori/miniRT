/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:02:11 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/30 18:34:33 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define EPSILON 0.0001
# define FREE 0
# define NO_FREE 1
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
void	parser(t_rt *rt);

// set_data.c functions
void	set_coordinates(t_coordinates *dest, char **src, double w);
void	set_color(t_color *dest, char **src);

// validate_data.c functions
int		validate_color(char **color);
int		validate_coordinates(char **coordinates);
int		validate_normalized_vector(t_coordinates coordinates);
int		validate_angle(char *angle);

// validate_elements.c functions
void	validate_amb_light(t_rt *rt);
void	validate_camera(t_rt *rt);
void	validate_light(t_rt *rt);

// validate_numbers.c functions
int		validate_double(char *number);
int		validate_int(char *number);

// validate_objects.c functions
void	validate_sphere(t_rt *rt, int sp);
void	validate_plane(t_rt *rt, int pl);
void	validate_cylinder(t_rt *rt, int cy);

// utils folder
// error.c function
void	free_ptrptr(char ***ptrptr);
void	print_error(char *error, int f, t_rt *rt);

int		validate_double(char *number);
int		validate_int(char *color);
int		validate_color(char **color);
void	validate_amb_light(t_rt *rt);
int		validate_coordinates(char **coordinates);

#endif