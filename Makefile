# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: averdejo <averdejo@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 11:21:23 by averdejo          #+#    #+#              #
#    Updated: 2024/03/19 19:02:23 by averdejo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

DIR_PRINTF = ft_printf/
PRINTF = $(DIR_PRINTF)libftprintf.a

SRC = main.c \
	utils.c \
	pipex.c \

OBJ = $(SRC:%.c=%.o)

INCLUDE = pipex.h
NAME = pipex
LIBFT = libft/libft.a
all: $(NAME)
lib: $(LIBFT)
printf: $(PRINTF)
#$(NAME): $(OBJ) $(INCLUDE)
#	$(LIB) $(NAME) $(OBJ)

$(NAME): $(OBJ) $(INCLUDE) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(PRINTF) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(DIR_PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(DIR_PRINTF)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(DIR_PRINTF)

re: fclean all
.PHONY: all clean fclean re lib printf
