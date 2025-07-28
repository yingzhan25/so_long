/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:40:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/07/28 18:49:18 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# define SIZE 32
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
# define WHITE 0xFFFFFF
# define BLACK 0xFF000000

# include "/usr/local/include/mlx.h"
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <time.h>

typedef struct s_map
{
	char	**grid;
	char	**vis;
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	int		collect;
	int		enemy_x;
	int		enemy_y;
	int		exit;
	int		player;
	int		enemy;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*tex[7];
	int		dir;
	int		exit_flag;
	int		exit_display0;
	int		exit_display1;
	int		collect_display;
	int		steps;
	t_map	*map;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	clock_t	last;
}	t_data;

t_map	*parse_map(const char *name);
int		is_path_valid(t_map *map);
void	validate_map(t_map *map);
void	exit_with_error(char *s);
void	free_grid(t_map *map, char **s);
void	free_and_exit(int fd, t_map *map, char *s);
void	cleanup_mlx(t_data *data);
char	**make_empty_grid(t_map *map);
int		game_loop(t_data *data);
void	move_enemy(t_data *data);
void	move_player(t_data *data, int i, int j);

#endif