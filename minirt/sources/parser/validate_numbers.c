/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 21:17:13 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/22 21:17:52 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_double(char *number)
{
	int	i;

	i = 0;
	if (!number[i])
		return (0);
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (1);
	if (number[i] == '.')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (1);
	return (0);
}

int	validate_int(char *number)
{
	int	i;

	i = 0;
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i] && i && ft_strlen(number) <= 3)
		return (1);
	return (0);
}
