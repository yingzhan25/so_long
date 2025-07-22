/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/22 17:38:39 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

# define SIZE 32
# define KeyPress 2
# define DestroyNotify 17

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307

# define KeyPressMask (1L<<0)

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
	void	*tex[5];
	int		exit_flag;
	int		steps;
	t_map	*map;
}	t_data;

t_map	*parse_map(const char *name);
int		is_path_valid(t_map *map);
void	exit_with_error(char *s);
void	free_and_exit(int fd, t_map *map, char *s);
char	**make_empty_grid(t_map *map);
void	load_textures(t_data *data);
void	render_map(t_data *data);
int		handle_keypress(int	keycode, t_data *data);
int		handle_close(t_data *data);
int		handle_clean(t_data *data);

# endif