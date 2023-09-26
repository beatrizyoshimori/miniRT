/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_ray_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:56:08 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/26 16:17:28 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	int				i;
	double			y;
	t_intersection	inter;
	t_discriminant	disc;
	t_ray			ray;

	ray = transform_ray(ray_in, cylinder->inverse);
	inter = (t_intersection){CY, 0, .cylinder = cylinder};
	disc = calculate_discriminant_ray_cylinder(ray);
	if (disc.discriminant >= 0)
	{
		i = -1;
		while (++i < 2)
		{
			y = ray.point.y + disc.t[i] * ray.vector.y;
			if (y > cylinder->min && y < cylinder->max)
			{
				inter.t[inter.count] = disc.t[i];
				inter.hit_point[inter.count++] \
					= calculate_ray_position(ray_in, inter.t[i]);
			}
		}
	}
	calculate_intersect_caps(ray_in, ray, cylinder, &inter);
	return (inter);
}
