/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison_matrices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:35:16 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/02 15:44:56 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	are_equals_matrices(double **A, double **B, int size)
{
	int	i;
	int	j;

	i = 0;
	while (A[i])
		i++;
	j = 0;
	while (B[j])
		j++;
	if (i != j)
		return (0);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!are_equals(A[i][j], B[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
