# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 12:39:56 by yingzhan          #+#    #+#              #
#    Updated: 2025/07/28 17:19:02 by yingzhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_BONUS = so_long_bonus
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L/usr/local/lib/ -lmlx -lXext -lX11
INCLUDES = -I./ -I/usr/local/include -I./libft/includes/
LIBFT = libft/libft.a

SRCS = main.c map.c validation.c helper.c events.c
BONUS_SRCS = main_bonus.c map_bonus.c validation_bonus.c helper_bonus.c \
			render_bonus.c moves_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME_BONUS)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C libft fclean

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus