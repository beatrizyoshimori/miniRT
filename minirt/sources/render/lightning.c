/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:49:38 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/13 19:47:42 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	lightning(t_rt *rt)
{
	t_color			effective_color;
	t_coordinates	light_vector;
	t_color			obj_color;
	t_color			color;
	double			light_dot_normal;
	t_coordinates	reflect_vector;
	double			reflect_dot_eye;

	obj_color = (t_color){0, 0, 0};
	if (rt->hit->type == SP)
		obj_color = rt->hit->sphere->color;
	else if (rt->hit->type == CY)
		obj_color = rt->hit->cylinder->color;
	effective_color = multiply_colors(multiply_color_by_scalar(rt->light.brightness, rt->light.color), obj_color);
	light_vector = normalize_vector(subtract_tuples(rt->light.point, rt->hit->hit_point));
	color = multiply_color_by_scalar(rt->material.ambient, effective_color);
	if (is_shadowed(rt) && rt->light.brightness)
		return (add_colors(color, multiply_colors(obj_color, multiply_color_by_scalar(rt->amb_light.ratio, rt->amb_light.color))));
	light_dot_normal = calculate_dot_product(light_vector, rt->hit->normal);
	if (light_dot_normal >= 0)
	{
		color = add_colors(color, multiply_color_by_scalar(rt->material.diffuse * light_dot_normal, effective_color));
		reflect_vector = calculate_reflecting_vector(negate_tuple(light_vector), rt->hit->normal);
		reflect_dot_eye = calculate_dot_product(reflect_vector, rt->hit->eye_vector);
		if (reflect_dot_eye > 0)
			color = add_colors(color, multiply_color_by_scalar(rt->light.brightness * rt->material.specular * pow(reflect_dot_eye, rt->material.shininess), rt->light.color));
	}
	color = add_colors(color, multiply_colors(obj_color, multiply_color_by_scalar(rt->amb_light.ratio, rt->amb_light.color)));
	return (color);
}

int	is_shadowed(t_rt *rt)
{
	double			distance;
	t_coordinates	vector;
	t_coordinates	over_point;
	t_ray			ray;
	t_intersections	*hit;

	over_point = add_tuples(rt->hit->hit_point, multiply_tuple(EPSILON, rt->hit->normal));
	vector = subtract_tuples(rt->light.point, over_point);
	distance = calculate_vector_magnitude(vector);
	vector = normalize_vector(vector);
	ray = (t_ray){over_point, vector};
	intersections(rt, ray, &rt->shadows);
	hit = get_hit(rt->shadows);
	if (hit && hit->t < distance)
	{
		free_intersections(&rt->shadows);
		return (1);
	}
	free_intersections(&rt->shadows);
	return (0);
}
