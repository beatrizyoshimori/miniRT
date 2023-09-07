/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:41:48 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/07 16:30:51 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_intersection(t_intersections **intersections, t_intersection new)
{
	int	i;

	i = 0;
	while (i < new.count)
	{
		intersections_list_add(intersections, \
			new_intersection(new.object, new.t[i]));
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
		intersection = calculate_ray_sphere_intersections(ray, rt->spheres[i]);
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
