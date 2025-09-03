/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_vertices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:41:20 by kchiang           #+#    #+#             */
/*   Updated: 2025/09/03 15:38:18 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	extract_coord(char *line, t_map *map, int i, int z);
static void	get_color(t_vect *vertices, char *s);
static void	str_tolower(char *str);
static void	set_height(t_map *map, t_vect *vertices);

void	parse_vertices(t_map *map, char *file)
{
	int		fd;
	int		z;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		delete_map(map);
		perror_exit("fdf: open");
	}
	z = 0;
	i = 0;
	line = get_next_line(fd);
	while (line && z < map->depth && i < map->vertex_count)
	{
		extract_coord(line, map, i, z++);
		i += map->width;
		free(line);
		line = get_next_line(fd);
	}
	return ;
}

static void	extract_coord(char *line, t_map *map, int i, int z)
{
	char	**ar;
	int		x;

	ar = ft_split(line, WHITESPACE);
	if (!ar)
	{
		free(line);
		delete_map(map);
		error_exit("ft_split failure");
	}
	x = 0;
	while (ar[x] && x < map->width)
	{
		map->vertices[i + x].x = x;
		map->vertices[i + x].z = z;
		map->vertices[i + x].y = ft_atoi(ar[x]);
		get_color(&map->vertices[i + x], ar[x]);
		set_height(map, &map->vertices[i + x]);
		if (x == map->width / 2 && z == map->depth / 2)
			map->center = map->vertices[i + x];
		free(ar[x++]);
	}
	free(ar);
	return ;
}

static void	get_color(t_vect *vertices, char *s)
{
	vertices->color = PIXEL_BLUE;
	vertices->blue = PIXEL_BLUE;
	while (*s && *s != ',')
		s++;
	if (*s == ',' && *(s + 1))
	{
		s++;
		while (*s == '+' || *s == '-')
			s++;
		str_tolower(s);
		if (ft_strncmp(s, "0x", 2))
			return ;
		s += 2;
		vertices->color = ft_atoi_base(s, BASE16_LOWER);
		vertices->red = get_red(vertices->color);
		vertices->green = get_green(vertices->color);
		vertices->blue = get_blue(vertices->color);
	}
	return ;
}

static void	str_tolower(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
	return ;
}

static void	set_height(t_map *map, t_vect *vertices)
{
	if (vertices->y > map->max_y)
		map->max_y = vertices->y;
	if (vertices->y < map->min_y)
		map->min_y = vertices->y;
	map->height = map->max_y - map->min_y + 1;
	return ;
}
