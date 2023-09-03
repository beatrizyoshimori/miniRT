/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:14:43 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/02 16:19:18 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_ptrptr(char ***ptrptr)
{
	int	i;

	i = 0;
	while (*ptrptr && (*ptrptr)[i])
	{
		free((*ptrptr)[i]);
		i++;
	}
	free(*ptrptr);
	*ptrptr = NULL;
}

void	free_matrix(double ***matrix)
{
	int	i;

	i = 0;
	while (*matrix && (*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}
