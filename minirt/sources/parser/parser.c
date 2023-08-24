/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/24 17:19:58 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_element(t_rt *rt)
{
	if (!ft_strncmp(rt->element[0], "A", 2))
		validate_amb_light(rt);
	else if (!ft_strncmp(rt->element[0], "C", 2))
		validate_camera(rt);
	else if (!ft_strncmp(rt->element[0], "L", 2))
		validate_light(rt);
	else if (!ft_strncmp(rt->element[0], "sp", 3))
		rt->num_sp++;
	else if (!ft_strncmp(rt->element[0], "pl", 3))
		rt->num_pl++;
	else if (!ft_strncmp(rt->element[0], "cy", 3))
		rt->num_cy++;
	else
		print_error("Invalid element.", FREE, rt);
}

static void	validate_object(t_rt *rt)
{
	int	sp;
	int	pl;
	int	cy;

	sp = 0;
	pl = 0;
	cy = 0;
	if (!ft_strncmp(rt->element[0], "sp", 3))
	{
		validate_sphere(rt, sp);
		sp++;
	}
	else if (!ft_strncmp(rt->element[0], "pl", 3))
	{
		validate_plane(rt, pl);
		pl++;
	}
	else if (!ft_strncmp(rt->element[0], "cy", 3))
	{
		validate_cylinder(rt, cy);
		cy++;
	}
}

void	parser(t_rt *rt)
{
	int	i;

	i = 0;
	while (rt->elements[i])
	{
		rt->element = ft_split(rt->elements[i], ' ');
		validate_element(rt);
		free_ptrptr(&rt->element);
		i++;
	}
	if (!rt->amb_light.amb_light || !rt->light.light || !rt->camera.camera)
		print_error("Some element (ambient light, camera, light) is missing.", \
			FREE, rt);
	rt->spheres = (t_sphere *)ft_calloc(rt->num_sp + 1, sizeof(t_sphere));
	rt->planes = (t_plane *)ft_calloc(rt->num_sp + 1, sizeof(t_plane));
	rt->cylinders = (t_cylinder *)ft_calloc(rt->num_sp + 1, sizeof(t_cylinder));
	i = 0;
	while (rt->elements[i])
	{
		rt->element = ft_split(rt->elements[i], ' ');
		validate_object(rt);
		free_ptrptr(&rt->element);
		i++;
	}
	free_ptrptr(&rt->elements);
}
