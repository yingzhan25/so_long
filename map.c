/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/21 13:25:34 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_map_width(int fd, t_map *map)
{
	char	*first_line;

	first_line = get_next_line(fd);
	if (!first_line)
		free_and_exit(fd, map, "Empty file map");
	map->width = ft_strlen(first_line) - 1;
	map->height = 1;
	free (first_line);
}

void	get_map_height(const char *name, t_map *map)
{
	int		fd;
	char	*line;
	int		cur_width;
	int		is_rect;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		free_and_exit(fd, map, "Failed to open map");
	get_map_width(fd, map);
	line = get_next_line(fd);
	is_rect = 1;
	while (line)
	{
		if (ft_strchr(line, '\n'))
			cur_width = ft_strlen(line) - 1;
		else
			cur_width = ft_strlen(line);
		if (cur_width != map->width)
			is_rect = 0;
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (!is_rect)
		free_and_exit(fd, map, "Map is not rectangular");
	close(fd);
}

void	fill_map(const char *name, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		free_and_exit(fd, map, "Failed to open map");
	map->grid = make_empty_grid(map);
	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			free_and_exit(fd, map, "Memory allocation failed");
		ft_strlcpy(map->grid[i], line, map->width + 1);
		free(line);
		i++;
	}
	close(fd);
}

void	check_chars(t_map *map, char c, int i, int j)
{
	if (!ft_strchr("10CPE", c))
		free_and_exit(-1, map, "Invalid character in map");
	if (c != '1')
		if((i == 0 || i == map->height - 1) || (j == 0 || j == map->width - 1))
			free_and_exit(-1, map, "Map not surrounded by walls");
	if (c == 'P')
	{
		map->start_x = j;
		map->start_y = i;
		if (++map->player != 1)
			free_and_exit(-1, map, "More than 1 player in map");
	}
	if (c == 'E' && ++map->exit != 1)
		free_and_exit(-1, map, "More than 1 exit in map");
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
		free_and_exit(-1, map, "Less than 1 collectible in map");
	if (map->exit < 1)
		free_and_exit(-1, map, "Less than 1 exit in map");
	if (map->player < 1)
		free_and_exit(-1, map, "Less than 1 player in map");
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->start_x = -1;
	map->start_y = -1;
	map->collect = 0;
	map->exit = 0;
	map->player = 0;
}

t_map	*parse_map(const char *name)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		free_and_exit(-1, map,"Failed to allocate map");
	init_map(map);
	get_map_height(name, map);
	fill_map(name, map);
	validate_map(map);
	if (!is_path_valid(map))
		free_and_exit(-1, map, "Path is invalid");
	return (map);
}