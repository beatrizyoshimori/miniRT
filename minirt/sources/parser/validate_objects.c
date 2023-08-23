/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:40:16 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/23 19:58:45 by byoshimo         ###   ########.fr       */
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

