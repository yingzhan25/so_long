/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/23 17:37:23 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_map_width(int fd, t_map *map)
{
	char	*first_line;

	first_line = get_next_line(fd);
	if (!first_line)
		free_and_exit(fd, map, "Empty file map");
	map->width = ft_strlen(first_line) - 1;
	map->height = 1;
	free (first_line);
}

static int	get_cur_width(char *line)
{
	int	cur_width;

	cur_width = 0;
	if (ft_strchr(line, '\n'))
		cur_width = ft_strlen(line) - 1;
	else
		cur_width = ft_strlen(line);
	return (cur_width);
}

static void	get_map_height(const char *name, t_map *map)
{
	int		fd;
	char	*line;
	int		is_rect;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		free_and_exit(fd, map, "Failed to open map");
	get_map_width(fd, map);
	line = get_next_line(fd);
	is_rect = 1;
	while (line)
	{
		if (get_cur_width(line) != map->width)
			is_rect = 0;
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (!is_rect)
		free_and_exit(fd, map, "Map is not rectangular");
	close(fd);
}

static void	fill_map(const char *name, t_map *map)
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

t_map	*parse_map(const char *name)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		free_and_exit(-1, map, "Memory allocation failed");
	map->grid = NULL;
	map->vis = NULL;
	map->width = 0;
	map->height = 0;
	map->start_x = -1;
	map->start_y = -1;
	map->collect = 0;
	map->exit = 0;
	map->player = 0;
	get_map_height(name, map);
	fill_map(name, map);
	validate_map(map);
	if (!is_path_valid(map))
		free_and_exit(-1, map, "Path is invalid");
	return (map);
}
