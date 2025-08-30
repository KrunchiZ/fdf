/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:34:37 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/30 16:23:27 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fn_count_vertex(t_map *map, char *file);
static void	fn_check_width(t_map *map, char *line);
static int	fn_get_width(char *line);
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
	return ;
}

static void	fn_count_vertex(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		fn_perror_exit("fdf: open");
	line = get_next_line(fd);
	if (line)
		map->width = fn_get_width(line);
	while (line)
	{
		fn_check_width(map, line);
		map->depth++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map->width < 2 || map->depth < 2)
		fn_error_exit("input: Map is not rectangular");
	map->vertex_count = map->width * map->depth;
	return ;
}

static void	fn_check_width(t_map *map, char *line)
{
	int	width;

	width = fn_get_width(line);
	if (width != map->width)
	{
		free(line);
		fn_error_exit("input: Map is not rectangular");
	}
	return ;
}

static int	fn_get_width(char *line)
{
	char	**arr;
	int		i;
	int		width;

	arr = ft_split(line, WHITESPACE);
	if (!arr)
	{
		free(line);
		fn_error_exit("ft_split failure");
	}
	i = 0;
	width = 0;
	while (arr[i])
	{
		width++;
		free(arr[i++]);
	}
	free(arr);
	return (width);
}
