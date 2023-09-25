/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_reflecting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:02:29 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/25 14:07:58 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_normal(t_intersections *hit)
{
	t_coordinates	o_point;
	t_coordinates	o_normal;
	t_coordinates	w_normal;

	if (hit->type == SP)
	{
		o_point = multiply_matrix_tuple(hit->sphere->inverse, hit->hit_point);
		o_normal = subtract_tuples(o_point, create_point(0, 0, 0));
		w_normal = multiply_matrix_tuple(hit->sphere->transpose, o_normal);
	}
	else if (hit->type == PL)
		w_normal = hit->plane->vector;
	else if (hit->type == CY)
	{
		o_point = multiply_matrix_tuple(hit->cylinder->inverse, hit->hit_point);
		o_normal = subtract_tuples(o_point, create_point(0, o_point.y, 0));
		w_normal = multiply_matrix_tuple(hit->cylinder->transpose, o_normal);
	}
	w_normal.w = 0;
	hit->normal = normalize_vector(w_normal);
}

t_coordinates	calculate_reflecting_vector(t_coordinates light, \
					t_coordinates normal)
{
	return (subtract_tuples(light, \
		multiply_tuple(2 * calculate_dot_product(light, normal), normal)));
}
