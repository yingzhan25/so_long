/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:23:00 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/28 17:00:17 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	exit_with_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit (1);
}

void	free_grid(t_map *map, char **s)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

void	free_and_exit(int fd, t_map *map, char *s)
{
	if (map && map->grid)
		free_grid(map, map->grid);
	if (map)
		free(map);
	if (fd >= 0)
		close(fd);
	if (s)
		exit_with_error(s);
}

/*First free map using free_and_exit(s = NULL);
then cleanup_mlx;
at last exit_with_error(if needed)*/

void	cleanup_mlx(t_data *data)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (data->tex[i])
			mlx_destroy_image(data->mlx_ptr, data->tex[i]);
		i++;
	}
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	free(data);
}

char	**make_empty_grid(t_map *map)
{
	char	**grid;
	int		i;

	grid = malloc(sizeof(char *) * map->height);
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
