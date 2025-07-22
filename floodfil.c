/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:05:48 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/22 16:31:11 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fil(int i, int j, t_map *map, int *is_exit, char **vis)
{
	if (i < 0 || i >= map->height || j < 0 || j >= map->width)
		return ;
	if (map->grid[i][j] == '1' || vis[i][j] == '1')
		return ;
	vis[i][j] = '1';
	if (map->grid[i][j] == 'C')
		map->collect--;
	if (map->grid[i][j] == 'E')
		*is_exit = 1;
	flood_fil(i, j + 1, map, is_exit, vis);
	flood_fil(i, j - 1, map, is_exit, vis);
	flood_fil(i - 1, j, map, is_exit, vis);
	flood_fil(i + 1, j, map, is_exit, vis);
}

int	is_path_valid(t_map *map)
{
	char	**vis;
	int	is_exit;
	int	i;
	int	tmp;

	is_exit = 0;
	vis = make_empty_grid(map);
	if (!vis)
		free_and_exit(-1, map, "Memory allocation failed");
	tmp = map->collect;
	flood_fil(map->start_y, map->start_x, map, &is_exit, vis);
	i = 0;
	while (i < map->height)
	{
		free(vis[i]);
		i++;
	}
	free(vis);
	if (map->collect == 0 && is_exit == 1)
	{
		map->collect = tmp;
		return (1);
	}
	else
		return (0);
}
