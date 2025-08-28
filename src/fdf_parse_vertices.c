/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_vertices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:41:20 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/28 19:35:25 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fn_parse_vertices(t_map *map, char *file)
{
	int		fd;
	int		z;
	int		i;
	char	*line;

	fd == open(file, O_RDONLY);
	if (fd == -1)
		fn_perror_exit("fdf: open");
	z = 0;
	i = 0;
	line = get_next_line(fd);
	while (line && z < map->depth)
	{
		fn_extract_coord(line, map, i, z++);
		i += map->width;
		free(line);
		line = get_next_line(fd);
	}
}

static void	fn_extract_coord(char *line, t_map *map, int i, int z)
{
	char	**arr;
	int		x;

	arr = ft_split(line, WHITESPACE);
	if (!arr)
	{
		free(line);
		fn_delete_map(map);
		fn_error_exit("ft_split failure");
	}
	x = 0;
	while (arr[x])
	{
		map->vertices[i + x].y = ft_atoi(arr[x]);
		map->vertices[i + x].color = fn_get_color(arr[x]);
		x++;
	}
}

static int	fn_get_color(char *s)
{
	int	color;

	color = 0;
	while (*s && *s != ',')
		s++;
	if (*s == ',')
	{
		s++;
		if (ft_strncmp(s, "0x", 2) || ft_strncmp(s, "0X", 2))
			return (PIXEL_BLUE);
		while (*s == '+' || *s == '-')
			s++;
		if (!ft_strncmp(s, "0x", 2) || !ft_strncmp(s, "0X", 2))
			s += 2;
		color = ft_atoi_base(s);
	}
	return (color);
}
