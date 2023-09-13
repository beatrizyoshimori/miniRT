/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:57:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/09/13 18:39:07 by lucade-s         ###   ########.fr       */
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

void	init_object_matrix(t_rt *rt)
{
	int		i;
	double	r;
	double	**scaling;
	double	**translation;
	double	**product;

	scaling = NULL;
	translation = NULL;
	product = NULL;
	i = 0;
	while (i < rt->num_sp)
	{
		r = rt->spheres[i].diameter / 2;
		scaling = create_scaling_matrix(create_point(r, r, r));
		translation = create_translation_matrix(rt->spheres[i].point);
		product = multiply_matrices(translation, scaling);
		rt->spheres[i].inverse = invert_matrix(product);
		rt->spheres[i].transpose = transpose_matrix(rt->spheres[i].inverse);
		i++;
	}
	free_matrix(&scaling);
	free_matrix(&translation);
	free_matrix(&product);
}

static t_rt	*init_rt(void)
{
	t_rt	*rt;

	rt = (t_rt *)ft_calloc(1, sizeof(t_rt));
	rt->material.ambient = 0.1;
	rt->material.diffuse = 0.9;
	rt->material.specular = 0.9;
	rt->material.shininess = 200.0;
	return (rt);
}

int	main(int argc, char *argv[])
{
	t_rt	*rt;

	rt = init_rt();
	check_arg(argc, argv);
	read_rt(rt, argv[1]);
	parser(rt);
	init_object_matrix(rt);
	render(rt);
	return (0);
}
