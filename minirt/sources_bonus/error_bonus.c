/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:44:16 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/26 22:00:34 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	print_error(char *error, t_rt *rt)
{
	printf("Error\n%s\n", error);
	if (rt)
	{
		free_ptrptr(&rt->elements);
		free_ptrptr(&rt->element);
		free_ptrptr(&rt->color);
		free_ptrptr(&rt->coordinates);
		free(rt->lights);
		free(rt->spheres);
		free(rt->planes);
		free(rt->cylinders);
		free(rt->cones);
		free(rt);
	}
	exit(1);
}