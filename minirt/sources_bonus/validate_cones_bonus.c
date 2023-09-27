/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cones_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:40:16 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/26 21:52:23 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	validate_cone_aux(t_rt *rt, int co)
{
	if (!validate_double(rt->element[4]))
		print_error(D_HEIGHT_CO, rt);
	rt->cones[co].height = ft_atod(rt->element[4]);
	if (rt->cones[co].height <= 0)
		print_error(R_HEIGHT_CO, rt);
	rt->cones[co].max = rt->cones[co].height / 2;
	rt->cones[co].min = -rt->cones[co].max;
	rt->color = ft_split(rt->element[5], ',');
	if (!validate_color(rt->color))
		print_error(COLOR_CO, rt);
	set_color(&rt->cones[co].color, rt->color);
	free_ptrptr(&rt->color);
}

void	validate_cone(t_rt *rt, int co)
{
	if (rt->element[6])
		print_error(ARG_CO, rt);
	rt->coordinates = ft_split(rt->element[1], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error(CENTER_CO, rt);
	set_coordinates(&rt->cones[co].point, rt->coordinates, POINT);
	free_ptrptr(&rt->coordinates);
	rt->coordinates = ft_split(rt->element[2], ',');
	if (!validate_coordinates(rt->coordinates))
		print_error(VECTOR_CO, rt);
	set_coordinates(&rt->cones[co].vector, rt->coordinates, VECTOR);
	if (!validate_normalized_vector(rt->cones[co].vector))
		print_error(N_VECTOR_CO, rt);
	free_ptrptr(&rt->coordinates);
	if (!validate_double(rt->element[3]))
		print_error(D_DIAM_CO, rt);
	rt->cones[co].diameter = ft_atod(rt->element[3]);
	if (rt->cones[co].diameter <= 0)
		print_error(R_DIAM_CO, rt);
	validate_cone_aux(rt, co);
}
