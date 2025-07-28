/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:33:58 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/28 18:24:13 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	else if (c == 'M')
		*img = data->tex[5];
	else if (c == 'W')
		*img = data->tex[6];
}

static void	mlx_put_image_to_image(t_data *data, void *src_img, int x, int y)
{
	t_data	src;
	char	*src_pixel;
	char	*dst_pixel;
	int		i;
	int		j;

	src.addr = mlx_get_data_addr(src_img, &src.bpp, &src.line_len, &src.endian);
	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			src_pixel = src.addr + (i * src.line_len + j * (src.bpp / 8));
			dst_pixel = data->addr + ((y + i) * data->line_len) + ((x + j) \
						* (data->bpp / 8));
			if (*(unsigned int *)src_pixel != BLACK)
				*(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
			j++;
		}
		i++;
	}
}

static void	draw_map(t_data *data)
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
			mlx_put_image_to_image(data, img, j * SIZE, i * SIZE);
			j++;
		}
		i++;
	}
}

static void	print_moves(t_data *data)
{
	char	*s;
	char	*output;

	s = ft_itoa(data->steps);
	if (!s)
	{
		free_and_exit(-1, data->map, NULL);
		cleanup_mlx(data);
		exit_with_error("Memory allocation failed");
	}
	output = ft_strjoin("Moves: ", s);
	if (!output)
	{
		free_and_exit(-1, data->map, NULL);
		cleanup_mlx(data);
		exit_with_error("Memory allocation failed");
	}
	mlx_string_put(data->mlx_ptr, data->win_ptr, 40, 20, WHITE, output);
	free(s);
	free(output);
}

int	game_loop(t_data *data)
{
	clock_t	now;

	if (data->exit_flag)
	{
		free_and_exit(-1, data->map, NULL);
		cleanup_mlx(data);
		exit(0);
	}
	now = clock();
	if ((now - data->last) < CLOCKS_PER_SEC / 2)
		return (0);
	data->last = now;
	move_enemy(data);
	ft_memset(data->addr, 0, data->line_len * data->map->height);
	draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	print_moves(data);
	return (0);
}
