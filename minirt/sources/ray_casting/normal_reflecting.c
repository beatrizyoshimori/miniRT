/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_reflecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:02:29 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/11 20:12:40 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	calculate_normal(t_intersections *hit)
{
	t_coordinates	vector;

	if (hit->type == SP)
		vector = subtract_tuples(hit->hit_point, hit->sphere->point);
	else if (hit->type == CY)
		vector = subtract_tuples(hit->hit_point, hit->cylinder->point);
	vector.w = 0;
	return (normalize_vector(vector));
}

t_coordinates	calculate_reflecting_vector(t_coordinates light, \
	t_coordinates normal)
{
	return (subtract_tuples(light, \
		multiply_tuple(2 * calculate_dot_product(light, normal), normal)));
}
