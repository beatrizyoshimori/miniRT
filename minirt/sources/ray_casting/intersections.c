/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:41:48 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/08 16:52:41 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_intersection(t_intersections **intersections, t_intersection new)
{
	int		i;
	void	*object;

	i = 0;
	while (i < new.count)
	{
		if (new.type == SP)
			object = (void *)new.sphere;
		else if (new.type == PL)
			object = (void *)new.plane;
		else
			object = (void *)new.cylinder;
		intersections_list_add(intersections, \
			new_intersection(new.type, new.t[i], new.hit_point[i], object));
		i++;
	}
}

void	intersections(t_rt *rt, t_ray ray)
{
	int				i;
	t_intersection	intersection;

	i = 0;
	while (i < rt->num_sp)
	{
		intersection = calculate_ray_sphere_intersections(ray, &rt->spheres[i]);
		if (intersection.count)
			add_intersection(&rt->intersections, intersection);
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
