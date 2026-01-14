# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/04 14:01:02 by aiturria          #+#    #+#              #
#    Updated: 2024/09/19 19:04:22 by angcampo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
BONUS = cub3d_bonus
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = ./source/
BONUS_DIR = ./bonus/
LIBFT_DIR = libft
MLX42_DIR = MLX42
MLX42_BUILD_DIR = $(MLX42_DIR)/build
INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX42_DIR)/include
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX42_BUILD_DIR) -lmlx42 -lm -lglfw

SRCS = cb_cub3d.c cb_window.c cb_raycasting.c cb_drawing.c cb_movements.c \
		cb_drawing2.c cb_save_settings_line.c cb_savemap.c cb_check_map.c \

SRCS_BONUS = cb_cub3d_bonus.c cb_window_bonus.c cb_raycasting_bonus.c \
			cb_drawing_bonus.c cb_movements_bonus.c cb_drawing2_bonus.c \
			cb_littlemap_bonus.c cb_shotgun_bonus.c \
			cb_save_settings_line_bonus.c cb_savemap_bonus.c cb_check_map_bonus.c cb_check_doors_bonus.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all:	$(NAME)

bonus: $(BONUS)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(MLX42_BUILD_DIR)/libmlx42.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIBS)

$(BONUS): $(OBJS_BONUS) $(LIBFT_DIR)/libft.a $(MLX42_BUILD_DIR)/libmlx42.a
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS) $(INCLUDES) $(LIBS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42_BUILD_DIR)/libmlx42.a:
	cmake -S $(MLX42_DIR) -B $(MLX42_BUILD_DIR)
	$(MAKE) -C $(MLX42_BUILD_DIR)

%.o:	$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

%.o:	$(BONUS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX42_BUILD_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX42_BUILD_DIR)

re:	fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus
