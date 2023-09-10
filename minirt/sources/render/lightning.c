/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:49:38 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/09 16:22:34 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	lightning(t_rt *rt)
{
	t_color			effective_color;
	t_coordinates	light_vector;
	t_color			color;
	double			light_dot_normal;
	t_coordinates	normal_vector;
	t_coordinates	reflect_vector;
	t_coordinates	eye_vector;
	double			reflect_dot_eye;

	effective_color = multiply_colors(multiply_color_by_scalar(rt->light.brightness, rt->light.color), rt->hit->sphere->color);
	light_vector = normalize_vector(subtract_tuples(rt->light.point, rt->hit->hit_point));
	color = multiply_color_by_scalar(rt->material.ambient, effective_color);
	normal_vector = calculate_sphere_normal(rt->hit);
	if (rt->hit->position_camera == INSIDE)
		normal_vector = negate_tuple(normal_vector);
	light_dot_normal = calculate_dot_product(light_vector, normal_vector);
	if (light_dot_normal >= 0)
	{
		color = add_colors(color, multiply_color_by_scalar(rt->material.diffuse * light_dot_normal, effective_color));
		reflect_vector = calculate_reflecting_vector(negate_tuple(light_vector), normal_vector);
		eye_vector = (negate_tuple(rt->hit->ray.vector));
		reflect_dot_eye = calculate_dot_product(reflect_vector, eye_vector);
		if (reflect_dot_eye > 0)
			color = add_colors(color, multiply_color_by_scalar(rt->light.brightness * rt->material.specular * pow(reflect_dot_eye, rt->material.shininess), rt->light.color));
	}
	color = add_colors(color, multiply_colors(rt->hit->sphere->color, multiply_color_by_scalar(rt->amb_light.ratio, rt->amb_light.color)));
	return (color);
}
