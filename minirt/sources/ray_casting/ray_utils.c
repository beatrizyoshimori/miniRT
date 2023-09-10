/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:45:36 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/09 23:19:53 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_rt *rt, double x, double y)
{
	double			world_x;
	double			world_y;
	t_coordinates	pixel;
	t_coordinates	origin;

	world_x = rt->render.half_width - x * rt->render.pixel_size;
	world_y = -rt->render.half_height + y * rt->render.pixel_size;
	pixel = multiply_matrix_tuple(rt->render.inverse, create_point(world_x, world_y, -1));
	origin = multiply_matrix_tuple(rt->render.inverse, create_point(0, 0, 0));
	return ((t_ray){origin, normalize_vector(subtract_tuples(pixel, origin))});
}

// t_ray	create_ray(t_rt *rt, double x, double y)
// {
// 	t_coordinates	point;
// 	t_coordinates	ray_origin;
// 	t_coordinates	vector;

// 	(void)rt;
// 	point = create_point(x, y, WALL_Z);
// 	ray_origin = rt->camera.point;
// 	vector = subtract_tuples(point, ray_origin);
// 	return ((t_ray){ray_origin, normalize_vector(vector)});
// }

t_coordinates	calculate_ray_position(t_ray ray, double t)
{
	return (add_tuples(ray.point, multiply_tuple(t, ray.vector)));
}

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

t_ray	transform_ray(t_ray ray, double **matrix)
{
	t_ray	transformed_ray;

	transformed_ray.point = multiply_matrix_tuple(matrix, ray.point);
	transformed_ray.vector = multiply_matrix_tuple(matrix, ray.vector);
	return (transformed_ray);
}
