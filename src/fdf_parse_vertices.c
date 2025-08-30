/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_vertices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:41:20 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/30 14:48:13 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fn_extract_coord(char *line, t_map *map, int i, int z);
static int	fn_get_color(char *s);
static void	fn_str_tolower(char *str);
static void	fn_set_height(t_map *map, t_vect *vertices);

void	fn_parse_vertices(t_map *map, char *file)
{
	int		fd;
	int		z;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		fn_perror_exit("fdf: open");
	z = 0;
	i = 0;
	line = get_next_line(fd);
	while (line && z < map->depth && i < map->vertex_count)
	{
		fn_extract_coord(line, map, i, z++);
		i += map->width;
		free(line);
		line = get_next_line(fd);
	}
	return ;
}

static void	fn_extract_coord(char *line, t_map *map, int i, int z)
{
	char	**ar;
	int		x;

	ar = ft_split(line, WHITESPACE);
	if (!ar)
	{
		free(line);
		fn_delete_map(map);
		fn_error_exit("ft_split failure");
	}
	x = 0;
	while (ar[x] && x < map->width)
	{
		map->vertices[i + x].x = x;
		map->vertices[i + x].z = z;
		map->vertices[i + x].y = ft_atoi(ar[x]);
		map->vertices[i + x].color = fn_get_color(&map->vertices[i + x], ar[x]);
		fn_set_height(map, &map->vertices[i + x]);
		free(ar[x++]);
	}
	free(ar);
	return ;
}

static int	fn_get_color(t_vect *vertices, char *s)
{
	vertices->color = PIXEL_BLUE;
	while (*s && *s != ',')
		s++;
	if (*s == ',' && *(s + 1))
	{
		s++;
		while (*s == '+' || *s == '-')
			s++;
		if (ft_strncmp(s, "0x", 2) || ft_strncmp(s, "0X", 2))
			return ;
		if (!ft_strncmp(s, "0x", 2) || !ft_strncmp(s, "0X", 2))
			s += 2;
		fn_str_tolower(s);
		vertices->color = ft_atoi_base(s, BASE16_LOWER);
		vertices->red = fn_get_red(vertices->color);
		vertices->green = fn_get_green(vertices->color);
		vertices->blue = fn_get_blue(vertices->color);
	}
	return ;
}

static void	fn_str_tolower(char *str)
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

static void	fn_set_height(t_map *map, t_vect *vertices)
{
	if (vertices->y > map->max_y)
		map->max_y = vertices->y;
	if (vertices->y < map->min_y)
		map->min_y = vertices->y;
	map->height = map->max_y - map->min_y + 1;
	return ;
}
