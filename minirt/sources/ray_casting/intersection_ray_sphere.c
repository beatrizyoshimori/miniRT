/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray_sphere.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:11:39 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/05 22:05:36 by lucade-s         ###   ########.fr       */
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
	c = calculate_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = calculate_discriminant(a, b, c);
	return ((t_intersection){SP, -(b * sqrt(discriminant)) / (2 * a), \
		(-b * sqrt(discriminant)) / (2 * a)});
}
