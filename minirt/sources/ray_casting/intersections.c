/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:41:48 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/11 20:16:48 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_position_camera(double t[100], int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (t[i] < 0 && t[i + 1] > 0)
			return (INSIDE);
		i++;
	}
	return (OUTSIDE);
}

void	add_intersection(t_intersections **intersections, t_intersection new)
{
	int		i;
	int		position_camera;

	i = 0;
	while (i < new.count)
	{
		position_camera = check_position_camera(new.t, new.count);
		intersections_list_add(intersections, \
			new_intersection(new, i, position_camera));
		i++;
	}
}

void	intersections(t_rt *rt, t_ray ray, t_intersections **intersections)
{
	int				i;
	t_intersection	intersection;

	i = 0;
	while (i < rt->num_sp)
	{
		intersection = calculate_ray_sphere_intersections(ray, &rt->spheres[i]);
		if (intersection.count)
			add_intersection(intersections, intersection);
		i++;
	}
	i = 0;
	while (i < rt->num_cy)
	{
		intersection = calculate_ray_cylinder_intersections(ray, &rt->cylinders[i]);
		if (intersection.count)
			add_intersection(intersections, intersection);
		i++;
	}
}

t_intersections	*get_hit(t_intersections *intersections)
{
	while (intersections)
	{
		if (intersections->t >= 0)
			break ;
		intersections = intersections->next;
	}
	return (intersections);
}
