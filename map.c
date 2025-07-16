/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/16 18:02:29 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_with_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit (1);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	get_map_size(const char *name, t_map *map)
{
	int		fd;
	char	*first_line;
	char	*line;
	int		cur_width;

	fd = open(name, O_RDONLY);
	first_line = get_next_line(fd);
	if (!first_line)
		exit_with_error("Empty file map");
	map->width = ft_strlen(first_line) - 1;
	map->height = 1;
	free (first_line);
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
	int		j;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit_with_error("Cannot open map");
	map->grid = malloc(sizeof(char *) * (map->height));
	if (!map->grid)
		exit_with_error("Allocation failed");
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map->grid[i])
		{
			j = 0;
			while (j < i)
			{
				free(map->grid[j]);
				j++;
			}
			free(map->grid);
			map->grid = NULL;
			exit_with_error("Memory allocation failed");
		}
		line = get_next_line(fd);
		if (!line)
		{
			j = 0;
			while (j <= i)
			{
				free(map->grid[j]);
				j++;
			}
			free(map->grid);
			map->grid = NULL;
			exit_with_error("Unexpected end reading files");
		}
		ft_strlcpy(map->grid[i], line, map->width);
		map->grid[i][map->width] = '\0';
		free(line);
		i++;
	}
	close(fd);
}

void	check_walls(t_map *map, char c, int i, int j)
{
	if ((i == 0 || i == map->height - 1) && c != 1)
		exit_with_error("Map not surrounded by walls");
	else if ((j == 0 || j == map->width - 1) && c != 1)
		exit_with_error("Map not surrounded by walls");
}

void	validate_map(t_map *map)
{
	int		i;
	int		j;
	char	c;
	int		nb_p;
	int		nb_e;

	i = 0;
	nb_p = 0;
	nb_e = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			c = map->grid[i][j];
			check_walls(&map, c, i, j);
			if (c == 'P')
			{
				map->start_x = j;
				map->start_y = i;
				nb_p++;
			}
			else if (c == 'E')
				nb_e++;
			else if (c == 'C')
				map->collect++;
			if ((c != '0' && c != '1') || nb_p != 1 || nb_e != 1)
				exit_with_error("Invalid character in map");
			j++;
		}
		i++;
	}
	if (map->collect < 1)
		exit_with_error("Invalid character in map");
}

t_map	parse_map(const char *name)
{
	t_map	map;

	map.grid = NULL;
	map.width = 0;
	map.height = 0;
	map.start_x = -1;
	map.start_y = -1;
	map.collect = 0;
	get_map_size(name, &map);
	fill_map(name, &map);
	validate_map(&map);
	if (!is_path_valid(&map))
	{
		free_map(&map);
		exit_with_error("Path is invalid");
	}
}