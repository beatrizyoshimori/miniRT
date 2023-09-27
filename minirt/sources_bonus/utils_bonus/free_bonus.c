/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:14:43 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/26 22:01:41 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	free_ptrptr(char ***ptrptr)
{
	int	i;

	i = 0;
	while (*ptrptr && (*ptrptr)[i])
	{
		free((*ptrptr)[i]);
		i++;
	}
	free(*ptrptr);
	*ptrptr = NULL;
}

void	free_matrix(double ***matrix)
{
	int	i;

	i = 0;
	while (*matrix && (*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

static void	free_sphere_plane_matrices(t_rt *rt)
{
	int	i;

	i = -1;
	while (++i < rt->num_sp)
	{
		free_matrix(&rt->spheres[i].inverse);
		free_matrix(&rt->spheres[i].transpose);
	}
	i = -1;
	while (++i < rt->num_pl)
	{
		free_matrix(&rt->planes[i].inverse);
		free_matrix(&rt->planes[i].transpose);
	}
}

static void	free_cylinder_cone_matrices(t_rt *rt)
{
	int	i;

	i = -1;
	while (++i < rt->num_cy)
	{
		free_matrix(&rt->cylinders[i].inverse);
		free_matrix(&rt->cylinders[i].transpose);
	}
	i = -1;
	while (++i < rt->num_co)
	{
		free_matrix(&rt->cones[i].inverse);
		free_matrix(&rt->cones[i].transpose);
	}
}

void	free_rt(t_rt *rt)
{
	free_ptrptr(&rt->elements);
	free_ptrptr(&rt->element);
	free_ptrptr(&rt->color);
	free_ptrptr(&rt->coordinates);
	free(rt->lights);
	free_sphere_plane_matrices(rt);
	free(rt->spheres);
	free(rt->planes);
	free_cylinder_cone_matrices(rt);
	free(rt->cylinders);
	free(rt->cones);
	mlx_close_window(rt->render.mlx);
	mlx_delete_image(rt->render.mlx, rt->render.image);
	mlx_terminate(rt->render.mlx);
	free(rt);
	exit(0);
}