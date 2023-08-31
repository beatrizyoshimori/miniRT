/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:42:32 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/30 18:50:14 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates	create_point(double x, double y, double z)
{
	return ((t_coordinates){.x = x, .y = y, .z = z, .w = 1});
}

t_coordinates	create_vector(double x, double y, double z)
{
	return ((t_coordinates){.x = x, .y = y, .z = z, .w = 0});
}
