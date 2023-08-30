/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:57:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/29 22:15:24 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_arg(int argc, char *argv[])
{
	if (argc != 2)
		print_error("Wrong number of arguments.\nUsage: ./miniRT scene.rt", \
			NO_FREE, NULL);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 4))
		print_error("Wrong scene format.\nUsage: ./miniRT scene.rt", \
			NO_FREE, NULL);
}

static int	check_number_elements(char **elements)
{
	if (!elements || !elements[0] || !elements[1] || !elements[2])
		return (0);
	return (1);
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
		print_error("Can't open file.", NO_FREE, NULL);
	while (read(fd, &c, 1))
		rd++;
	close(fd);
	buffer = (char *)ft_calloc(rd + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	read(fd, buffer, rd);
	close(fd);
	rt->elements = ft_split(buffer, '\n');
	free(buffer);
	if (!check_number_elements(rt->elements))
		print_error("Invalid numbers of elements.", FREE, rt);
}

int	main(int argc, char *argv[])
{
	t_rt	*rt;
	mlx_t	*mlx;

	rt = (t_rt *)ft_calloc(1, sizeof(t_rt));
	check_arg(argc, argv);
	read_rt(rt, argv[1]);
	parser(rt);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
