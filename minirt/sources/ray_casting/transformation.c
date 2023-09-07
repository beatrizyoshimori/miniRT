/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:40:03 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/07 13:48:34 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	transform_ray(t_ray ray, double **matrix)
{
	t_ray	transformed_ray;

	transformed_ray.point = multiply_matrix_tuple(matrix, ray.point);
	transformed_ray.vector = multiply_matrix_tuple(matrix, ray.vector);
	return (transformed_ray);
}
