/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:57:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/08/16 21:59:48 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_arg(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_error("Wrong number of arguments.\nUsage: ./miniRT scene.rt");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 4))
	{
		print_error("Wrong scene format.\nUsage: ./miniRT scene.rt");
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	check_arg(argc, argv);
	parser();
	return (0);
}
