/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:39:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/22 17:37:54 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char *av[])
{
	t_map	*map;
	t_data	*data;

	if (ac != 2)
		free_and_exit(-1, 0,"Only 1 map allowd");
	map = parse_map(av[1]);
	data = malloc(sizeof(t_data));
	if (!data)
		free_and_exit(-1, map, "Memory allocation failed");
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, map->width * SIZE, map->height * SIZE, "so_long");
	data->map = map;
	data->exit_flag = 0;
	data->steps = 0;
	load_textures(data);
	render_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, handle_close, data);
	mlx_loop_hook(data->mlx_ptr, handle_clean, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}