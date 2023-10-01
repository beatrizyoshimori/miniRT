/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_texture_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:18:07 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/30 22:11:00 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_coordinates	calculate_map(t_intersections *hit)
{
	double	theta;
	double	phi;
	double	raw_u;

	theta = atan2(hit->o_point.x, hit->o_point.z);
	raw_u = theta / (2 * M_PI);
	if (hit->type == CO)
		return ((t_coordinates){20 * (1 - (raw_u + 0.5)), \
			4 * hit->o_point.y, 0, 0});
	phi = acos(hit->o_point.y);
	if (hit->sphere->color.red == EARTH || hit->sphere->color.red == MOON)
		return ((t_coordinates){1 - (raw_u + 0.5), \
			1 - phi / M_PI, 0, 0});
	return ((t_coordinates){16 * (1 - (raw_u + 0.5)), \
		8 * (1 - phi / M_PI), 0, 0});
}

t_color	draw_checkerboard(t_intersections *hit)
{
	t_coordinates	point;
	t_coordinates	u_v;

	if (hit->type == SP || hit->type == CO)
	{
		u_v = calculate_map(hit);
		u_v.z = floor(u_v.x);
		u_v.w = floor(u_v.y);
		if ((int)(u_v.z + u_v.w) % 2 == 0)
			return ((t_color){0, 0, 0});
		else
			return ((t_color){255, 255, 255});
	}
	point = create_point(floor(4 * hit->o_point.x), \
		floor(4 * hit->o_point.y), floor(4 * hit->o_point.z));
	if ((int)(point.x + point.y + point.z) % 2 == 0)
		return ((t_color){0, 0, 0});
	return ((t_color){255, 255, 255});
}

t_color	draw_texture(t_intersections *hit)
{
	int				pixel;
	t_coordinates	u_v;

	u_v = calculate_map(hit);
	pixel = (u_v.x * 450 * 4 + u_v.y * 225 * 450) * 4;
	printf("%f %f %d\n", u_v.x, u_v.y, pixel);
	return ((t_color){hit->sphere->texture->pixels[pixel], hit->sphere->texture->pixels[pixel + 1], hit->sphere->texture->pixels[pixel + 2]});
}
