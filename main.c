/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:39:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/16 12:39:44 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char *av[])
{
	t_map	map;
	t_data	data;

	if (ac != 2)
	{
		printf("ONLY 1 map is allowd!\n");
		return (1);
	}
	map = parse_map(av[1]);
	init_game(&game, &map);
	mlx_loop(data.mlx_ptr);
	free_map(&map);
	return 0;
}