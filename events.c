/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:33:58 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/29 14:18:40 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	win_condition(t_data *data, char c)
{
	if (c == 'C')
		data->map->collect--;
	if (c == 'E')
	{
		data->exit_display = 1;
		if (!data->map->collect)
		{
			ft_printf("You win in %d steps!\n", data->steps);
			data->exit_flag = 1;
		}
	}
}

static void	move_player(t_data *data, int i, int j)
{
	char	c;

	if (data->map->grid[data->map->start_y + i][data->map->start_x + j] != '1')
	{
		if (!data->exit_display)
			data->map->grid[data->map->start_y][data->map->start_x] = '0';
		else
		{
			data->map->grid[data->map->start_y][data->map->start_x] = 'E';
			data->exit_display = 0;
		}
		data->map->start_x += j;
		data->map->start_y += i;
		data->steps++;
		ft_printf("%d\n", data->steps);
		c = data->map->grid[data->map->start_y][data->map->start_x];
		data->map->grid[data->map->start_y][data->map->start_x] = 'P';
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		render_map(data);
		win_condition(data, c);
	}
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		move_player(data, -1, 0);
	else if (keycode == KEY_S)
		move_player(data, 1, 0);
	else if (keycode == KEY_A)
		move_player(data, 0, -1);
	else if (keycode == KEY_D)
		move_player(data, 0, 1);
	else if (keycode == KEY_ESC)
		data->exit_flag = 1;
	return (0);
}

int	handle_close(t_data *data)
{
	data->exit_flag = 1;
	return (0);
}

int	handle_clean(t_data *data)
{
	if (data->exit_flag)
	{
		free_and_exit(-1, data->map, NULL);
		cleanup_mlx(data);
		exit(0);
	}
	return (0);
}
