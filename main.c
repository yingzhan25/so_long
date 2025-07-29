/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:39:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/29 14:01:14 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_data(t_data *data, t_map *map)
{
	data->map = map;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, map->width * SIZE, \
					map->height * SIZE, "./so_long");
	data->exit_flag = 0;
	data->exit_display = 0;
	data->steps = 0;
}

static void	load_textures(t_data *data)
{
	int	size;

	size = SIZE;
	data->tex[0] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/collect.xpm", &size, &size);
	data->tex[1] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/exit.xpm", &size, &size);
	data->tex[2] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/floor.xpm", &size, &size);
	data->tex[3] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/player.xpm", &size, &size);
	data->tex[4] = mlx_xpm_file_to_image(data->mlx_ptr, \
				"./textures/wall.xpm", &size, &size);
	if (!data->tex[0] || !data->tex[1] || !data->tex[2] \
				|| !data->tex[3] || !data->tex[4])
	{
		free_and_exit(-1, data->map, NULL);
		cleanup_mlx(data);
		exit_with_error("Failed to load textures");
	}
}

static void	render_img(char c, void **img, t_data *data)
{
	if (c == 'C')
		*img = data->tex[0];
	else if (c == 'E')
		*img = data->tex[1];
	else if (c == '0')
		*img = data->tex[2];
	else if (c == 'P')
		*img = data->tex[3];
	else if (c == '1')
		*img = data->tex[4];
}

void	render_map(t_data *data)
{
	int		i;
	int		j;
	void	*img;

	i = 0;
	img = NULL;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			render_img(data->map->grid[i][j], &img, data);
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, \
									j * SIZE, i * SIZE);
			j++;
		}
		i++;
	}
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
	render_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, handle_close, data);
	mlx_loop_hook(data->mlx_ptr, handle_clean, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
