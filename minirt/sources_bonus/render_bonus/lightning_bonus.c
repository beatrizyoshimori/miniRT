/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:49:38 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/30 19:50:50 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_color	calculate_diffuse_specular(t_rt *rt, \
					t_color effective_color, int i)
{
	double			light_dot_normal;
	double			reflect_dot_eye;
	t_color			aux_color;
	t_coordinates	light_vector;
	t_coordinates	reflect_vector;

	aux_color = (t_color){0, 0, 0};
	light_vector = normalize_vector(subtract_tuples(rt->lights[i].point, \
		rt->hit->hit_point));
	light_dot_normal = calculate_dot_product(light_vector, rt->hit->normal);
	if (light_dot_normal >= 0)
	{
		aux_color = multiply_color_by_scalar(rt->material.diffuse \
			* light_dot_normal, effective_color);
		reflect_vector = calculate_reflecting_vector \
			(negate_tuple(light_vector), rt->hit->normal);
		reflect_dot_eye = calculate_dot_product(reflect_vector, \
			rt->hit->eye_vector);
		if (reflect_dot_eye > 0)
			aux_color = add_colors(aux_color, \
				multiply_color_by_scalar(rt->lights[i].brightness \
				* rt->material.specular * pow(reflect_dot_eye, \
				rt->material.shininess), rt->lights[i].color));
	}
	return (aux_color);
}

static int	is_shadowed(t_rt *rt, int i)
{
	double			distance;
	t_coordinates	vector;
	t_coordinates	over_point;
	t_ray			ray;
	t_intersections	*hit;

	over_point = add_tuples(rt->hit->hit_point, \
		multiply_tuple(EPSILON, rt->hit->normal));
	vector = subtract_tuples(rt->lights[i].point, over_point);
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

static t_color	get_object_color(t_rt *rt)
{
	t_color	color;

	if (rt->hit->type == SP)
		color = rt->hit->sphere->color;
	else if (rt->hit->type == PL)
	{
		color = rt->hit->plane->color;
		if (color.red == CB)
		{
			rt->hit->o_point = multiply_matrix_tuple(rt->hit->plane->inverse, \
				rt->hit->hit_point);
			rt->hit->o_point.y = 0;
		}
	}
	else if (rt->hit->type == CY)
		color = rt->hit->cylinder->color;
	else
		color = rt->hit->cone->color;
	if (color.red == CB)
		color = draw_checkerboard(rt->hit);
	else if (color.red == EARTH || color.red == MOON)
		color = draw_texture(rt->hit);
	return (color);
}

t_color	lightning(t_rt *rt)
{
	int				i;
	t_color			effective_color;
	t_color			obj_color;
	t_color			color;
	t_color			aux_color;

	color = (t_color){0, 0, 0};
	obj_color = get_object_color(rt);
	i = -1;
	while (++i < rt->num_lights)
	{
		aux_color = (t_color){0, 0, 0};
		effective_color = multiply_colors(obj_color, \
			multiply_color_by_scalar(rt->lights[i].brightness, \
			rt->lights[i].color));
		aux_color = add_colors(multiply_color_by_scalar(rt->material.ambient, \
			effective_color), multiply_colors(obj_color, \
			multiply_color_by_scalar(rt->amb_light.ratio, \
			rt->amb_light.color)));
		if (!is_shadowed(rt, i))
			aux_color = add_colors(aux_color, \
				calculate_diffuse_specular(rt, effective_color, i));
		color = add_colors(aux_color, color);
	}
	return (color);
}
