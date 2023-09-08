/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:28:08 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/08 20:22:12 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_rt *rt, double x, double y)
{
	t_coordinates	point;
	t_coordinates	ray_origin;
	t_coordinates	vector;

	(void)rt;
	point = create_point(x, y, WALL_Z);
	ray_origin = create_point(0, 0, -5);
	vector = subtract_tuples(point, ray_origin);
	return ((t_ray){ray_origin, normalize_vector(vector)});
}

// static unsigned int	get_color(t_intersections *hit)
// {
// 	return (hit->sphere->color.red << 24 | hit->sphere->color.green << 16 \
// 		| hit->sphere->color.blue << 8 | 255);
// }

void	draw(t_rt *rt)
{
	int				i;
	int				j;
	double			x;
	double			y;
	t_ray			ray;
	t_intersections	*hit;

	j = 0;
	while (j < HEIGHT)
	{
		y = rt->render.half_wall - rt->render.pixel_size_h * j;
		i = 0;
		while (i < WIDTH)
		{
			x = -rt->render.half_wall + rt->render.pixel_size_w * i;
			ray = create_ray(rt, x, y);
			intersections(rt, ray);
			hit = get_hit(rt->intersections);
			if (hit)
			{
				t_color color = lightning(rt, hit);
				mlx_put_pixel(rt->render.image, i, j, color.red << 24 | color.green << 16 \
					| color.blue << 8 | 255);
			}
			free_intersections(&rt->intersections);
			i++;
		}
		j++;
	}
}

void	render(t_rt *rt)
{
	rt->render.mlx = mlx_init(WIDTH, HEIGHT, "miniRT - bilu", true);
	if (!rt->render.mlx)
		print_error(MLX_INIT, rt);
	rt->render.image = mlx_new_image(rt->render.mlx, WIDTH, HEIGHT);
	if (!rt->render.image)
	{
		mlx_close_window(rt->render.mlx);
		print_error(MLX_IMAGE, rt);
	}
	draw(rt);
	if (mlx_image_to_window(rt->render.mlx, rt->render.image, 0, 0) == -1)
	{
		mlx_close_window(rt->render.mlx);
		mlx_delete_image(rt->render.mlx, rt->render.image);
		print_error(MLX_IMAGE_TO_WIN, rt);
	}
	mlx_loop(rt->render.mlx);
	mlx_terminate(rt->render.mlx);
}
