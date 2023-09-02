/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:57:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/02 15:31:24 by lucade-s         ###   ########.fr       */
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
	i = 100;
	while (i <= 299)
	{
		j = 100;
		while (j <= 299)
		{
			mlx_put_pixel(image, i, j, 0 << 24 | 0 << 16 | 0 << 8 | 255);
			j++;
		}
		i++;
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
