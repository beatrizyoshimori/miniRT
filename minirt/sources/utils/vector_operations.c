/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 20:48:55 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/30 21:58:44 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_vector_magnitude(t_coordinates v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2)));
}

t_coordinates	normalize_vector(t_coordinates v)
{
	return (divide_tuple(get_vector_magnitude(v), v));
}

double	get_dot_product(t_coordinates v, t_coordinates u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z + v.w * u.w);
}

t_coordinates	get_cross_product(t_coordinates v, t_coordinates u)
{
	return ((t_coordinates){v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, \
		v.x * u.y - v.y * u.x, 0});
}
