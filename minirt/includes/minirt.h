/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:02:11 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/18 20:06:38 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_amb_light
{
	
}	t_amb_light;


typedef struct s_rt
{
	char	**elements;
}	t_rt;

// parser folder
// parser.c function
void	parser(t_rt *rt);

// utils folder
// error.c function
void	print_error(char *error);

#endif