/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray_sphere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:11:39 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/08 11:24:10 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	calculate_ray_sphere_intersections(t_ray ray, t_sphere sphere)
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	t_coordinates	sphere_to_ray;

	sphere_to_ray = subtract_tuples(ray.point, sphere.point);
	a = calculate_dot_product(ray.vector, ray.vector);
	b = 2 * calculate_dot_product(ray.vector, sphere_to_ray);
	c = calculate_dot_product(sphere_to_ray, sphere_to_ray) \
		- pow(sphere.diameter / 2, 2);
	discriminant = calculate_discriminant(a, b, c);
	if (discriminant < 0)
		return ((t_intersection){SP, 0, .t = {0}});
	if (discriminant == 0)
		return ((t_intersection){SP, 1, .color = sphere.color, \
			.t[0] = (-b - sqrt(discriminant)) / (2 * a)});
	return ((t_intersection){SP, 2, .color = sphere.color, \
		.t[0] = (-b - sqrt(discriminant)) / (2 * a), \
		.t[1] = (-b + sqrt(discriminant)) / (2 * a)});
}
