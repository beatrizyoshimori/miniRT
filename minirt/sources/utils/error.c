/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:44:16 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/23 22:54:45 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_ptrptr(char ***ptrptr)
{
	int		i;

	i = 0;
	while (*ptrptr && (*ptrptr)[i])
	{
		free((*ptrptr)[i]);
		i++;
	}
	free(*ptrptr);
	*ptrptr = NULL;
}

void	print_error(char *error, int f, t_rt *rt)
{
	printf("Error\n%s\n", error);
	if (f == FREE)
	{
		free_ptrptr(&rt->elements);
		free_ptrptr(&rt->element);
		free_ptrptr(&rt->color);
		free(rt->spheres);
		free(rt->planes);
		free(rt->cylinders);
		free(rt);
	}
	exit(1);
}
