/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:44:16 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/19 17:09:53 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_ptrptr(char **ptrptr)
{
	int	i;

	i = 0;
	while (ptrptr[i])
	{
		free(ptrptr[i]);
		i++;
	}
	free(ptrptr);
	ptrptr = NULL;
}

void	print_error(char *error, int f, t_rt *rt)
{
	printf("Error\n%s\n", error);
	if (f == FREE)
	{
		free_ptrptr(rt->elements);
		free_ptrptr(rt->element);
		free(rt);
	}
	exit(1);
}
