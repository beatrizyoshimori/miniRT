/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:45:36 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/11 20:05:51 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_rt *rt, double x, double y)
{
	t_coordinates	point;
	t_coordinates	vector;

	point = create_point(x, y, -1);
	vector = rt->camera.vector;
	return ((t_ray){point, vector});
}

t_coordinates	calculate_ray_position(t_ray ray, double t)
{
	return (add_tuples(ray.point, multiply_tuple(t, ray.vector)));
}

t_ray	transform_ray(t_ray ray, double **matrix)
{
	t_ray	transformed_ray;

	transformed_ray.point = multiply_matrix_tuple(matrix, ray.point);
	transformed_ray.vector = multiply_matrix_tuple(matrix, ray.vector);
	return (transformed_ray);
}
