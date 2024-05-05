# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upolat <upolat@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 17:49:46 by upolat            #+#    #+#              #
#    Updated: 2024/05/05 13:14:36 by upolat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME        = libftprintf.a
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
CC          = gcc
CFLAGS      = -Wall -Werror -Wextra -I$(LIBFT_DIR) -I.
AR          = ar rcs
RM          = rm -f

# Source and Object Files
SRC         = ft_printf.c ft_printf_utils.c ft_printf_base.c ft_printf_types.c
OBJ         = $(SRC:.c=.o)

# Rules
all:        $(NAME)

$(NAME):    $(OBJ)
	@make -C $(LIBFT_DIR)      # Make sure libft is compiled
	@cp $(LIBFT_LIB) $(NAME)   # Copy libft.a to current directory
	@$(AR) $(NAME) $(OBJ)      # Add ft_printf.o to libftprintf.a
	@echo "libftprintf.a created successfully!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@   # Compile ft_printf.c into ft_printf.o

clean:
	$(RM) $(OBJ) libft.a
	@make clean -C $(LIBFT_DIR)

fclean:     clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re:         fclean all

.PHONY:     all clean fclean re

