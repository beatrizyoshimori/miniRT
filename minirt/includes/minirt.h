/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:02:11 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/19 20:20:57 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

# define EPSILON 0.0001
# define FREE 0
# define NO_FREE 1

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_coordinates;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_amb_light
{
	double	ratio;
	t_rgb	color;
}	t_amb_light;

typedef struct s_camera
{
	t_coordinates	point;
	t_coordinates	vector;
	double			fov;
}	t_camera;

typedef struct s_light
{
	t_coordinates	point;
	double			brightness;
	t_rgb			color;
}	t_light;

typedef struct s_sphere
{
	t_coordinates	center;
	double			diameter;
	t_rgb			color;
}	t_sphere;

typedef struct s_plane
{
	t_coordinates	point;
	t_coordinates	normal;
	t_rgb			color;
}	t_plane;

typedef struct s_cylinder
{
	t_coordinates	center;
	t_coordinates	vector;
	double			diameter;
	double			height;
	t_rgb			color;
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

// utils folder
// error.c function
void	free_ptrptr(char **ptrptr);
void	print_error(char *error, int f, t_rt *rt);

int		validate_double(char *number);
int		validate_int(char *color);
int		validate_color(char **color);
void	validate_amb_light(t_rt *rt);

#endif