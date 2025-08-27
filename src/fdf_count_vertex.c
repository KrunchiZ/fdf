/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_count_vertex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:35:51 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/28 00:36:50 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fn_check_width(t_map *map, char *line);
static int	fn_get_width(t_map *map, char *line);

void	fn_count_vertex(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd == open(file, O_RDONLY);
	if (fd == -1)
		fn_perror_exit("fdf: open");
	line = get_next_line(fd);
	if (line)
		map->width = fn_get_width(map, line);
	while (line)
	{
		fn_check_width(map, line);
		map->depth++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->vertex_count = map->width * map->depth;
}

static void	fn_check_width(t_map *map, char *line)
{
	int	width;

	width = fn_get_width(map, line);
	if (width != map->width)
	{
		free(line);
		fn_error_exit("input: Map is not rectangular");
	}
	return;
}

static int	fn_get_width(t_map *map, char *line)
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
	while (arr[i])
	{
		width++;
		free(arr[i++]);
	}
	free(arr);
	return (width);
}
