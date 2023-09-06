/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:45:36 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/05 22:05:56 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	calculate_ray_position(t_ray ray, double t)
{
	return (add_tuples(ray.point, multiply_tuple(t, ray.vector)));
}

double	calculate_discriminant(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}
