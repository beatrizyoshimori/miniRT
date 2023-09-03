/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison_matrices.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:35:16 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/02 19:18:14 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	length_matrix(double **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	are_equals_matrices(double **A, double **B)
{
	int	i;
	int	j;
	int	size;

	if (length_matrix(A) != length_matrix(B))
		return (0);
	size = length_matrix(A);
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
