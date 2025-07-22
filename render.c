/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:36:54 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/21 17:52:03 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_data *data)
{
	int	size;

	size = SIZE;
	data->tex[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/collect.xpm", &size, &size);
	data->tex[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/exit.xpm", &size, &size);
	data->tex[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/floor.xpm", &size, &size);
	data->tex[3] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player.xpm", &size, &size);
	data->tex[4] = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/wall.xpm", &size, &size);
	if (!data->tex[0] || !data->tex[1] || !data->tex[2] || !data->tex[3] || !data->tex[4])
		exit_with_error("Failed to load textures");
}

void	render_map(t_data *data)
{
	int		i;
	int		j;
	char	c;
	void	*img;

	i = 0;
	img = NULL;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			c = data->map->grid[i][j];
			if (c == 'C')
				img = data->tex[0];
			else if (c == 'E')
				img = data->tex[1];
			else if (c == '0')
				img = data->tex[2];
			else if (c == 'P')
				img = data->tex[3];
			else if (c == '1')
				img = data->tex[4];
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, j * SIZE, i * SIZE);
			j++;
		}
		i++;
	}
}