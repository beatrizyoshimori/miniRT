/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:49:38 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/08 20:52:01 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	lightning(t_rt *rt, t_intersections *hit)
{
	t_color			effective_color;
	t_coordinates	light_vector;
	t_color			ambient;
	double			light_dot_normal;
	t_coordinates	normal_vector;
	t_color			diffuse;
	t_color			specular;
	t_coordinates	reflect_vector;
	t_coordinates	eye_vector;
	double			reflect_dot_eye;
	double			factor;
	double			scalar;

	diffuse = (t_color){0};
	specular = (t_color){0};
	factor = 0;
	scalar = 0;
	effective_color = multiply_colors(multiply_color_by_scalar(rt->light.brightness, rt->light.color), hit->sphere->color);
	light_vector = normalize_vector(subtract_tuples(rt->light.point, hit->hit_point));
	ambient = multiply_color_by_scalar(rt->material.ambient, effective_color);
	normal_vector = calculate_sphere_normal(hit);
	light_dot_normal = calculate_dot_product(light_vector, normal_vector);
	if (light_dot_normal < 0)
	{
		diffuse = (t_color){0, 0, 0};
		specular = (t_color){0, 0, 0};
	}
	else
	{
		scalar = rt->material.diffuse * light_dot_normal;
		if (scalar > 1)
			scalar = 1;
		diffuse = multiply_color_by_scalar(scalar, effective_color);
		reflect_vector = calculate_reflecting_vector(negate_tuple(light_vector), normal_vector);
		eye_vector = (t_coordinates){0, 0, -1, 0};
		reflect_dot_eye = calculate_dot_product(reflect_vector, eye_vector);
		if (reflect_dot_eye <= 0)
			specular = (t_color){0, 0, 0};
		else
		{
			factor = pow(reflect_dot_eye, rt->material.shininess);
			scalar = rt->light.brightness * rt->material.specular * factor;
			if (scalar > 1)
				scalar = 1;
			specular = multiply_color_by_scalar(scalar, rt->light.color);
		}
	}
	return (add_colors(diffuse, add_colors(ambient, specular)));
}
