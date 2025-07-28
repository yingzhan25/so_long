/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:39:19 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/28 18:52:36 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	update_map_enemy(t_data *data)
{
	if (!data->exit_display1 && !data->collect_display)
		data->map->grid[data->map->enemy_y][data->map->enemy_x] = '0';
	else if (data->exit_display1)
	{
		data->map->grid[data->map->enemy_y][data->map->enemy_x] = 'E';
		data->exit_display1 = 0;
	}
	else if (data->collect_display)
	{
		data->map->grid[data->map->enemy_y][data->map->enemy_x] = 'C';
		data->collect_display = 0;
	}
	if (data->map->grid[data->map->enemy_y][data->map->enemy_x + data->dir] \
		== 'E')
		data->exit_display1 = 1;
	if (data->map->grid[data->map->enemy_y][data->map->enemy_x + data->dir] \
		== 'C')
		data->collect_display = 1;
	data->map->enemy_x += data->dir;
	if (data->dir == 1)
		data->map->grid[data->map->enemy_y][data->map->enemy_x] = 'M';
	else
		data->map->grid[data->map->enemy_y][data->map->enemy_x] = 'W';
}

void	move_enemy(t_data *data)
{
	if (data->map->grid[data->map->enemy_y][data->map->enemy_x + data->dir] \
		== '1')
	{
		data->dir *= -1;
		return ;
	}
	if (data->map->grid[data->map->enemy_y][data->map->enemy_x + data->dir] \
		== 'P')
	{
		ft_printf("You were caught by BUG in %d steps!\n", data->steps);
		data->exit_flag = 1;
		return ;
	}
	update_map_enemy(data);
	return ;
}

static void	update_map_player(t_data *data, int i, int j)
{
	if (!data->exit_display0)
		data->map->grid[data->map->start_y][data->map->start_x] = '0';
	else
	{
		data->map->grid[data->map->start_y][data->map->start_x] = 'E';
		data->exit_display0 = 0;
	}
	data->map->start_x += j;
	data->map->start_y += i;
	data->steps++;
	if (data->map->grid[data->map->start_y][data->map->start_x] == 'C')
		data->map->collect--;
	if (data->map->grid[data->map->start_y][data->map->start_x] == 'E')
	{
		data->exit_display0 = 1;
		if (!data->map->collect)
		{
			ft_printf("You win in %d steps!\n", data->steps);
			data->exit_flag = 1;
		}
	}
	data->map->grid[data->map->start_y][data->map->start_x] = 'P';
}

void	move_player(t_data *data, int i, int j)
{
	int		new_x;
	int		new_y;

	new_y = data->map->start_y + i;
	new_x = data->map->start_x + j;
	if (data->map->grid[new_y][new_x] == 'M' || data->map->grid[new_y][new_x] \
		== 'W')
	{
		ft_printf("You were caught by BUG in %d steps!\n", data->steps);
		data->exit_flag = 1;
		return ;
	}
	if (data->map->grid[new_y][new_x] != '1')
		update_map_player(data, i, j);
}
