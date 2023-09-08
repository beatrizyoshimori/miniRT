/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:20:58 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/08 16:53:32 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	*new_intersection(int type, double t, \
	t_coordinates hit_point, void *object)
{
	t_intersections	*head;

	head = (t_intersections *)ft_calloc(1, sizeof(t_intersections));
	if (head == NULL)
		return (NULL);
	head->type = type;
	head->t = t;
	head->hit_point = hit_point;
	if (type == SP)
		head->sphere = (t_sphere *)object;
	else if (type == PL)
		head->plane = (t_plane *)object;
	else
		head->cylinder = (t_cylinder *)object;
	head->next = NULL;
	return (head);
}

static t_intersections	*get_intersections_position(t_intersections \
	*intersections, t_intersections *new)
{
	if (intersections == NULL)
		return (intersections);
	while (intersections->next)
	{
		if (intersections->next->t > new->t)
			return (intersections);
		intersections = intersections->next;
	}
	return (intersections);
}

void	intersections_list_add(t_intersections **intersections, \
	t_intersections *new)
{
	t_intersections	*aux;
	t_intersections	*aux_next;

	if (!(*intersections))
	{
		*intersections = new;
		return ;
	}
	if ((*intersections)->t > new->t)
	{
		aux = *intersections;
		new->next = aux;
		*intersections = new;
		return ;
	}
	aux = get_intersections_position(*intersections, new);
	aux_next = aux->next;
	aux->next = new;
	new->next = aux_next;
}

void	free_intersections(t_intersections **intersections)
{
	t_intersections	*aux;

	while (*intersections)
	{
		aux = (*intersections)->next;
		free(*intersections);
		(*intersections) = aux;
	}
}
