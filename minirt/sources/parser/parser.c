/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:00:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/19 17:52:39 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_double(char *number)
{
	int	i;

	i = 0;
	if (!number[i])
		return (0);
	if (number[i] == '+' || number[i] == '-')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (number[i] == '.')
		i++;
	if (!number[i])
		return (0);
	while (ft_isdigit(number[i]))
		i++;
	if (!number[i])
		return (1);
	return (0);
}
int	validate_int(char *color)
{
	int	i;

	i = 0;
	while (ft_isdigit(color[i]))
		i++;
	if (!color[i] && i && ft_strlen(color) <= 3)
		return (1);
	return (0);
}

int	validate_color(char **color)
{
	int	i;

	i = 0;
	while (validate_int(color[i]))
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			break ;
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

void	validate_amb_light(t_rt *rt)
{
	int	i;

	i = 0;
	if (validate_double(rt->element[1]))
	{
		rt->amb_light.ratio = ft_atod(rt->element[1]);
		if (rt->amb_light.ratio < 0 || rt->amb_light.ratio > 1)
			print_error("Invalid ambient light ratio.", FREE, rt);
	}
	else
		print_error("Invalid ambient light ratio.", FREE, rt);
	rt->color = ft_split(rt->element[2], ',');
	if (validate_color(rt->color))
	{
		rt->amb_light.color.red = ft_atoi(rt->color[0]);
		rt->amb_light.color.green = ft_atoi(rt->color[1]);
		rt->amb_light.color.blue = ft_atoi(rt->color[2]);
	}
	else
		print_error("Invalid ambient light color.", FREE, rt);
}

void	validate_element(t_rt *rt)
{
	if (!ft_strncmp(rt->element[0], "A", 2))
		validate_amb_light(rt);
}

void	split_elements(t_rt *rt)
{
	int		i;

	i = 0;
	while (rt->elements[i])
	{
		rt->element = ft_split(rt->elements[i], ' ');
		validate_element(rt);
		i++;
	}
}

void	parser(t_rt *rt)
{
	split_elements(rt);
}
