/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:20:27 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/02 15:41:02 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**create_matrix(int size)
{
	int		i;
	double	**matrix;

	matrix = (double **)ft_calloc(size + 1, sizeof(double *));
	i = 0;
	while (i < size)
	{
		matrix[i] = (double *)ft_calloc(size, sizeof(double));
		i++;
	}
	return (matrix);
}
