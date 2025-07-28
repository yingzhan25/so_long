/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:39:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/28 18:49:48 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_data(t_data *data, t_map *map)
{
	data->map = map;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, map->width * SIZE, \
					map->height * SIZE, "./so_long");
	data->dir = 1;
	data->exit_flag = 0;
	data->exit_display0 = 0;
	data->exit_display1 = 0;
	data->collect_display = 0;
	data->steps = 0;
	data->last = 0;
	data->img = mlx_new_image(data->mlx_ptr, data->map->width * SIZE, \
				data->map->height * SIZE);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, \
				&data->endian);
}

static void	load_textures(t_data *data)
{
	int	s;

	s = SIZE;
	data->tex[0] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/collect.xpm", &s, &s);
	data->tex[1] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/exit.xpm", &s, &s);
	data->tex[2] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/floor.xpm", &s, &s);
	data->tex[3] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/player.xpm", &s, &s);
	data->tex[4] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/wall.xpm", &s, &s);
	data->tex[5] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/enemy0.xpm", &s, &s);
	data->tex[6] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/enemy1.xpm", &s, &s);
	if (!data->tex[0] || !data->tex[1] || !data->tex[2] \
	|| !data->tex[3] || !data->tex[4] || !data->tex[5] || !data->tex[6])
	{
		free_and_exit(-1, data->map, NULL);
		cleanup_mlx(data);
		exit_with_error("Failed to load textures");
	}
}

static int	handle_keypress(int keycode, t_data *data)
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

static int	handle_close(t_data *data)
{
	data->exit_flag = 1;
	return (0);
}

int	main(int ac, char *av[])
{
	t_map	*map;
	t_data	*data;

	if (ac != 2)
		free_and_exit(-1, 0, "Only 1 map allowd");
	map = parse_map(av[1]);
	data = malloc(sizeof(t_data));
	if (!data)
		free_and_exit(-1, map, "Memory allocation failed");
	init_data(data, map);
	load_textures(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, handle_close, data);
	mlx_loop_hook(data->mlx_ptr, game_loop, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
