/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:21:50 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/22 22:11:21 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_amb_light(t_rt *rt)
{
	if (rt->element[3])
		print_error("Invalid number of arguments on ambient light.", FREE, rt);
	if (validate_double(rt->element[1]))
	{
		rt->amb_light.ratio = ft_atod(rt->element[1]);
		if (rt->amb_light.ratio < 0 || rt->amb_light.ratio > 1)
			print_error("Invalid ambient light ratio. Ratio: 0.0 - 1.0.", \
				FREE, rt);
	}
	else
		print_error("Invalid ambient light ratio. Ratio is not a double.", \
			FREE, rt);
	rt->color = ft_split(rt->element[2], ',');
	if (validate_color(rt->color))
		set_color(rt->amb_light.color, rt->color);
	else
		print_error("Invalid ambient light color.", FREE, rt);
	free_ptrptr(rt->color);
}

void	validate_camera(t_rt *rt)
{
	if (rt->element[4])
		print_error("Invalid number of arguments on camera.", FREE, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (validate_coordinates(rt->coordinates))
		set_coordinates(rt->camera.point, rt->coordinates);
	else
		print_error("Invalid camera point.", FREE, rt);
	free_ptrptr(rt->coordinates);
	rt->coordinates = ft_split(rt->element[2], ',');
	if (validate_coordinates(rt->coordinates))
	{
		set_coordinates(rt->camera.vector, rt->coordinates);
		if (!validate_normalized_vector(rt->camera.vector))
			print_error("Invalid camera vector. Vector is not normalized.", \
				FREE, rt);
	}
	else
		print_error("Invalid camera vector.", FREE, rt);
	free_ptrptr(rt->coordinates);
	if (validate_angle(rt->element[3]))
		rt->camera.fov = ft_atoi(rt->element[3]);
	else
		print_error("Invalid camera horizontal field of view.", FREE, rt);
}

void	validate_light(t_rt *rt)
{
	if (rt->element[4])
		print_error("Invalid number of arguments on light.", FREE, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (validate_coordinates(rt->coordinates))
		set_coordinates(rt->light.point, rt->coordinates);
	else
		print_error("Invalid light point.", FREE, rt);
	free_ptrptr(rt->coordinates);
	if (validate_double(rt->element[2]))
	{
		rt->light.brightness = ft_atod(rt->element[2]);
		if (rt->light.brightness < 0 || rt->light.brightness > 1)
			print_error("Invalid light brightness.", FREE, rt);
	}
	else
		print_error("Invalid light brightness.", FREE, rt);
	rt->color = ft_split(rt->element[3], ',');
	if (validate_color(rt->color))
		set_color(rt->light.color, rt->color);
	else
		print_error("Invalid light color.", FREE, rt);
	free_ptrptr(rt->color);
}
