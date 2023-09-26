/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:11:39 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/26 15:18:55 by lucade-s         ###   ########.fr       */
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
		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
		inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
	}
	else
	{
		inter.count = 2;
		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
		inter.t[1] = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
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

int	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;
	double	point;

	x = ray.point.x + t * ray.vector.x;
	z = ray.point.z + t * ray.vector.z;
	point = x * x + z * z;
	if (point <= 1)
		return (1);
	return (0);
}

void	calculate_intersect_caps(t_ray ray_in, t_ray ray, \
			t_cylinder *cylinder, t_intersection *inter)
{
	double	t;

	if (are_equals(ray.vector.y, 0))
		return ;
	t = (cylinder->min - ray.point.y) / ray.vector.y;
	if (check_cap(ray, t))
	{
		inter->hit_point[inter->count] = calculate_ray_position(ray_in, t);
		inter->t[inter->count] = t;
		inter->count++;
	}
	t = (cylinder->max - ray.point.y) / ray.vector.y;
	if (check_cap(ray, t))
	{
		inter->hit_point[inter->count] = calculate_ray_position(ray_in, t);
		inter->t[inter->count] = t;
		inter->count++;
	}
}

t_intersection	calculate_ray_cylinder_intersections(t_ray ray_in, \
					t_cylinder *cylinder)
{
	double			y;
	t_intersection	inter;
	t_discriminant	disc;
	t_ray			ray;

	ray = transform_ray(ray_in, cylinder->inverse);
	inter = (t_intersection){CY, 0, .cylinder = cylinder};
	disc = calculate_discriminant_ray_cylinder(ray);
	if (disc.discriminant >= 0)
	{
		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
		inter.t[1] = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
		y = ray.point.y + inter.t[0] * ray.vector.y;
		if (y > cylinder->min && y < cylinder->max)
		{
			inter.t[inter.count] = inter.t[0];
			inter.hit_point[inter.count++] = calculate_ray_position(ray_in, inter.t[0]);
		}
		y = ray.point.y + inter.t[1] * ray.vector.y;
		if (y > cylinder->min && y < cylinder->max)
		{
			inter.t[inter.count] = inter.t[1];
			inter.hit_point[inter.count++] = calculate_ray_position(ray_in, inter.t[1]);
		}
	}
	calculate_intersect_caps(ray_in, ray, cylinder, &inter);
	return (inter);
}

// t_intersection	calculate_ray_cylinder_intersections(t_ray ray_in, \
// 					t_cylinder *cylinder)
// {
// 	double			y;
// 	t_intersection	inter;
// 	t_discriminant	disc;
// 	t_ray			ray;

// 	ray = transform_ray(ray_in, cylinder->inverse);
// 	inter = (t_intersection){CY, 0, .cylinder = cylinder};
// 	disc = calculate_discriminant_ray_cylinder(ray);
// 	if (are_equals(disc.discriminant, 0))
// 	{
// 		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
// 		y = ray.point.y + inter.t[0] * ray.vector.y;
// 		if (y <= cylinder->min || y >= cylinder->max)
// 			return (inter);
// 		inter.count = 1;
// 		inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
// 	}
// 	else if (disc.discriminant > 0)
// 	{
// 		inter.t[0] = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
// 		inter.t[1] = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
// 		y = ray.point.y + inter.t[0] * ray.vector.y;
// 		if (y > cylinder->min && y < cylinder->max)
// 			inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
// 		else
// 		{
// 			inter.t[0] = (cylinder->min - ray.point.y) / ray.vector.y;
// 			if (check_cap(ray, inter.t[0]))
// 				inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
// 			else
// 			{
// 				inter.t[0] = (cylinder->max - ray.point.y) / ray.vector.y;
// 				if (check_cap(ray, inter.t[0]))
// 					inter.hit_point[0] = calculate_ray_position(ray_in, inter.t[0]);
// 			}
// 		}
// 		y = ray.point.y + inter.t[1] * ray.vector.y;
// 		if (y > cylinder->min && y < cylinder->max)
// 			inter.hit_point[1] = calculate_ray_position(ray_in, inter.t[1]);
// 		else
// 		{
// 			inter.t[1] = (cylinder->min - ray.point.y) / ray.vector.y;
// 			if (check_cap(ray, inter.t[1]))
// 				inter.hit_point[1] = calculate_ray_position(ray_in, inter.t[1]);
// 			else
// 			{
// 				inter.t[1] = (cylinder->max - ray.point.y) / ray.vector.y;
// 				if (check_cap(ray, inter.t[1]))
// 					inter.hit_point[1] = calculate_ray_position(ray_in, inter.t[1]);
// 			}
// 		}
// 		inter.count = 2;
// 	}
// 	return (inter);
// }
