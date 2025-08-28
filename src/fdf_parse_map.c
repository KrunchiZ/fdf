/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:34:37 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/28 13:41:05 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fn_init_vector_arr(t_map *map);

void	fn_parse_map(t_map *map, char *file)
{
	fn_count_vertex(map, file);
	fn_init_vector_arr(map);
	fn_parse_vertices(map, file);
}

static void	fn_init_vector_arr(t_map *map)
{
	map->vertices = ft_calloc(map->vertex_count, sizeof(t_vect));
	map->px_pos = ft_calloc(map->vertex_count, sizeof(t_vect));
	if (!map->vertices || !map->px_pos)
	{
		fn_delete_map(map);
		fn_error_exit("ft_calloc failure");
	}
}
