/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:06:19 by kchiang           #+#    #+#             */
/*   Updated: 2025/10/22 21:10:32 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "fdf.h"

void	error_exit(char *str)
{
	ft_putstr_fd("fdf: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	delete_map(t_map *map)
{
	free(map->vertices);
	free(map->render_pt);
	free(map->edges);
	*map = (t_map){0};
}
