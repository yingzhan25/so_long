/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/16 14:40:42 by yingzhan         ###   ########.fr       */
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
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*texture[5];
	t_map	*map;
}	t_data;

# endif