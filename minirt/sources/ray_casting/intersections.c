/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:41:48 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/15 19:58:17 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	add_intersection(t_ray ray, t_intersections **intersections, \
			t_intersection new)
{
	int	i;

	i = 0;
	while (i < new.count)
	{
		intersections_list_add(intersections, \
			new_intersection(new, i, ray));
		i++;
	}
}

void	intersections(t_rt *rt, t_ray ray, t_intersections **intersections)
{
	int				i;
	t_intersection	inter;

	i = 0;
	while (i < rt->num_sp)
	{
		inter = calculate_ray_sphere_intersections(ray, &rt->spheres[i]);
		if (inter.count)
			add_intersection(ray, intersections, inter);
		i++;
	}
	i = 0;
	while (i < rt->num_cy)
	{
		inter = calculate_ray_cylinder_intersections(ray, &rt->cylinders[i]);
		if (inter.count)
			add_intersection(ray, intersections, inter);
		i++;
	}
}

t_intersections	*get_hit(t_intersections *intersections)
{
	while (intersections)
	{
		if (intersections->t > 0)
			break ;
		intersections = intersections->next;
	}
	return (intersections);
}
