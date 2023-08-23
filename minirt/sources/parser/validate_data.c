/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:19:14 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/22 21:19:42 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_color(char **color)
{
	int	i;

	i = 0;
	while (color[i] && validate_int(color[i]))
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
	while (coordinates[i] && validate_double(coordinates[i]))
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
