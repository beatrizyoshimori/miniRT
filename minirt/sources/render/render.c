/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:28:08 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/09 23:24:23 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**transform_view(t_rt *rt, t_coordinates up)
{
	double			**orientation;
	double			**translation;
	double			**transformation;
	t_coordinates	left;
	t_coordinates	true_up;

	orientation = create_identity_matrix(4);
	left = calculate_cross_product(rt->camera.vector, normalize_vector(up));
	true_up = calculate_cross_product(left, rt->camera.vector);
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[2][0] = -rt->camera.vector.x;
	orientation[2][1] = -rt->camera.vector.y;
	orientation[2][2] = -rt->camera.vector.z;
	translation = create_translation_matrix(negate_tuple(rt->camera.point));
	transformation = multiply_matrices(orientation, translation);
	free_matrix(&orientation);
	free_matrix(&translation);
	return (transformation);
}

// void	calculate_pixel_size(t_rt *rt)
// {
// 	double	aspect;
// 	double	half_view;

// 	half_view = tan(rt->camera.fov * 3.141592 / 360);
// 	printf("fov: %f\n", rt->camera.fov);
// 	printf("half_view: %f\n", half_view);
// 	aspect = WIDTH / HEIGHT;
// 	if (aspect >= 1)
// 	{
// 		rt->render.half_width = half_view;
// 		rt->render.half_height = half_view / aspect;
// 	}
// 	else
// 	{
// 		rt->render.half_width = half_view * aspect;
// 		rt->render.half_height = half_view;
// 	}
// 	rt->render.pixel_size = rt->render.half_width * 100 / HEIGHT;
// }

void	draw(t_rt *rt)
{
	int				i;
	int				j;
	double			x;
	double			y;
	t_ray			ray;

	// rt->render.pixel_size = 0.03;
	//rt->render.pixel_size /= tan(rt->camera.fov * 3.14 / 360);
	printf("pixel_size: %f\n", rt->render.pixel_size);
	rt->render.transformation = transform_view(rt, create_vector(1, 0, 0));
	rt->render.inverse = invert_matrix(rt->render.transformation);
	j = 0;
	while (j < HEIGHT)
	{
		y = rt->render.half_wall - rt->render.pixel_size * j;
		i = 0;
		while (i < WIDTH)
		{
			x = -rt->render.half_wall + rt->render.pixel_size * i;
			ray = create_ray(rt, x, y);
			intersections(rt, ray);
			rt->hit = get_hit(rt->intersections);
			if (rt->hit)
			{
				rt->hit->ray = ray;
				rt->hit->color = lightning(rt);
				mlx_put_pixel(rt->render.image, i, j, rt->hit->color.red << 24 \
					| rt->hit->color.green << 16 \
					| rt->hit->color.blue << 8 | 255);
			}
			free_intersections(&rt->intersections);
			i++;
		}
		j++;
	}
	free_matrix(&rt->render.transformation);
	free_matrix(&rt->render.inverse);
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
