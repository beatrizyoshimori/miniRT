/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_reflecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:02:29 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/08 18:22:27 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	calculate_sphere_normal(t_intersections *hit)
{
	t_coordinates	vector;

	vector = subtract_tuples(hit->hit_point, hit->sphere->point);
	vector.w = 0;
	return (normalize_vector(vector));
}

t_coordinates	calculate_reflecting_vector(t_coordinates light, \
	t_coordinates normal)
{
	return (subtract_tuples(light, \
		multiply_tuple(2 * calculate_dot_product(light, normal), normal)));
}
