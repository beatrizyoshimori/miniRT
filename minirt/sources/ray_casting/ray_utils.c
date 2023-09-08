/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:45:36 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/08 18:14:38 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	calculate_ray_position(t_ray ray, double t)
{
	return (add_tuples(ray.point, multiply_tuple(t, ray.vector)));
}

double	calculate_discriminant_ray_sphere(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

// t_discriminant	*calculate_discriminant_ray_sphere(t_ray ray, t_sphere *sphere)
// {
// 	t_discriminant	*discriminant;

// 	discriminant = NULL;
// 	discriminant = (t_discriminant *)ft_calloc(1, sizeof(t_discriminant));
// 	discriminant->sphere_to_ray = subtract_tuples(ray.point, sphere->point);
// 	discriminant->a = calculate_dot_product(ray.vector, ray.vector);
// 	discriminant->b = 2 * calculate_dot_product(ray.vector, \
// 		discriminant->sphere_to_ray);
// 	discriminant->c = calculate_dot_product(discriminant->sphere_to_ray, \
// 		discriminant->sphere_to_ray) - pow(sphere->diameter / 2, 2);
// 	return (discriminant);
// }