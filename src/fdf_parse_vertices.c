/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_vertices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:41:20 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/28 14:04:05 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fn_parse_vertices(t_map *map, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd == open(file, O_RDONLY);
	if (fd == -1)
		fn_perror_exit("fdf: open");
	i = 0;
	line = get_next_line(fd);
	while (line && i < map->vertex_count)
	{
		fn_extract_coord(line, map, i);
		i += map->width;
		free(line);
		line = get_next_line(fd);
	}
}

static void	fn_extract_coord(char *line, t_map *map, int i)
{
	char	**arr;
	int		i;

	arr = ft_split(line, WHITESPACE);
	if (!arr)
	{
		free(line);
		fn_delete_map(map);
		fn_error_exit("ft_split failure");
	}
	i = 0;
	while (arr[i])
	{
		if (fn_is_invalid(arr[i]))
		{
			free(line);
			fn_delete_map(map);
			fn_error_exit("input: Invalid map");
		}
	}
}

static int	fn_is_invalid(char *s)
{
	if (!*s)
		return (true);
	if (*s == '+' || *s == '-')
		s++;
}
