/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminant.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:05:30 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/11 20:35:39 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_discriminant	calculate_discriminant_ray_sphere(t_ray ray, t_sphere *sphere)
{
	t_discriminant	discriminant;

	discriminant.vector = subtract_tuples(ray.point, sphere->point);
	discriminant.a = calculate_dot_product(ray.vector, ray.vector);
	discriminant.b = 2 * calculate_dot_product(ray.vector, \
		discriminant.vector);
	discriminant.c = calculate_dot_product(discriminant.vector, \
		discriminant.vector) - pow(sphere->diameter / 2, 2);
	discriminant.discriminant = discriminant.b * discriminant.b - 4 \
		* discriminant.a * discriminant.c;
	return (discriminant);
}

t_discriminant	calculate_discriminant_ray_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_discriminant	discriminant;

	discriminant.a = ray.vector.x * ray.vector.x + ray.vector.z * ray.vector.z;
	discriminant.b = 2 * (ray.point.x - cylinder->point.x) * ray.vector.x + 2 * (ray.point.z - cylinder->point.z) * ray.vector.z;
	discriminant.c = (ray.point.x - cylinder->point.x) * (ray.point.x - cylinder->point.x) + (ray.point.z - cylinder->point.z) * (ray.point.z - cylinder->point.z) - pow(cylinder->diameter / 2, 2);
	discriminant.discriminant = discriminant.b * discriminant.b - 4 \
		* discriminant.a * discriminant.c;
	return (discriminant);
}
