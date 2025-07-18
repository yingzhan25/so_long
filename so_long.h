/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/18 17:33:16 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx/mlx.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
#include "libft/includes/get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	int		collect;
	int		exit;
	int		player;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*texture[5];
	t_map	*map;
}	t_data;

t_map	*parse_map(const char *name);
int		is_path_valid(t_map *map);
void	free_map(t_map *map);
void	exit_with_error(char *s);
char	**make_empty_grid(t_map *map);
void	clean_fail_alloc(int i, char ***grid);

# endif