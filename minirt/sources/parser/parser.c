/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/22 21:41:58 by byoshimo         ###   ########.fr       */
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
}

static void	split_elements(t_rt *rt)
{
	int		i;

	i = 0;
	while (rt->elements[i])
	{
		rt->element = ft_split(rt->elements[i], ' ');
		validate_element(rt);
		free_ptrptr(rt->element);
		i++;
	}
	free_ptrptr(rt->elements);
}

void	parser(t_rt *rt)
{
	split_elements(rt);
}
