/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray_sphere_plane.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:11:39 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/26 16:05:35 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	calculate_ray_sphere_intersections(t_ray ray_in, \
					t_sphere *sphere)
{
	t_intersection	inter;
	t_discriminant	disc;
	t_ray			ray;

	ray = transform_ray(ray_in, sphere->inverse);
	inter = (t_intersection){SP, 0, .sphere = sphere};
	disc = calculate_discriminant_ray_sphere(ray);
	if (disc.discriminant < 0)
		return (inter);
	if (disc.discriminant == 0)
	{
		inter.count = 1;
		inter.t[0] = disc.t[0];
		inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
	}
	else
	{
		inter.count = 2;
		inter.t[0] = disc.t[0];
		inter.t[1] = disc.t[1];
		inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
		inter.hit_point[1] = calculate_ray_position(ray_in, inter.t[1]);
	}
	return (inter);
}

t_intersection	calculate_ray_plane_intersections(t_ray ray_in, \
					t_plane *plane)
{
	t_intersection	inter;
	t_ray			ray;

	ray = transform_ray(ray_in, plane->inverse);
	inter = (t_intersection){PL, 0, .plane = plane};
	if (are_equals(ray.vector.y, 0))
		return (inter);
	inter.count = 1;
	inter.t[0] = -ray.point.y / ray.vector.y;
	inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
	return (inter);
}