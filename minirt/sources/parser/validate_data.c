/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:19:14 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/23 18:07:15 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_color(char **color)
{
	int	i;

	i = 0;
	while (color && color[i] && validate_int(color[i]))
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			break ;
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int	validate_coordinates(char **coordinates)
{
	int	i;

	i = 0;
	while (coordinates && coordinates[i] && validate_double(coordinates[i]))
		i++;
	if (i != 3)
		return (0);
	return (1);
}

int	validate_normalized_vector(t_coordinates coordinates)
{
	double	norm;
	double	aux;

	aux = pow(coordinates.x, 2) + pow(coordinates.y, 2) + pow(coordinates.z, 2);
	norm = sqrt(aux);
	norm = round(norm * pow(10, 6)) / pow(10, 6);
	if (norm == 1)
		return (1);
	return (0);
}

int	validate_angle(char *angle)
{
	if (angle && validate_int(angle) && ft_atoi(angle) >= 0 \
		&& ft_atoi(angle) <= 180)
		return (1);
	return (0);
}
