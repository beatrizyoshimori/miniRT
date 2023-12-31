/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:21:50 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/01 17:12:52 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_amb_light(t_rt *rt)
{
	if (rt->amb_light.amb_light)
		print_error(NUM_AMB_LIGHT, rt);
	if (rt->element[3])
		print_error(ARG_AMB_LIGHT, rt);
	if (!validate_double(rt->element[1]))
		print_error(D_RATIO_AMB_LIGHT, rt);
	rt->amb_light.ratio = ft_atod(rt->element[1]);
	if (rt->amb_light.ratio < 0 || rt->amb_light.ratio > 1)
		print_error(R_RATIO_AMB_LIGHT, rt);
	rt->color = ft_split(rt->element[2], ',');
	if (!validate_color(rt->color))
		print_error(COLOR_AMB_LIGHT, rt);
	set_color(&rt->amb_light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->amb_light.amb_light = 1;
}

void	validate_camera(t_rt *rt)
{
	if (rt->camera.camera)
		print_error(NUM_CAM, rt);
	if (rt->element[4])
		print_error(ARG_CAM, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error(POINT_CAM, rt);
	set_coordinates(&rt->camera.point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->element[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error(VECTOR_CAM, rt);
	set_coordinates(&rt->camera.vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->camera.vector))
		print_error(R_VECTOR_CAM, rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_angle(rt->element[3]))
		print_error(FOV_CAM, rt);
	rt->camera.fov = ft_atoi(rt->element[3]);
	rt->camera.camera = 1;
}

void	validate_light(t_rt *rt)
{
	if (rt->light.light)
		print_error(NUM_LIGHT, rt);
	if (rt->element[4])
		print_error(ARG_LIGHT, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error(POINT_LIGHT, rt);
	set_coordinates(&rt->light.point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->element[2]))
		print_error(D_BRIGHT_LIGHT, rt);
	rt->light.brightness = ft_atod(rt->element[2]);
	if (rt->light.brightness < 0 || rt->light.brightness > 1)
		print_error(R_BRIGHT_LIGHT, rt);
	rt->color = ft_split(rt->element[3], ',');
	if (!validate_color(rt->color))
		print_error(COLOR_LIGHT, rt);
	set_color(&rt->light.color, rt->color);
	free_ptrptr(&rt->color);
	rt->light.light = 1;
}
