/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:11:39 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/11 20:04:26 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	calculate_ray_sphere_intersections(t_ray ray, t_sphere *sphere)
{
	t_intersection	inter;
	t_discriminant	disc;

	inter = (t_intersection){SP, 0, .sphere = sphere};
	disc = calculate_discriminant_ray_sphere(ray, sphere);
	if (disc.discriminant < 0)
		return (inter);
	if (disc.discriminant == 0)
	{
		inter.count = 1;
		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
		inter.hit_point[0] = calculate_ray_position(ray, inter.t[0]);
	}
	else
	{
		inter.count = 2;
		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
		inter.t[1] = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
		inter.hit_point[0] = calculate_ray_position(ray, inter.t[0]);
		inter.hit_point[1] = calculate_ray_position(ray, inter.t[1]);
	}
	return (inter);
}

t_intersection	calculate_ray_cylinder_intersections(t_ray ray, t_cylinder *cylinder)
{
	t_intersection	inter;
	t_discriminant	disc;

	inter = (t_intersection){CY, 0, .cylinder = cylinder};
	disc = calculate_discriminant_ray_cylinder(ray, cylinder);
	if (disc.discriminant < 0)
		return (inter);
	if (disc.discriminant == 0)
	{
		inter.count = 1;
		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
		inter.hit_point[0] = calculate_ray_position(ray, inter.t[0]);
	}
	else
	{
		inter.count = 2;
		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
		inter.t[1] = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
		inter.hit_point[0] = calculate_ray_position(ray, inter.t[0]);
		inter.hit_point[1] = calculate_ray_position(ray, inter.t[1]);
	}
	return (inter);
}