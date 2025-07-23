/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:05:48 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/23 17:39:25 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_chars(t_map *map, char c, int i, int j)
{
	if (!ft_strchr("10CPE", c))
		free_and_exit(-1, map, "Invalid character in map");
	if (c != '1')
		if ((i == 0 || i == map->height - 1) || (j == 0 || j == map->width - 1))
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

static void	flood_fil(int i, int j, t_map *map, int *is_exit)
{
	if (i < 0 || i >= map->height || j < 0 || j >= map->width)
		return ;
	if (map->grid[i][j] == '1' || map->vis[i][j] == '1')
		return ;
	map->vis[i][j] = '1';
	if (map->grid[i][j] == 'C')
		map->collect--;
	if (map->grid[i][j] == 'E')
		*is_exit = 1;
	flood_fil(i, j + 1, map, is_exit);
	flood_fil(i, j - 1, map, is_exit);
	flood_fil(i - 1, j, map, is_exit);
	flood_fil(i + 1, j, map, is_exit);
}

int	is_path_valid(t_map *map)
{
	int		is_exit;
	int		tmp;

	is_exit = 0;
	map->vis = make_empty_grid(map);
	if (!map->vis)
		free_and_exit(-1, map, "Memory allocation failed");
	tmp = map->collect;
	flood_fil(map->start_y, map->start_x, map, &is_exit);
	free_grid(map, map->vis);
	if (map->collect == 0 && is_exit == 1)
	{
		map->collect = tmp;
		return (1);
	}
	else
		return (0);
}
