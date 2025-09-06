/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:34:37 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/06 22:52:10 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	count_vertex(t_map *map, char *file);
static void	check_width(t_map *map, char *line);
static int	get_width(char *line);
static void	center_geo_pivot(t_map *map);

void	parse_map(t_map *map, char *file)
{
	count_vertex(map, file);
	map->vertices = ft_calloc(map->vertex_count, sizeof(t_vect));
	map->render_pt = ft_calloc(map->vertex_count, sizeof(t_vect));
	map->edges = ft_calloc(map->edge_count, sizeof(t_edge));
	if (!map->vertices || !map->render_pt || !map->edges)
	{
		delete_map(map);
		error_exit("ft_calloc failure");
	}
	parse_vertices(map, file);
	center_geo_pivot(map);
	return ;
}

static void	center_geo_pivot(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->vertex_count)
	{
		map->vertices[i].x -= (map->width - 1.0f) / 2.0f;
		map->vertices[i].z -= (map->depth - 1.0f) / 2.0f;
		map->vertices[i].y -= map->min_y + (map->height - 1.0f) / 2.0f;
		i++;
	}
	return ;
}

static void	count_vertex(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror_exit("fdf: open");
	line = get_next_line(fd);
	if (line)
		map->width = get_width(line);
	while (line)
	{
		check_width(map, line);
		map->depth++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map->width < 2 || map->depth < 2)
		error_exit("input: Map is not rectangular");
	map->vertex_count = map->width * map->depth;
	map->edge_count
		= (map->width - 1) * map->depth + (map->depth - 1) * map->width;
	return ;
}

static void	check_width(t_map *map, char *line)
{
	int	width;

	width = get_width(line);
	if (width != map->width)
	{
		free(line);
		error_exit("input: Map is not rectangular");
	}
	return ;
}

static int	get_width(char *line)
{
	char	**arr;
	int		i;
	int		width;

	arr = ft_split(line, WHITESPACE);
	if (!arr)
	{
		free(line);
		error_exit("ft_split failure");
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
