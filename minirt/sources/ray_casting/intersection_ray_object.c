/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:11:39 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/08 18:15:24 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	calculate_ray_sphere_intersections(t_ray ray, t_sphere *sphere)
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
	t_coordinates	sphere_to_ray;
	t_intersection	intersection;

	intersection = (t_intersection){SP, 0, .sphere = sphere};
	sphere_to_ray = subtract_tuples(ray.point, sphere->point);
	a = calculate_dot_product(ray.vector, ray.vector);
	b = 2 * calculate_dot_product(ray.vector, sphere_to_ray);
	c = calculate_dot_product(sphere_to_ray, sphere_to_ray) \
		- pow(sphere->diameter / 2, 2);
	discriminant = calculate_discriminant_ray_sphere(a, b, c);
	if (discriminant < 0)
		return (intersection);
	if (discriminant == 0)
	{
		intersection.count = 1;
		intersection.t[0] = (-b - sqrt(discriminant)) / (2 * a);
		intersection.hit_point[0] = calculate_ray_position(ray, intersection.t[0]);
	}
	else
	{
		intersection.count = 2;
		intersection.t[0] = (-b - sqrt(discriminant)) / (2 * a);
		intersection.t[1] = (-b + sqrt(discriminant)) / (2 * a);
		intersection.hit_point[0] = calculate_ray_position(ray, intersection.t[0]);
		intersection.hit_point[1] = calculate_ray_position(ray, intersection.t[1]);
	}
	return (intersection);
}

// t_intersection	calculate_ray_sphere_intersections(t_ray ray, t_sphere *sphere)
// {
// 	t_discriminant	*discriminant;
// 	t_intersection	intersection;

// 	intersection = (t_intersection){SP, 0, .sphere = sphere};
// 	discriminant = calculate_discriminant_ray_sphere(ray, sphere);
// 	if (discriminant->discriminant < 0)
// 		return (intersection);
// 	if (discriminant->discriminant == 0)
// 	{
// 		intersection.count = 1;
// 		intersection.t[0] = (-discriminant->b - sqrt(discriminant->discriminant)) / (2 * discriminant->a);
// 		intersection.hit_point[0] = calculate_ray_position(ray, intersection.t[0]);
// 	}
// 	else
// 	{
// 		intersection.count = 2;
// 		intersection.t[0] = (-discriminant->b - sqrt(discriminant->discriminant)) / (2 * discriminant->a);
// 		intersection.t[1] = (-discriminant->b + sqrt(discriminant->discriminant)) / (2 * discriminant->a);
// 		intersection.hit_point[0] = calculate_ray_position(ray, intersection.t[0]);
// 		intersection.hit_point[1] = calculate_ray_position(ray, intersection.t[1]);
// 	}
// 	return (intersection);
// }