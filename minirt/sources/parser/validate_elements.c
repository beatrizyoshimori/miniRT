/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:21:50 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/23 22:54:37 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_amb_light(t_rt *rt)
{
	if (rt->amb_light.amb_light)
		print_error("Invalid number of ambient lights.", FREE, rt);
	if (rt->element[3])
		print_error("Invalid number of arguments on ambient light.", FREE, rt);
	if (!validate_double(rt->element[1]))
		print_error("Invalid ambient light ratio. Ratio is not a double.", \
			FREE, rt);
	rt->amb_light.ratio = ft_atod(rt->element[1]);
	if (rt->amb_light.ratio < 0 || rt->amb_light.ratio > 1)
		print_error("Invalid ambient light ratio. Ratio: 0.0 - 1.0.", \
			FREE, rt);
	rt->color = ft_split(rt->element[2], ',');
	if (!validate_color(rt->color))
		print_error("Invalid ambient light color.", FREE, rt);
	set_color(&rt->amb_light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->amb_light.amb_light = 1;
}

void	validate_camera(t_rt *rt)
{
	if (rt->camera.camera)
		print_error("Invalid number of cameras.", FREE, rt);
	if (rt->element[4])
		print_error("Invalid number of arguments on camera.", FREE, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid camera point.", FREE, rt);
	set_coordinates(&rt->camera.point, rt->coordinates);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->element[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid camera vector.", FREE, rt);
	set_coordinates(&rt->camera.vector, rt->coordinates);
	if (!validate_normalized_vector(rt->camera.vector))
		print_error("Invalid camera vector. Vector is not normalized.", \
			FREE, rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_angle(rt->element[3]))
		print_error("Invalid camera horizontal field of view.", FREE, rt);
	rt->camera.fov = ft_atoi(rt->element[3]);
	rt->camera.camera = 1;
}

void	validate_light(t_rt *rt)
{
	if (rt->light.light)
		print_error("Invalid number of lights.", FREE, rt);
	if (rt->element[4])
		print_error("Invalid number of arguments on light.", FREE, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error("Invalid light point.", FREE, rt);
	set_coordinates(&rt->light.point, rt->coordinates);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->element[2]))
		print_error("Invalid light brightness. Brightness is a double", \
			FREE, rt);
	rt->light.brightness = ft_atod(rt->element[2]);
	if (rt->light.brightness < 0 || rt->light.brightness > 1)
		print_error("Invalid light brightness.", FREE, rt);
	rt->color = ft_split(rt->element[3], ',');
	if (!validate_color(rt->color))
		print_error("Invalid light color.", FREE, rt);
	set_color(&rt->light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->light.light = 1;
}
