/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:05:48 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/18 17:32:03 by yingzhan         ###   ########.fr       */
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

	is_exit = 0;
	vis = make_empty_grid(map);
	if (!vis)
		exit_with_error("Memory allocation failed");
	flood_fil(map->start_y, map->start_x, map, &is_exit, vis);
	if (map->collect == 0 && is_exit == 1)
		return (1);
	else
		return (0);
}
