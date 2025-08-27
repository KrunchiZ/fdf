/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:34:37 by kchiang           #+#    #+#             */
/*   Updated: 2025/08/27 19:34:13 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fn_parse_map(t_map *map, char *file)
{
	fn_get_widthdepth(map, file);
}

static void	fn_get_widthdepth(t_map *map, char *file)
{
	int	fd;
	char *line;

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
}

static void	fn_check_width(t_map *map, char *line)
{
	int	width;

	width = fn_get_width(map, line);
	if (width != map->width)
		;//free line and error
	else
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
