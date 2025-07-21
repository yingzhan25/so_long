/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:23:00 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/21 13:48:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	exit_with_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit (1);
}

void	free_and_exit(int fd, t_map *map, char *s)
{
	int	i;

	if (map && map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	if (map)
		free(map);
	if (fd >= 0)
		close(fd);
	if (s)
		exit_with_error(s);
}

char	**make_empty_grid(t_map *map)
{
	char	**grid;
	int	i;

	grid = malloc(sizeof(char*) * map->height);
	if (!grid)
		free_and_exit(-1, map, "Memory allocation failed");
	i = 0;
	while (i < map->height)
	{
		grid[i] = malloc(sizeof(char) * (map->width + 1));
		if (!grid[i])
			free_and_exit(-1, map, "Memory allocation failed");
		ft_memset(grid[i], '0', map->width);
		grid[i][map->width] = '\0';
		i++;
	}
	return (grid);
}