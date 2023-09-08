/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:20:58 by lucade-s          #+#    #+#             */
/*   Updated: 2023/09/08 11:19:37 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersections	*new_intersection(int object, double t, t_color color)
{
	t_intersections	*head;

	head = (t_intersections *)ft_calloc(1, sizeof(t_intersections));
	if (head == NULL)
		return (NULL);
	head->object = object;
	head->t = t;
	head->color = color;
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
