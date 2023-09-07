/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:57:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/07 17:05:44 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_arg(int argc, char *argv[])
{
	if (argc != 2)
		print_error(USAGE, NULL);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 4))
		print_error(FORMAT, NULL);
}

static void	read_rt(t_rt *rt, char *file)
{
	int		fd;
	int		rd;
	char	c;
	char	*buffer;

	fd = open(file, O_RDONLY);
	rd = read(fd, &c, 1);
	if (rd == -1)
		print_error(INV_FILE, rt);
	while (read(fd, &c, 1))
		rd++;
	close(fd);
	buffer = (char *)ft_calloc(rd + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	read(fd, buffer, rd);
	close(fd);
	rt->elements = ft_split(buffer, '\n');
	free(buffer);
}

void	render(t_rt *rt)
{
	int			i;
	int			j;
	t_mlx		*mlx;
	t_mlx_image	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT - bilu", true);
	if (!mlx)
		print_error(MLX_INIT, rt);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
	{
		mlx_close_window(mlx);
		print_error(MLX_IMAGE, rt);
	}
	double	pixel_size = WALL_SIZE / WIDTH;
	double	half = WALL_SIZE / 2;
	j = 0;
	while (j < HEIGHT)
	{
		double	y = half - pixel_size * j;
		i = 0;
		while (i < WIDTH)
		{
			double	x = -half + pixel_size * i;
			t_coordinates	position = create_point(x, y, WALL_Z);
			t_coordinates	ray_origin = create_point(0, 0, -5);
			t_coordinates	vector = subtract_tuples(position, ray_origin);
			t_ray	ray = {ray_origin, normalize_vector(vector)};
			intersections(rt, ray);
			if (get_hit(rt->intersections))
				mlx_put_pixel(image, i, j, 255 << 24 | 0 << 16 | 0 << 8 | 255);
			free_intersections(&rt->intersections);
			i++;
		}
		j++;
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		mlx_delete_image(mlx, image);
		print_error(MLX_IMAGE_TO_WIN, rt);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

int	main(int argc, char *argv[])
{
	t_rt	*rt;

	check_arg(argc, argv);
	rt = (t_rt *)ft_calloc(1, sizeof(t_rt));
	read_rt(rt, argv[1]);
	parser(rt);
	render(rt);
	return (0);
}
