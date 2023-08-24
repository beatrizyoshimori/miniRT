/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:40:16 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/23 21:01:37 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_sphere(t_rt *rt, int sp)
{
	if (rt->element[4])
		print_error("Invalid number of arguments on sphere.", FREE, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid sphere center coordinates.", FREE, rt);
	set_coordinates(&rt->spheres[sp].center, rt->coordinates);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->element[2]))
		print_error("Invalid sphere diameter. Diameter is not a double.", \
			FREE, rt);
	rt->spheres[sp].diameter = ft_atod(rt->element[2]);
	if (rt->spheres[sp].diameter <= 0)
		print_error("Invalid sphere diameter. \
			Diameter must be greater than 0.", FREE, rt);
	rt->color = ft_split(rt->element[3], ',');
	if (!validate_color(rt->color))
		print_error("Invalid sphere color.", FREE, rt);
	set_color(&rt->spheres[sp].color, rt->color);
	free_ptrptr(&rt->color);
}

void	validate_plane(t_rt *rt, int pl)
{
	if (rt->element[4])
		print_error("Invalid number of arguments on plane.", FREE, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid plane point.", FREE, rt);
	set_coordinates(&rt->planes[pl].point, rt->coordinates);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->element[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid plane normal.", FREE, rt);
	set_coordinates(&rt->planes[pl].normal, rt->coordinates);
	if (!validate_normalized_vector(rt->planes[pl].normal))
		print_error("Invalid plane normal. Normal is not normalized.", \
			FREE, rt);
	free_ptrptr(&rt->coordinates);
	rt->color = ft_split(rt->element[3], ',');
	if (!validate_color(rt->color))
		print_error("Invalid plane color.", FREE, rt);
	set_color(&rt->planes[pl].color, rt->color);
	free_ptrptr(&rt->color);
}

static void	validate_cylinder_aux(t_rt *rt, int cy)
{
	if (!validate_double(rt->element[4]))
		print_error("Invalid cylinder height. Height is not a double.", \
			FREE, rt);
	rt->cylinders[cy].height = ft_atod(rt->element[4]);
	if (rt->cylinders[cy].height <= 0)
		print_error("Invalid cylinder height. \
			Height must be greater than 0.", FREE, rt);
	rt->color = ft_split(rt->element[5], ',');
	if (!validate_color(rt->color))
		print_error("Invalid cylinder color.", FREE, rt);
	set_color(&rt->cylinders[cy].color, rt->color);
	free_ptrptr(&rt->color);
}

void	validate_cylinder(t_rt *rt, int cy)
{
	if (rt->element[6])
		print_error("Invalid number of arguments on cylinder.", FREE, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid cylinder center coordinates.", FREE, rt);
	set_coordinates(&rt->cylinders[cy].center, rt->coordinates);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->element[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid cylinder vector.", FREE, rt);
	set_coordinates(&rt->cylinders[cy].vector, rt->coordinates);
	if (!validate_normalized_vector(rt->cylinders[cy].vector))
		print_error("Invalid cylinder vector. Vector is not normalized.", \
			FREE, rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->element[3]))
		print_error("Invalid cylinder diameter. Diameter is not a double.", \
			FREE, rt);
	rt->cylinders[cy].diameter = ft_atod(rt->element[3]);
	if (rt->cylinders[cy].diameter <= 0)
		print_error("Invalid cylinder diameter. \
			Diameter must be greater than 0.", FREE, rt);
	validate_cylinder_aux(rt, cy);
}
