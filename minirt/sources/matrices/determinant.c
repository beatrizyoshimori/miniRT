/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:22:11 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/06 16:52:06 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**copy_submatrix(double **matrix, int size, int i, int j)
{
	int		k;
	int		l;
	double	**submatrix;

	submatrix = create_matrix(size - 1);
	k = 0;
	while (k < size - 1)
	{
		l = 0;
		while (l < size - 1)
		{
			if (k >= i && l >= j)
				submatrix[k][l] = matrix[k + 1][l + 1];
			else if (k >= i && l < j)
				submatrix[k][l] = matrix[k + 1][l];
			else if (k < i && l >= j)
				submatrix[k][l] = matrix[k][l + 1];
			else
				submatrix[k][l] = matrix[k][l];
			l++;
		}
		k++;
	}
	return (submatrix);
}

static double	calculate_determinant_2_x_2(double **matrix)
{
	return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

double	calculate_determinant(double **matrix)
{
	int		j;
	int		size;
	double	determinant;
	double	**submatrix;
	double	minor;

	size = matrix_length(matrix);
	determinant = 0;
	j = 0;
	while (j < size)
	{
		submatrix = copy_submatrix(matrix, size, 0, j);
		if (matrix_length(submatrix) == 2)
			minor = calculate_determinant_2_x_2(submatrix);
		else
			minor = calculate_determinant(submatrix);
		if (j % 2)
			determinant -= matrix[0][j] * minor;
		else
			determinant += matrix[0][j] * minor;
		free_matrix(&submatrix);
		j++;
	}
	return (determinant);
}

double	**calculate_cofactor_matrix(double **matrix)
{
	int		i;
	int		j;
	int		size;
	double	**submatrix;
	double	**cofactor;

	size = matrix_length(matrix);
	cofactor = create_matrix(size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			submatrix = copy_submatrix(matrix, size, i, j);
			cofactor[i][j] = calculate_determinant(submatrix);
			if ((i + j) % 2)
				cofactor[i][j] *= -1;
			free_matrix(&submatrix);
			j++;
		}
		i++;
	}
	return (cofactor);
}
