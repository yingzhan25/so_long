NAME = so_long
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
INCLUDES = -I./ -I./mlx -I./libft/includes/
LIBFT = libft/libft.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(make) -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(make) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(make) -C libft fclean

re: fclean all

.PHONY: all clean fclean re