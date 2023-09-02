/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:59:40 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/01 19:31:01 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	add_colors(t_color a, t_color b)
{
	return ((t_color){a.red + b.red, a.green + b.green, a.blue + b.blue});
}

t_color	subtract_colors(t_color a, t_color b)
{
	return ((t_color){a.red - b.red, a.green - b.green, a.blue - b.blue});
}

t_color	multiply_color_by_scalar(double scalar, t_color a)
{
	return ((t_color){scalar * a.red, scalar * a.green, scalar * a.blue});
}

t_color	multiply_colors(t_color a, t_color b)
{
	return ((t_color){a.red * b.red, a.green * b.green, a.blue * b.blue});
}
