/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/17 18:47:42 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map_width(int fd, t_map *map)
{
	char	*first_line;

	first_line = get_next_line(fd);
	if (!first_line)
		exit_with_error("Empty file map");
	map->width = ft_strlen(first_line) - 1;
	map->height = 1;
	free (first_line);
}

void	get_map_height(const char *name, t_map *map)
{
	int		fd;
	char	*line;
	int		cur_width;

	fd = open(name, O_RDONLY);
	get_map_width(fd, map);
	line = get_next_line(fd);
	while (line)
	{
		cur_width = ft_strlen(line) - 1;
		if (cur_width != map->width)
		{
			free(line);
			close(fd);
			exit_with_error("Map is not rectangular");
		}
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	fill_map(const char *name, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit_with_error("Cannot open map");
	map->grid = make_empty_grid(map);
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			clean_fail_alloc(i, &map->grid);
		ft_strlcpy(map->grid[i], line, map->width);
		free(line);
		i++;
	}
	close(fd);
}

void	check_chars(t_map *map, char c, int i, int j)
{
	int	p;
	int	e;

	p = 0;
	e = 0;
	if (!ft_strchr("10CPE", c))
		exit_with_error("Invalid character in map");
	if (c != '1')
		if((i == 0 || i == map->height - 1) || (j == 0 || j == map->width - 1))
			exit_with_error("Map not surrounded by walls");
	if (c == 'P')
	{
		map->start_x = j;
		map->start_y = i;
		if (++p != 1)
			exit_with_error("Invalid character in map");
	}
	if (c == 'E' && ++e != 1)
			exit_with_error("Invalid character in map");
	if (c == 'C')
		map->collect++;
}

void	validate_map(t_map *map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			c = map->grid[i][j];
			check_chars(map, c, i, j);
			j++;
		}
		i++;
	}
	if (map->collect < 1)
		exit_with_error("Invalid character in map");
}

t_map	*parse_map(const char *name)
{
	t_map	*map;

	map = 0;
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->start_x = -1;
	map->start_y = -1;
	map->collect = 0;
	get_map_height(name, map);
	fill_map(name, map);
	validate_map(map);
	if (!is_path_valid(map))
	{
		free_map(map);
		exit_with_error("Path is invalid");
	}
	return (map);
}