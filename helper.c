/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:23:00 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/17 18:49:23 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	exit_with_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit (1);
}

void	clean_fail_alloc(int i, char ***grid)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(grid[j]);
		j++;
	}
	free(grid);
	grid = NULL;
	exit_with_error("Memory allocation failed");
}

char	**make_empty_grid(t_map *map)
{
	char	**grid;
	int	i;

	grid = malloc(sizeof(char*) * map->height);
	if (!grid)
		exit_with_error("Memory allocation failed");
	i = 0;
	while (i < map->height)
	{
		grid[i] = malloc(sizeof(char) * (map->width + 1));
		if (!grid[i])
			clean_fail_alloc(i, &grid);
		ft_memset(grid[i], '0', map->width);
		grid[i][map->width] = '\0';
		i++;
	}
	return (grid);
}